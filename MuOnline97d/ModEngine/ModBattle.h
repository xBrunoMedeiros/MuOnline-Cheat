#pragma once
#include "../Includes.h"

namespace ModEngine
{
	class Battle : public Thread<Battle>
	{
	public:
		// FastPot control variables.
		static DWORD FastPotKey; // Default: 0
		static DWORD FastPotDelay; // Default: 15ms
		static BOOL FastPotStatus; // Default: FALSE
		// OneHit control variables.
		static DWORD OneHitKey; // Default: 0
		static DWORD OneHitDelay; // Default: 15ms
		static BOOL OneHitStatus; // Default: FALSE
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
				if (GameEngine::StageScene != GameEngine::STAGE_WORLD || (!Battle::FastPotStatus && !Battle::OneHitStatus))
				{
					// Delay timer while running in background.
					Sleep(100);
					// Continue loop
					continue;
				}
				// AutoPot control timer var
				static DWORD FastPotTimer = 0;
				// AutoPot check is enabled
				if (Battle::FastPotStatus &&
					ModEngine::IsPressedKey(Battle::FastPotKey) &&
					ModEngine::Retardation(FastPotTimer, Battle::FastPotDelay)
					) {
					// Use consumable potion hp.
					Battle::UseConsumable(GameEngine::POT_HP);
				}

				// OneHit control timer var
				static DWORD OneHitTimer = 0;
				// OneHit check is enabled
				if (Battle::OneHitStatus &&
					ModEngine::IsPressedKey(Battle::OneHitKey) &&
					ModEngine::Retardation(OneHitTimer, Battle::OneHitDelay) &&
					GameEngine::TargetIndex >= 0
					) {
					// Use skill in target
					Battle::CastSkill(GameEngine::TargetIndex, 0x2B);
				}

				// Delay timer
				Sleep(1);
			}
		}
	public:
		static BOOL CastSkill(INT Index, UCHAR Skill)
		{
			// Check target is visible.
			if (!GameEngine::Objects[Index].IsVisible()) return FALSE;
			// Create packet
			GameEngine::StructUseSkill Packet = {
				/*    Type */ 0xC3,
				/*    Size */ 0x06,
				/*  Opcode */ 0x19,
				/*   Skill */ Skill,
				/* Network */ GameEngine::Objects[Index].Network[1], GameEngine::Objects[Index].Network[0]
			};
			PUCHAR PacketEncoded = GameEngine::Cryptographer::EncodeClientToServer(&Packet, 0);
			// Send packet
			INT Result = GameEngine::SendNetworkBuffer(GameEngine::Socket, PacketEncoded, PacketEncoded[1], 0);
			// Free packet
			delete[] PacketEncoded;
			// Return operation succesfully
			return TRUE;
		}

		static BOOL UseConsumable(GameEngine::ItemConsumable TypeItem)
		{
			// Get slot of potions
			UCHAR HPSlot = GameEngine::GetSlotOfConsumable(TypeItem);
			// Check have potions
			if (HPSlot < 0) return FALSE;
			// Create Packet
			GameEngine::StructConsumeItem Packet = {
				/*    Type */ 0xC3,
				/*    Size */ 0x06,
				/*  Opcode */ 0x26,
				/*    Slot */ HPSlot + 12,
				/* Unknown */ 0x0000
			};
			PUCHAR PacketEncoded = GameEngine::Cryptographer::EncodeClientToServer(&Packet, 0);
			// Send Packet
			INT Result = GameEngine::SendNetworkBuffer(GameEngine::Socket, PacketEncoded, PacketEncoded[1], 0);
			// Free Packet
			delete[] PacketEncoded;
			// Return operation succesfully
			return TRUE;
		}
	};
	/// <summary>
	/// FastPot control variables.
	/// </summary>
	DWORD Battle::FastPotKey = 0;
	DWORD Battle::FastPotDelay = 15;
	BOOL Battle::FastPotStatus = FALSE;
	/// <summary>
	/// OneHit control variables.
	/// </summary>
	DWORD Battle::OneHitKey = 0;
	DWORD Battle::OneHitDelay = 15;
	BOOL Battle::OneHitStatus = FALSE;
}