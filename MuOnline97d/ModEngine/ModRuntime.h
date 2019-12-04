#pragma once
#include "../Includes.h"

namespace ModEngine
{
	class Runtime : public Thread<Runtime>
	{
	public:
		// Utilities control variables.
		static BOOLEAN Pull; // Default: FALSE
		static BOOLEAN Trace; // Default: FALSE
		static BOOLEAN AutoTrade; // Default: FALSE
		static DWORD TargetsCount; // Default: 0
		static CHAR Targets[10][GameEngine::NICKNAME_MAX_SIZE + 1]; // Default: { 0 }
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
				if (GameEngine::StageScene != GameEngine::STAGE_WORLD || (!Runtime::Pull && !Runtime::Trace && !Runtime::AutoTrade))
				{
					// Delay timer while running in background.
					Sleep(100);
					// Continue loop
					continue;
				}
				// Get own object.
				GameEngine::PEntryObject SelfObject = &GameEngine::Objects[GameEngine::SelfIndex];
				// Loop between objects.
				for (int Index = 0; Index < 400; Index++)
				{
					// Get target object.
					GameEngine::PEntryObject TargetObject = &GameEngine::Objects[Index];
					// Check target object with own object.
					if (TargetObject == SelfObject) continue;
					// Target is visible
					if (!TargetObject->IsVisible()) continue;
					// Target is alive
					if (TargetObject->AnimDeath > 0) continue;
					// Loop in objects
					for (DWORD A = 0; A < Runtime::TargetsCount; A++)
					{
						// Check target nickname
						if (_stricmp((LPCSTR)&TargetObject->Name, Runtime::Targets[A]) == 0)
						{
							// Pull Object
							if (Runtime::Pull)
								TargetObject->Position = SelfObject->Position;
							// Trace Object, if defined only 1 target.
							else if (Runtime::Trace && Runtime::TargetsCount == 1)
								SelfObject->Position = TargetObject->Position;
							// AutoTrade
							static DWORD AutoTradeTimer = 0;
							if (Runtime::AutoTrade && !GameEngine::TradeOpen && ModEngine::Retardation(AutoTradeTimer, 500))
								Runtime::RequestTrade(Index);
							// Break
							break;
						}
					}
					// Minimum delay.
					Sleep(1);
				}
				// Delay Runtime
				Sleep(50);
			}
		}

		static BOOL RequestTrade(INT Index)
		{
			DEBUG("Trade(%d): 0x%X - 0x%X\n\r", Index, GameEngine::Objects[Index].Network[0], GameEngine::Objects[Index].Network[1]);
			// Create packet
			GameEngine::StructTradeRequest Packet = {
				/*    Type */ 0xC3,
				/*    Size */ 0x05,
				/*  Opcode */ 0x36,
				/* Network */ GameEngine::Objects[Index].Network[1], GameEngine::Objects[Index].Network[0]
			};
			for (UCHAR X = 0; X < ((PUCHAR)&Packet)[1]; X++)
			{
				DEBUG("%0.2X ", ((PUCHAR)&Packet)[X]);
			}
			DEBUG("\n\r");
			PUCHAR PacketEncoded = GameEngine::Cryptographer::EncodeClientToServer(&Packet, 0);
			for (UCHAR X = 0; X < PacketEncoded[1]; X++)
			{
				DEBUG("%0.2X ", PacketEncoded[X]);
			}
			DEBUG("\n\r");
			// Send packet
			INT Result = GameEngine::SendNetworkBuffer(GameEngine::Socket, PacketEncoded, PacketEncoded[1], 0);
			// Free packet
			delete[] PacketEncoded;
			// Return operation succesfully
			return TRUE;
		}
	};
	// Utilities control variables.
	BOOLEAN Runtime::Pull = FALSE;
	BOOLEAN Runtime::Trace = FALSE;
	BOOLEAN Runtime::AutoTrade = FALSE;
	DWORD Runtime::TargetsCount = 0;
	CHAR Runtime::Targets[10][GameEngine::NICKNAME_MAX_SIZE + 1] = { 0 };
}
