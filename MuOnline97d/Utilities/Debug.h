#pragma once
// #include "../Includes.h"

#if DEBUG_MODE == TRUE
	// remove warning unsafe freopen
	#pragma warning(disable:4996)
	// initialize console and set title
	#define DEBUG_INITIALIZE(Title) {	\
		AllocConsole();					\
		freopen("CONOUT$", "w", stdout);\
		freopen("CONIN$", "w", stdin);	\
		SetConsoleTitleA(Title);		\
	}
	// print message in console
	#define DEBUG(...) printf(__VA_ARGS__)
#else
	#define DEBUG_INITIALIZE(Title) { }
	#define DEBUG(...) { }
#endif