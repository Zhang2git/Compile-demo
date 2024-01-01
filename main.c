
#include <windows.h>
#include <stdio.h>
#include "software.h"
#include "hardware.h"

int main() 
{
    HANDLE hThread1;
    DWORD threadID1;

    int threadParam1 = 1;
    // 创建线程
    hThread1 = CreateThread(NULL, 0, ThreadFunction, &threadParam1, 0, &threadID1);

    while(1) {
        GenerateCmd();
        ReleaseCmd();
        Sleep(10);
    }

    // 等待线程结束
    WaitForSingleObject(hThread1, INFINITE);

    // 关闭线程句柄
    CloseHandle(hThread1);
    
    return 0;
}
