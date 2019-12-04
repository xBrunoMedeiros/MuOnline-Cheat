#pragma once
#include "../Includes.h"

namespace ModEngine
{ 
	class AutoKill : public Thread<AutoKill>
	{
	public:
		// AutoKill control variables.
		static DWORD Range; // Default: 300 Range 
		static DWORD Timer; // Default: 25ms
		static BOOLEAN Status; // Default: FALSE
	public:
		// Thread Execute
		static VOID Run()
		{
			// Decoration Message
			DEBUG("%s: Called!\n\r", __FUNCTION__);
			// Keep Running
			while (TRUE)
			{
				// Check is enabled function & stage world.
				if (GameEngine::StageScene != GameEngine::STAGE_WORLD || !AutoKill::Status)
				{
					// Delay timer while running in background.
					Sleep(100);
					// Continue loop
					continue;
				}
				// Get own object.
				GameEngine::PEntryObject SelfObject = &GameEngine::Objects[GameEngine::SelfIndex];
				// Loop between objects.
				for (int Index = 0; Index < 400 && !SelfObject->InCity(); Index++)
				{
					// Minimum delay.
					Sleep(1);
					// Get target object.
					GameEngine::PEntryObject TargetObject = &GameEngine::Objects[Index];
					// Check target object with own object.
					if (TargetObject == SelfObject) continue;
					// Target is visible
					if (!TargetObject->IsVisible()) continue;
					// Target is alive
					if (TargetObject->AnimDeath > 0) continue;
					// Target in City
					if (TargetObject->InCity()) continue;
					// Target in Range
					if (TargetObject->GetDistance(SelfObject) > AutoKill::Range) continue;
					// Create packet
					GameEngine::StructUseSkill Packet = {
						/*    Type */ 0xC3,
						/*    Size */ 0x06,
						/*  Opcode */ 0x19,
						/*   Skill */ 0x2B,
						/* Network */ TargetObject->Network[1], TargetObject->Network[0]
					};
					// Encode packet
					PUCHAR PacketEncoded = GameEngine::Cryptographer::EncodeClientToServer(&Packet, 0);
					// Send packet
					INT Result = GameEngine::SendNetworkBuffer(GameEngine::Socket, PacketEncoded, PacketEncoded[1], 0);
					// Free packet
					delete[] PacketEncoded;
					// Delay timer
					Sleep(AutoKill::Timer);
				}
				Sleep(3);
			}
		}
	};
	// AutoKill control variables.
	DWORD AutoKill::Range = 300;
	DWORD AutoKill::Timer = 25;
	BOOLEAN AutoKill::Status = FALSE;
}