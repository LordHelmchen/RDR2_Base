#include "includes.h"


unsigned long __stdcall onAttach()
{
    hooks::init();
    return 0;
}

bool menuStarted = false;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        if (!menuStarted) //For some reason (maybe i am just stupid) DLL_PROCESS_ATTACH gets called twice
        {
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)onAttach, hModule, 0, 0);
            globals::module = hModule;
        }
        menuStarted = true;
    }
    return TRUE;
}

