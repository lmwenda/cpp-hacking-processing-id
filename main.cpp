#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

// Global Variables

/*
hProc = Handle Process
pID = idek
*/

HANDLE hProc = NULL; // This Global Variable is going to be the Handle to the Process
DWORD pID; // This is going to read or write memory with that Global Variable handle

// A Function which will return a Boolean and attach to the processor we want
bool attachProc(char* procName)
{
    PROCESSENTRY32 procEntry32;
    procEntry32.dwSize = sizeof(PROCESSENTRY32);
    auto hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(hProcSnap == INVALID_HANDLE_VALUE)
    {
        std::cout<<"Failed to take a Snapshot of Processes!"<<std::endl;
        return false;
    }

    while(Process32Next(hProcSnap, &procEntry32))
    {
        std::cout<<procEntry32.szExeFile << std::endl; // Printing out the File

        if(!strcmp(procName, procEntry32.szExeFile))
        {
            std::cout<<"Found Process " << procEntry32.szExeFile << " with Process ID " << procEntry32.th32ProcessID<<std::endl;
            hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
            pID = procEntry32.th32ProcessID;

            if(hProc == NULL)
            {
                std::cout<<"Failed getting handle to Process." << std::endl;
            }

            CloseHandle(hProcSnap);
            return true;
        }
    }
    std::cout<<"Couldn't find "<< procName << " in the process snapshot"<<std::endl;
    CloseHandle(hProcSnap);
    return false;
}

template <class dataType>
void wpm(dataType valToWrite, DWORD addressToWrite)
{
    WriteProcessMemory(hProc, (PVOID)addressToWrite, &valToWrite, sizeof(dataType), 0);
}

template <class dataType>
dataType rpm (DWORD addressToRead)
{
    dataType rpmBuffer;
    ReadProcessMemory(hProc, (PVOID)addressToRead, &rpmBuffer, sizeof(dataType), 0);
    return rpmBuffer;
}

// Main Func
int main()
{
    DWORD memoryAddress = 0x0057FCD0;
    attachProc((char*)"NortonSecurity.exe");
    while(true)
    {
        wpm<int>(100, memoryAddress);
    }
}
