#pragma once
#include <Windows.h>

#define DeltaPtr(lpHook, lpCallback, iSize) ((DWORD)((DWORD)lpCallback - (DWORD)lpHook - (DWORD)iSize))
//#define SwapUInt16(num) ((USHORT)((num >> 8) | (num << 8)))

DWORD protectMemory(DWORD address, DWORD prot, SIZE_T size)
{
	DWORD oldProt;
	VirtualProtect((LPVOID)address, size, prot, &oldProt);
	return oldProt;
}

template<typename T>
T readMemory(DWORD address)
{
	return *((T*)address);
}

template<typename T>
void writeMemory(DWORD address, T value)
{
	*((T*)address) = value;
}

template<typename T>
void writeMemory(LPVOID address, T value)
{
	writeMemory<T>((DWORD)address, value);
}


#define callCdecl(dwAddress, Retn, ...) (*(Retn (__cdecl*)(__VA_ARGS__)) dwAddress)
#define callStdcall(dwAddress, Retn, ...) (*(Retn (__stdcall*)(__VA_ARGS__)) dwAddress)
#define callThiscall(dwAddress, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) dwAddress)
#define callThiscallMethod(dwClass, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)dwClass) + (dwIndex * 4))))