#pragma once
#include "../Includes.h"

namespace GameEngine
{
	/// <summary>
	/// Print message in game chat
	/// </summary>
	/// <param name="szFrom">Sender's name</param>
	/// <param name="szMessage">The message to be displayed</param>
	/// <param name="dwColor">Index color to message</param>
	VOID PutHistory(LPCSTR szFrom, LPCSTR szMessage, INT dwColor) {
		callStdcall(Address::lpFuncPutHistory, VOID, LPCSTR szFrom, LPCSTR szMessage, INT)(
			szFrom, szMessage, dwColor
		);
	}

	/// <summary>
	/// Displays a modal box with text
	/// </summary>
	/// <param name="szMessage">The message to be displayed</param>
	VOID ShowBox(LPCSTR szMessage) {
		callStdcall(Address::lpFuncShowBox, VOID, LPCSTR szMessage)(szMessage);
	}

	/// <summary>
	/// Search for entity with NetworkIndex specified.
	/// </summary>
	/// <param name="NetworkIndex">NetworkIndex of the entity</param>
	/// <returns>If the function succeeds, the return value EntryIndex</returns>
	INT GetIndexByNetwork(USHORT NetworkIndex)
	{
		return callCdecl(Address::lpFuncGetIndexByNetwork, INT, INT NetworkIndex)(NetworkIndex);
	};

	/// <summary>
	/// The send function is used to write outgoing data on a connected socket.
	/// </summary>
	/// <param name="hSocket">A descriptor identifying a connected socket.</param>
	/// <param name="lpBuffer">A pointer to a buffer containing the data to be transmitted.</param>
	/// <param name="iSize">The length, in bytes, of the data in buffer pointed to by the buf parameter.</param>
	/// <param name="Flags">A set of flags that specify the way in which the call is made. </param>
	/// <returns>
	/// If no error occurs, send returns the total number of bytes sent,
	/// which can be less than the number requested to be sent in the len parameter.
	/// </returns>
	INT SendNetworkBuffer(INT hSocket, PUCHAR lpBuffer, INT iSize, INT Flags)
	{
		return callStdcall(readMemory<DWORD>(Address::lpFuncSendNetworkBuffer), INT, INT hSocket, PUCHAR lpBuffer, INT iSize, INT Flags)(
			hSocket, lpBuffer, iSize, Flags
		);
	};

	/// <summary>
	///  Get slot of consumable item.
	/// </summary>
	/// <param name="TypeItem">Item type index</param>
	/// <returns>If the function succeeds, the return slot number</returns>
	UCHAR GetSlotOfConsumable(ItemConsumable TypeItem)
	{
		return callCdecl(Address::lpFuncGetSlotOfConsumable, UCHAR, ItemConsumable TypeItem)(TypeItem);
	};
}