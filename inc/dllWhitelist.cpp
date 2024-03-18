#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <vector>
#include <string>
#include "Sleep.h"

// Function to get the file name of the current executable
std::string GetExecutableFileName() {
    char szFileName[MAX_PATH];
    GetModuleFileNameA(NULL, szFileName, MAX_PATH);
    return szFileName;
}

// This function is no longer needed
// std::wstring StringToWString(const std::string& s) { ... }

bool UnloadDllByName(std::string dllName) {
    HMODULE hModule = GetModuleHandleA(dllName.c_str()); // Use ANSI version directly
    if (hModule == NULL) {
        // std::cerr << "DLL not found: " << dllName << std::endl;
        return false;
    }

    // Attempt to unload the DLL
    if (FreeLibrary(hModule)) {
        std::cout << "DLL unloaded successfully: " << dllName << std::endl << std::endl;
        return true;
    } else {
        std::cerr << "Failed to unload DLL: " << dllName << std::endl << std::endl;
        return false;
    }
}

void ForceDllWhitelist(int intervalMilliseconds = 500) {
    while (true) { // Infinite loop to continuously check for unknown DLLs
        DWORD processId = GetCurrentProcessId();
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
        if (hProcess == NULL) {
            std::cerr << "Failed to open process." << std::endl << std::endl;
            continue; // Skip to the next iteration instead of returning
        }

        HMODULE hModules[1024];
        DWORD cbNeeded;
        if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
            int moduleCount = cbNeeded / sizeof(HMODULE);

            std::vector<std::string> knownModules = {
                "ntdll.dll",
                "KERNEL32.DLL",
                "KERNELBASE.dll",
                "apphelp.dll",
                "ucrtbase.dll",
                "msvcrt.dll",
                "kernel.appcore.dll"
            };

            knownModules.push_back(GetExecutableFileName());

            for (int i = 0; i < moduleCount; i++) {
                char szModName[MAX_PATH];
                if (GetModuleFileNameExA(hProcess, hModules[i], szModName, sizeof(szModName))) {
                    std::string moduleName = szModName;
                    bool isKnownModule = false;
                    for (const auto& knownModule : knownModules) {
                        if (moduleName.find(knownModule) != std::string::npos) {
                            isKnownModule = true;
                            break;
                        }
                    }

                    if(!isKnownModule) {
                        std::cout << "Unknown module detected: " << moduleName << std::endl;
                        UnloadDllByName(moduleName);
                    }
                }
            }
        } else {
            std::cerr << "Failed to enumerate process modules." << std::endl << std::endl;
        }

        CloseHandle(hProcess);
        customSleep(intervalMilliseconds);
    }
}