#include <windows.h>
#include <stdio.h>
#include "fifo.h"

int ReleaseCmd(void)
{
    if (IsRspQueueEmpty()) {
        return 0;
    }
    RspDequeue();
    CmdDequeue();
    return 0;
}

int GenerateCmd()
{
    if (IsCmdQueueFull()) {
        return 0;
    }

    struct timeval time_now = {0};
    gettimeofday(&time_now, NULL);
    CmdEnqueue(time_now);
    return 1;
}

