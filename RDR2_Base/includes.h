#pragma once

#include <Windows.h>
#include <iostream>
#include "hooks.h"
#include "globals.h"
#include <string>
#include <Psapi.h>
#include "memory.h"
#include "MinHook/MinHook.h"
#include "natives.h"
#include "invoker.h"
#include "UI.h"
#include "Features.h"
#include "menu.h"
#pragma comment(lib, "MinHook\\libMinHook.x64.lib")
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dmoguids.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#pragma comment(lib, "msdmo.lib")
#pragma comment(lib, "Strmiids.lib")
#define CONSOLE
