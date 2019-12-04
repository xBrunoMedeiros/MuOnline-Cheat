#pragma once

// Windows SDK
#include <Windows.h>
#include <iostream>
#include <thread>

// Debug Mode
#define DEBUG_MODE FALSE

// Project Utils
#include "Utilities\Debug.h"
#include "Utilities\Thread.h"
#include "Utilities\Memory\Detours.h"
#include "Utilities\Memory\SimpleMemory.h"

// Game Engine
#include "GameEngine\GameDefines.h"
#include "GameEngine\GameAddress.h"
#include "GameEngine\GameStructures.h"
#include "GameEngine\GameVariables.h"
#include "GameEngine\GameFunctions.h"
#include "GameEngine\Cryptographer\Cryptographer.h"

// Mods Engine
#include "ModEngine\ModFunctions.h"
#include "ModEngine\ModIntegrator.h"
#include "ModEngine\ModController.h"
#include "ModEngine\ModRuntime.h"
#include "ModEngine\ModAutoKill.h"
#include "ModEngine\ModBattle.h"