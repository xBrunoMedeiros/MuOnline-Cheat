#pragma once
#include "../Includes.h"

namespace ModEngine
{
	struct _Battle
	{
		DWORD Key;
		DWORD Timer;
		BOOLEAN Status;
	};

	struct _AutoKill
	{
		DWORD Range;
		DWORD Timer;
		BOOLEAN Status;
	};

	typedef struct _ShareMemory
	{
		// Key of protection based on Timer
		DWORD KeyProtect;
		// FastPot
		_Battle FastPot;
		// OneHit
		_Battle OneHit;
		// GameSpeed
		DWORD GameSpeedTimer;
		// Target Functions
		BOOLEAN Pull;
		BOOLEAN Trace;
		BOOLEAN Aimbot;
		BOOLEAN AutoTrade;
		// AutoKill
		_AutoKill AutoKill;
		// Targets Selected
		DWORD TargetsCount;
		CHAR Targets[10][GameEngine::NICKNAME_MAX_SIZE + 1];
	} TShareMemory, *PShareMemory;

	class Controller
	{
	public:
		static HANDLE hShareMemory;
		static PShareMemory Cache;
	public:
		static BOOL Initialize(LPCSTR MemoryName)
		{
			// Open handle to Shared Memory
			Controller::hShareMemory = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, MemoryName);
			if (Controller::hShareMemory)
			{
				// Allocate Shared Memory
				Controller::Cache = (PShareMemory)MapViewOfFile(hShareMemory, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(TShareMemory));
				if (Controller::Cache == NULL)
				{
					// Fail to allocate memory
					DEBUG("Could not map view of file (%d).\n", GetLastError());
					return FALSE;
				} else {
					// Operation successfully.
					return TRUE;
				}
			} else {
				// Fail to open handle.
				DEBUG("Could not open file mapping object (%d).\n", GetLastError());
				return FALSE;
			}
		}
	};

	HANDLE Controller::hShareMemory = NULL;
	PShareMemory Controller::Cache = NULL;
}