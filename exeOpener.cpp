#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include "main.h"

using namespace std;

// Global Variables
HANDLE hProc = NULL;
DWORD pID;

bool exeOpener::prompt()
{
    PROCESSENTRY32 procEntry32;
    procEntry32.dwSize = sizeof(PROCESSENTRY32);
    auto hProcSnap = CreateToolHelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    
    if(hProcSnap == INVALID_HANDLE_VALUE)
    {
        cout<<"Failed to take Snapshot during the Process."<<endl;
        return false;
    }
    
    while(Process32Next(hProc, &procEntry32))
    {
        cout<<procName, procEntry32.szExeFile<<endl;
    }
}
