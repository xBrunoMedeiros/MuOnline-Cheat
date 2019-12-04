#pragma once
#include <Windows.h>
#include <thread>

template <typename T>
class Thread
{
public:
	static std::thread thread;
public:
	static BOOL Initialize()
	{
		// Decoration Message
		DEBUG("%s: Called!\n\r", __FUNCTION__);
		// Check is running thread
		if (Thread<T>::thread.joinable())
			return FALSE;
		// Create thread
		Thread<T>::thread = std::thread(&T::Run);
		// Return success operation
		return TRUE;
	}
	static BOOL Deinitialize()
	{
		// Decoration Message
		DEBUG("%s: Called!\n\r", __FUNCTION__);
		// Check is running thread
		if (Thread<T>::thread.joinable())
			return FALSE;
		// Finalize thread
		TerminateThread(Thread<T>::thread.native_handle(), 1);
		// Return success operation
		return TRUE;
	}
};
template<typename T> std::thread Thread<T>::thread;