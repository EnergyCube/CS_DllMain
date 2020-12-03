#include "pch.h"
#include <string>
#include <shlwapi.h>
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "mscoree.lib")

extern void LaunchDll(
    unsigned char* dll, size_t dllLength,
    char const* className, char const* methodName);

void LaunchDll(
    unsigned char* dll, size_t dllLength,
    char const* className, char const* methodName)
{}

BOOL APIENTRY DllMain(HMODULE h,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DWORD Current_Process_ProcessID = GetCurrentProcessId();
        if (Current_Process_ProcessID > 0) {
            std::wstring MutexString = L"ProcessCheck_" + std::to_wstring(Current_Process_ProcessID);
            HANDLE handleMutex = CreateMutexW(NULL, TRUE, MutexString.c_str());
            bool LoadDllDuringThisCall = true;
            if (GetLastError() == ERROR_ALREADY_EXISTS)
            {
                LoadDllDuringThisCall = false;
                // Already Loaded
            }
            if (LoadDllDuringThisCall) {
                wchar_t CurrentWorkingDirectoryWhereExeIs[MAX_PATH];
                std::wstring ress = std::wstring(CurrentWorkingDirectoryWhereExeIs, GetModuleFileNameW(NULL, CurrentWorkingDirectoryWhereExeIs, MAX_PATH));
                PathRemoveFileSpecW(CurrentWorkingDirectoryWhereExeIs);
                std::wstring CurrentExeWorksPath = CurrentWorkingDirectoryWhereExeIs;

                std::wstring CS_DllMainDLL_Path = CurrentExeWorksPath + L"\\CS_DllMain.dll";

                typedef void (WINAPI* FuncCall)();
                FuncCall CS_DllMain_FuncCall;

                HMODULE CS_DllMainDLL = LoadLibraryW(CS_DllMainDLL_Path.c_str());
                if (CS_DllMainDLL != NULL) {
                    CS_DllMain_FuncCall = (FuncCall)GetProcAddress(CS_DllMainDLL, "CS_DllMain");
                    if (CS_DllMain_FuncCall) {
                        // Call the CS_DllMain function in the C# dll
                        CS_DllMain_FuncCall();
                    } else {
                        // Function not found !
                    }
                }
                else {
                    std::wstring ErrorCode = std::to_wstring(GetLastError());
                    // Unnable to found CS_DllMain.dll !
                }
            }
        }
        else {
            // Unnable to get current process ID !
        }
        break;
    }
    case DLL_THREAD_ATTACH:
    {
        break;
    }
    case DLL_THREAD_DETACH:
    {
        break;
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}