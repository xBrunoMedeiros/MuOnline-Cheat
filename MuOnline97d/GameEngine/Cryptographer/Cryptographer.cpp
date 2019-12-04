#include "Cryptographer.h"

namespace GameEngine
{
	// Offset in array
	#define XorModulus	0
	#define Encryption	4
	#define Decryption	8
	#define XorKeyList	12

	// XorList to Encode/Decode with Xor32
	UCHAR Cryptographer::XorKey[32] = {
		0xE7, 0x6D, 0x3A, 0x89,	0xBC, 0xB2, 0x9F, 0x73,
		0x23, 0xA8, 0xFE, 0xB6,	0x49, 0x5D, 0x39, 0x5D,
		0x8A, 0xCB, 0x63, 0x8D,	0xEA, 0x7D, 0x2B, 0x5F,
		0xC3, 0xB1, 0xE9, 0x83,	0x29, 0x51, 0xE8, 0x56
	};

	// ClientToServer with EncodeC1C2 (Enc1.dat / Dec1.dat)
	DWORD Cryptographer::ClientToServer[16] = {
		0x0001F44F, 0x00028386, 0x0001125B, 0x0001A192, // XorModulus
		0x00005BC1, 0x00002E87,	0x00004D68, 0x0000354F, // Encryption
		0x00007B38, 0x000007FF, 0x0000DEB3, 0x000027C7, // Decryption
		0x0000BD1D, 0x0000B455, 0x00003B43, 0x00009239  // XorKeyList
	};

	// ServerToClient without EncodeC1C2 (Enc2.dat / Dec2.dat)
	DWORD Cryptographer::ServerToClient[16] = {
		0x00011E6E, 0x0001ADA5, 0x0001821B, 0x00029C32, // XorModulus
		0x00003371, 0x00004A5C, 0x00008A9A, 0x00007393, // Encryption
		0x00004673, 0x00007684, 0x0000607D, 0x00002B85, // Decryption
		0x0000F234, 0x0000FB99, 0x00008A2E, 0x0000FC57  // XorKeyList
	};

	PUCHAR Cryptographer::EncodeClientToServer(LPVOID lpSource, UCHAR KeyEncode)
	{
		// Assign pointer unsigned char
		PUCHAR tempSrc = (PUCHAR)lpSource;
		PUCHAR lpOutput = nullptr;
		PUCHAR lpTemp = nullptr;
		// Check encryption type
		switch (tempSrc[0])
		{
			case 0xC1:
			{
				// Get current size, specified by the second byte.
				INT iSize = tempSrc[1];
				// Allocate memory
				lpOutput = new UCHAR[iSize];
				memcpy(lpOutput, lpSource, iSize);
				// Encode packet with Xor32
				Cryptographer::EncryptXor32(lpOutput, iSize);
			} break;
			case 0xC2:
			{
				// Get current size, specified by the second and third byte.
				// Encode packet with Xor32
			} break;
			case 0xC3: 
			{
				// Get current size, specified by the second byte.
				INT iSize = tempSrc[1];
				// Calculate new size
				INT newSize = ((iSize + 7) / 8) * 11;
				// Allocate memory
				lpOutput = new UCHAR[newSize];
				lpTemp = new UCHAR[iSize];
				memset(lpOutput, 0, newSize);
				memcpy(lpTemp, lpSource, iSize);
				// Encode packet with Xor32
				Cryptographer::EncryptXor32(lpTemp, iSize);
				// Set counter/serial of packet
				lpTemp[1] = KeyEncode;
				// Encode packet with SimpleModulus
				Cryptographer::Encrypt(&lpOutput[2], &lpTemp[1], iSize - 1, &Cryptographer::ClientToServer[0]);
				// Free memory of temp buffer
				delete[] lpTemp;
				// Set encode type and size
				lpOutput[0] = 0xC3;
				lpOutput[1] = newSize + 2;
			} break;
			case 0xC4:
			{
				// Get current size, specified by the second and third byte.
				// Encode packet with Xor32
				// Encode packet with SimpleModulus
			} break;
		}
		return lpOutput;
	}

	VOID Cryptographer::EncryptXor32(PUCHAR lpBuff, INT iSize)
	{
		// Encode buffer with Xor32
		for (int i = 3; i < iSize; i++)
			lpBuff[i] ^= lpBuff[i - 1] ^ Cryptographer::XorKey[i % 32];
	}

	INT Cryptographer::Encrypt(LPVOID lpDest, LPVOID lpSource, INT iSize, PDWORD Where)
	{
		INT iTempSize = iSize;
		INT iOriSize;
		PUCHAR lpTempDest = (LPBYTE)lpDest;
		PUCHAR lpTempSource = (LPBYTE)lpSource;

		iSize = ((iSize + 7) / 8) * 11;

		if (lpDest != NULL)
		{
			iOriSize = iTempSize;
			for (INT i = 0; i < iTempSize; i += 8, iOriSize -= 8, lpTempDest += 11)
			{
				if (iOriSize >= 8)
					Cryptographer::EncryptBlock(lpTempDest, lpTempSource + i, 8, Where);
				else
					Cryptographer::EncryptBlock(lpTempDest, lpTempSource + i, iOriSize, Where);
			}
		}
		return iSize;
	}

	INT Cryptographer::Decrypt(LPVOID lpDest, LPVOID lpSource, INT iSize, PDWORD Where)
	{
		if (lpDest == NULL)
			return iSize * 8 / 11;

		LPBYTE lpTempDest = (LPBYTE)lpDest;
		LPBYTE lpTempSrc = (LPBYTE)lpSource;

		INT iResult = 0;
		INT iDecLen = 0;

		while (iSize > 0 && iDecLen < iSize)
		{
			INT iTempResult = Cryptographer::DecryptBlock(lpTempDest, lpTempSrc, Where);
			if (iResult < 0)
				return iResult;
			iResult += iTempResult;
			iDecLen += 11;
			lpTempSrc += 11;
			lpTempDest += 8;
		}
		return iResult;
	}

	INT Cryptographer::EncryptBlock(LPVOID lpDest, LPVOID lpSource, INT iSize, PDWORD Where)
	{
		DWORD dwEncBuffer[4];
		DWORD dwEncValue = 0;

		LPBYTE lpEncDest = (LPBYTE)lpDest;
		LPBYTE lpEncSource = (LPBYTE)lpSource;

		memset(lpEncDest, 0, 11);

		for (INT i = 0; i < 4; i++)
		{
			dwEncBuffer[i] = (Where[XorKeyList + i] ^ ((PWORD)lpEncSource)[i] ^ dwEncValue) * Where[Encryption + i] % Where[XorModulus + i];
			dwEncValue = dwEncBuffer[i] & 0xFFFF;
		}

		for (INT i = 0; i < 3; i++)
		{
			dwEncBuffer[i] = dwEncBuffer[i] ^ Where[XorKeyList + i] ^ (dwEncBuffer[i + 1] & 0xFFFF);
		}

		INT iBitPos = 0;
		for (INT i = 0; i < 4; i++)
		{
			iBitPos = Cryptographer::AddBits(lpDest, iBitPos, &dwEncBuffer[i], 0, 16);
			iBitPos = Cryptographer::AddBits(lpDest, iBitPos, &dwEncBuffer[i], 22, 2);
		}

		BYTE btCheckSum = 0xF8;

		for (INT i = 0; i < 8; i++)
			btCheckSum ^= lpEncSource[i];

		((LPBYTE)&dwEncValue)[1] = btCheckSum;
		((LPBYTE)&dwEncValue)[0] = btCheckSum ^ iSize ^ 0x3D;

		return Cryptographer::AddBits(lpDest, iBitPos, &dwEncValue, 0, 16);
	}

	INT Cryptographer::DecryptBlock(LPVOID lpDest, LPVOID lpSource, PDWORD Where)
	{
		memset(lpDest, 0, 8);
		DWORD dwDecBuffer[4] = { 0 };
		INT iBitPosition = 0;

		LPBYTE lpDecDest = (LPBYTE)lpDest;
		LPBYTE lpDecSource = (LPBYTE)lpSource;

		for (INT i = 0; i < 4; i++)
		{
			Cryptographer::AddBits(&dwDecBuffer[i], 0, lpDecSource, iBitPosition, 16);
			iBitPosition += 16;
			Cryptographer::AddBits(&dwDecBuffer[i], 22, lpDecSource, iBitPosition, 2);
			iBitPosition += 2;
		}

		for (INT i = 2; i >= 0; i--)
		{
			dwDecBuffer[i] = dwDecBuffer[i] ^ Where[XorKeyList + i] ^ (dwDecBuffer[i + 1] & 0xFFFF);
		}

		DWORD Temp = 0, Temp1;

		for (INT i = 0; i < 4; i++)
		{
			Temp1 = ((Where[Decryption + i] * (dwDecBuffer[i])) % Where[XorModulus + i]) ^ Where[XorKeyList + i] ^ Temp;
			Temp = dwDecBuffer[i] & 0xFFFF;
			((PWORD)lpDecDest)[i] = (Temp1 & 0xFFFF);
		}

		dwDecBuffer[0] = 0;
		Cryptographer::AddBits(&dwDecBuffer[0], 0, lpDecSource, iBitPosition, 16);
		((LPBYTE)dwDecBuffer)[0] = ((LPBYTE)dwDecBuffer)[1] ^ ((LPBYTE)dwDecBuffer)[0] ^ 0x3D;

		BYTE btCheckSum = 0xF8;

		for (INT i = 0; i < 8; i++)
			btCheckSum ^= lpDecDest[i];

		if (btCheckSum != ((LPBYTE)dwDecBuffer)[1])
			return -1;

		return ((LPBYTE)dwDecBuffer)[0];
	}

	INT Cryptographer::AddBits(LPVOID lpDest, INT iDestBitPos, LPVOID lpSource, INT iBitSourcePos, INT iBitLen)
	{
		// Get Buffer Lens
		INT iSourceBufferBitLen = iBitLen + iBitSourcePos;
		INT iTempBufferLen = Cryptographer::GetByteOfBit(iSourceBufferBitLen - 1);
		iTempBufferLen += 1 - Cryptographer::GetByteOfBit(iBitSourcePos);

		// Copy the Source Buffer
		PUCHAR pTempBuffer = new UCHAR[iTempBufferLen + 1];
		memset(pTempBuffer, 0, iTempBufferLen + 1);
		memcpy(pTempBuffer, (PUCHAR)lpSource + Cryptographer::GetByteOfBit(iBitSourcePos), iTempBufferLen);

		// Save the Last ibt if exist
		if ((iSourceBufferBitLen % 8) != 0)
			pTempBuffer[iTempBufferLen - 1] &= 255 << (8 - (iSourceBufferBitLen % 8));

		// Get the Values to Shift
		INT iShiftLeft = (iBitSourcePos % 8);
		INT iShiftRight = (iDestBitPos % 8);

		// Shift the Values to Add the right space of the desired bits
		Cryptographer::Shift(pTempBuffer, iTempBufferLen, -iShiftLeft);
		Cryptographer::Shift(pTempBuffer, iTempBufferLen + 1, iShiftRight);

		// Copy the the bits of Source to the Dest
		INT iNewTempBufferLen = ((iShiftRight <= iShiftLeft) ? 0 : 1) + iTempBufferLen;
		PUCHAR TempDist = (PUCHAR)lpDest + Cryptographer::GetByteOfBit(iDestBitPos);

		for (INT i = 0; i < iNewTempBufferLen; i++)
			TempDist[i] |= pTempBuffer[i];

		// Delete the temp Buffer
		delete[] pTempBuffer;

		// Return the number of bits of the new Dest Buffer
		return iDestBitPos + iBitLen;
	}

	VOID Cryptographer::Shift(LPVOID lpBuff, INT iSize, INT ShiftLen)
	{
		PUCHAR TempBuff = (PUCHAR)lpBuff;

		// Case no Shift Len
		if (ShiftLen != 0)
		{
			// Shift Right
			if (ShiftLen > 0)
			{
				if ((iSize - 1) > 0)
				{
					for (int i = (iSize - 1); i > 0; i--)
					{
						TempBuff[i] = (TempBuff[i - 1] << ((8 - ShiftLen))) | (TempBuff[i] >> ShiftLen);
					}
				}
				TempBuff[0] >>= ShiftLen;
			}
			// Shift Left
			else {
				ShiftLen = -ShiftLen;
				if ((iSize - 1) > 0)
				{
					for (int i = 0; i < (iSize - 1); i++)
					{
						TempBuff[i] = (TempBuff[i + 1] >> ((8 - ShiftLen))) | (TempBuff[i] << ShiftLen);
					}
				}
				TempBuff[iSize - 1] <<= ShiftLen;
			}
		}
	}

	INT Cryptographer::GetByteOfBit(INT btByte)
	{
		return btByte >> 3;
	}
}