#pragma once
#include "../Includes.h"

#define assignPtr(sType, dwAddress) *(sType*)(dwAddress)

namespace GameEngine
{
	/// <summary>
	/// Objects List
	/// </summary>
	auto Objects = readMemory<PEntryObject>(Address::lpVarObjects);

	/// <summary>
	/// Self index in object list
	/// </summary>
	auto& SelfIndex = assignPtr(INT, Address::lpVarSelfIndex);

	/// <summary>
	/// Target index in object list
	/// </summary>
	auto& TargetIndex = assignPtr(INT, Address::lpVarTargetIndex);

	/// <summary>
	/// Stage Index of the current stage
	/// </summary>
	auto& StageScene = assignPtr(DWORD, Address::lpVarStageScene);

	/// <summary>
	/// Handle network socket
	/// </summary>
	auto& Socket = assignPtr(DWORD, Address::lpVarSocketNetwork);

	/// <summary>
	/// Chat is open to write
	/// </summary>
	auto& ChatOpen = assignPtr(BOOLEAN, Address::lpVarChatOpen);

	/// <summary>
	/// Trade is open
	/// </summary>
	auto& TradeOpen = assignPtr(BOOLEAN, Address::lpVarTradeOpen);
}