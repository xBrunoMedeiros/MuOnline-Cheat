#pragma once
#include "../Includes.h"

namespace GameEngine
{
	/// <summary>
	/// Structure of packet 0xC3 0x05 0x36
	/// </summary>
	typedef struct _StructTradeRequest
	{
		UCHAR Type;
		UCHAR Size;
		UCHAR Opcode;
		UCHAR Network[2];
	} StructTradeRequest, *PStructTradeRequest;

	/// <summary>
	/// Structure of packet 0xC3 0x06 0x19
	/// </summary>
	typedef struct _StructUseSkill
	{
		UCHAR Type;
		UCHAR Size;
		UCHAR Opcode;
		UCHAR Skill;
		UCHAR Network[2];
	} StructUseSkill, *PStructUseSkill;

	/// <summary>
	/// Structure of packet 0xC3 0x06 0x26
	/// </summary>
	typedef struct _StructConsumeItem
	{
		UCHAR Type;
		UCHAR Size;
		UCHAR Opcode;
		UCHAR Slot;
		USHORT Unknown;
	} StructConsumeItem, *PStructConsumeItem;

	/// <summary>
	/// Structure of Positions
	/// </summary>
	typedef struct _D3DVector3D
	{
		FLOAT X;
		FLOAT Y;
		FLOAT Z;
	} D3DVector3D, *PD3DVector3D;

	/// <summary>
		/// Structure of objects
		/// </summary>
		typedef struct _EntryObject
		{
			USHORT Flags; // 0x0000
		USHORT Sprite; // 0x0002
		CHAR __0x0004[0x000E - 0x0004];
		BYTE SpriteSize; // 0x000E
		CHAR __0x000F;
		D3DVector3D Position; // 0x0010
		CHAR __0x001C[0x010D - 0x001C];
		BYTE Animation; // 0x010D
		CHAR __0x010E[0x0113 - 0x010E];
		BYTE AnimationSpeed; // 0x0113
		CHAR __0x0114[0x01C4 - 0x0114];
		BYTE Classe; // 0x01C4
		CHAR __0x01C5;
		WORD Level; // 0x01C6
		BYTE Privileges; // 0x01C8
		CHAR Name[23]; // 0x01C9
		CHAR __0x01E0[0x01E4 - 0x01E0];
		UCHAR Network[2]; // 0x01E4
		CHAR __0x01E6[0x0368 - 0x01E6];
		BOOL Walking; // 0x0368
		CHAR __0x036C[0x0378 - 0x036C];
		BYTE LastMovement; // 0x0378
		BYTE AnimDeath; // 0x0379
		CHAR __0x037A[0x03D0 - 0x037A];
		DWORD FlagsCity; // 0x03D0
		CHAR __0x03D4[0x0424 - 0x03D4];
	public:
		// Check is visible object
		BOOL IsVisible()
		{
			return this->Flags & GameEngine::OBJECT_VISIBLE;
		}
		// Check is inside the city.
		BOOL InCity()
		{
			return this->FlagsCity & 0x10000;
		}
		// Distance to another object.
		DOUBLE GetDistance(_EntryObject* Entry)
		{
			return sqrt(
				pow((this->Position.X - Entry->Position.X), 2) +
				pow((this->Position.Y - Entry->Position.Y), 2) +
				pow((this->Position.Z - Entry->Position.Z), 2)
			);
		}
	} EntryObject, *PEntryObject;
}