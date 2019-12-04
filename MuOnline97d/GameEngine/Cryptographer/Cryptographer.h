#pragma once
#include <Windows.h>

namespace GameEngine
{
	class Cryptographer
	{
	private:
		static UCHAR XorKey[32];
		static DWORD ClientToServer[16];
		static DWORD ServerToClient[16];
	public:
		static PUCHAR EncodeClientToServer(LPVOID lpSource, UCHAR KeyEncode);
	protected:
		static VOID EncryptXor32(PUCHAR lpBuff, INT iSize);
	protected:
		static INT Encrypt(LPVOID lpDest, LPVOID lpSource, INT iSize, PDWORD Where);
		static INT Decrypt(LPVOID lpDest, LPVOID lpSource, INT iSize, PDWORD Where);
	protected:
		static INT EncryptBlock(LPVOID, LPVOID, INT, PDWORD);
		static INT DecryptBlock(LPVOID, LPVOID, PDWORD);
		static INT AddBits(LPVOID lpDest, INT iDestBitPos, LPVOID lpSource, INT iBitSourcePos, INT iBitLen);
		static VOID Shift(LPVOID lpBuff, INT iSize, INT ShiftLen);
		static INT GetByteOfBit(INT);
	public:
		static auto Singleton()
		{
			auto instance = new Cryptographer();
			return instance;
		}
	};
}