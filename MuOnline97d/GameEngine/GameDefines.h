#pragma once
#include "../Includes.h"

namespace GameEngine
{
	/// <summary>
	/// Game Defines
	/// </summary>
	enum Game : DWORD
	{
		NICKNAME_MAX_SIZE = 10
	};

	/// <summary>
	/// Types of consumables
	/// </summary>
	enum ItemConsumable : DWORD
	{
		POT_HP = 0x0000,
		POT_MP = 0x0001,
		POT_ANTIDOTE = 0x0002
	};

	/// <summary>
	/// Types of screen stage
	/// </summary>
	enum SceneStages : DWORD
	{
		STAGE_CHARS = 0x0004,
		STAGE_WORLD = 0x0005
	};

	/// <summary>
	/// Object Details Flags
	/// </summary>
	enum ObjectDetail : DWORD
	{
		OBJECT_VISIBLE = 0x0001
	};
}