#pragma once
#include "../Includes.h"

namespace GameEngine
{
	/// <summary>
	/// Customer memory addresses.
	/// </summary>
	enum Address : DWORD
	{
		// Native Variables
		lpVarObjects				= 0x07424644, // Objects List
		lpVarSelfIndex				= 0x05754890, // Self index in object list
		lpVarTargetIndex			= 0x006B7DC4, // Target index in object list
		lpVarStageScene				= 0x006C41C0, // Index of the current stage
		lpVarSocketNetwork			= 0x057506AC, // Handle network socket
		lpVarChatOpen				= 0x006B7DFC, // Chat is open to write
		lpVarTradeOpen				= 0x07D139BC, // Trade is open
		
		// Native Functions
		lpFuncSendNetworkBuffer		= 0x006A7584, // Send packet to Server
		lpFuncGetIndexByNetwork		= 0x00507C70, // Get EntryIndex using EntryNetwork
		lpFuncGetSlotOfConsumable	= 0x0054C550, // Get Slot of consumable item 
		lpFuncPutHistory			= 0x00549630, // Print message in game chat
		lpFuncShowBox				= 0x0061E5B0, // Show message box in game

		// Pointers to ModEngine::Integrator { SpeedHacker and anothers... }
		lpSpeedHacker				= 0x00628EAE, // SpeedHacker - Change Memory to call ptr ds:[MyCallback].

		// Cryptographer
		lpVarCryptographer			= 0x05754800,
		lpFuncCryptographerEncrypt	= 0x00674DC0,
		// HashTable
		lpVarHashTable				= 0x057500B0,
		lpFuncHashTableGetCounter	= 0x00409340,
		lpFuncHashTableSetCounter	= 0x00409580,
	};

	typedef struct _StructCryptographer
	{
	public:
		INT Encrypt(PUCHAR lpOutput, PUCHAR lpInput, UINT iSize) {
			return callThiscall(Address::lpFuncCryptographerEncrypt, INT, _StructCryptographer*, PUCHAR, PUCHAR, UINT)(
				this, lpOutput, lpInput, iSize
			);
		}
	} StructCryptographer, *PStructCryptographer;

	typedef struct _StructHashTable
	{
	public:
		VOID GetCounter(PUCHAR Counter) {
			callThiscall(Address::lpFuncHashTableGetCounter, VOID, _StructHashTable*, PUCHAR lpHashCounter)(this, Counter);
		}
		VOID SetCounter(PUCHAR Counter) {
			callThiscall(Address::lpFuncHashTableSetCounter, VOID, _StructHashTable*, PUCHAR lpHashCounter)(this, Counter);
		}
	} StructHashTable, *PStructHashTable;
}