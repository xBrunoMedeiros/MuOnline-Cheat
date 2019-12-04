#pragma once
#include "../Includes.h"

namespace ModEngine
{
	/// <summary>
	/// Integration module with the game.
	/// </summary>
	class Integrator
	{
	public:
		/// <summary>
		/// Speed of game acceleration, Default: 0.
		/// </summary>
		static DWORD GameAcceleration;
	public:
		/// <summary>
		/// Initialize Hooks in the game.
		/// </summary>
		static BOOL Initialize()
		{
			// Decoration Message
			DEBUG("%s: Called!\n\r", __FUNCTION__);
			// Create pointer to my callback
			static LPVOID PtrGameTimer = &Integrator::GameTimer;
			// Write pointer in the call
			writeMemory<LPVOID>(GameEngine::Address::lpSpeedHacker, &PtrGameTimer);
			// Decoration Message
			DEBUG("%s: GameTimer Hooked!\n\r", __FUNCTION__);
			// Return result
			return TRUE;
		}
		/// <summary>
		/// Remove Hooks of the game.
		/// </summary>
		static BOOL Deinitialize()
		{
			// Decoration Message
			DEBUG("%s: Called!\n\r", __FUNCTION__);
			// Decoration Message
			DEBUG("%s: [Warning] Disabled!\n\r", __FUNCTION__);
			// ....
			return FALSE;
		}
	protected:
		/// <summary>
		/// Game function callback to integrate game acceleration.
		/// </summary>
		static DWORD __stdcall GameTimer(VOID)
		{
			return GetTickCount() - Integrator::GameAcceleration;
		}
	};

	/// <summary>
	/// Speed of game acceleration, Default: 0.
	/// </summary>
	DWORD Integrator::GameAcceleration = 0;
}