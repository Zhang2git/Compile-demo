#include <windows.h>
#include <stdio.h>
#include "fifo.h"

CRITICAL_SECTION cs; // 互斥锁
struct timeval g_TempTime = {0};
static int g_CmdCnt = 0;

int HardWareExcution(struct Nodes *cmd_node)
{
    if (cmd_node == NULL) {
        printf("[HardWareExcution]: error\n");
        return -1;
    }

    gettimeofday(&g_TempTime, NULL);
    long time_ms_now = g_TempTime.tv_sec * 1000 + g_TempTime.tv_usec / 1000;
    long time_ms_past = cmd_node->data.tv_sec * 1000 + cmd_node->data.tv_usec / 1000; 
    if ((time_ms_now - time_ms_past) < 1000) {
        
        return 0;
    }
    printf("cmd %d handled\n", g_CmdCnt);
    g_CmdCnt++;
    return 1;
}

// 线程函数
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    int ret = 0;
    struct Nodes *cmd_node = NULL;
    while (1) {
        EnterCriticalSection(&cs);
        if (!IsCmdQueueEmpty()) {
            cmd_node = CmdQueueNodeGet();
            ret = HardWareExcution(cmd_node);
            if (ret == 1) {
                RspEnqueue(cmd_node->data);
            }
        }
        LeaveCriticalSection(&cs);
        Sleep(10);
    }
}



