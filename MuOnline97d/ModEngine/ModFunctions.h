#pragma once
#include "../Includes.h"

namespace ModEngine
{

	/// <summary>
	/// Check timer and re-set timer.
	/// </summary>
	/// <param name="Timer">Action Timer.</param>
	/// <param name="Delay">Waiting time between actions.</param>
	/// <returns>If the function succeeds, the return TRUE</return>
	BOOL Retardation(DWORD& Timer, DWORD Delay)
	{
		// Check timer, and set new time to re-assign.
		if (GetTickCount() - Timer >= Delay)
		{
			Timer = GetTickCount();
			return TRUE;
		} else
			return FALSE;
	}

	/// <summary>
	/// Check if there is a key, or if chat is closed & key is pressed.
	/// </summary>
	/// <param name="vKey">ASCII codes's</param>
	/// <returns>If the function succeeds, the return TRUE</return>
	BOOL IsPressedKey(INT vKey)
	{
		// Check if there is a key, or if chat is closed & key is pressed.
		return vKey == 0 || (!GameEngine::ChatOpen && (GetAsyncKeyState(vKey) & 0x8001));
	}
}