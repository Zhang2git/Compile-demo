#include <windows.h>
#include <stdio.h>

#include "fifo.h"

static struct Queue g_CmdQueue = {
    .count = 0,
    .front = NULL,
    .rear = NULL,
};

static struct Queue g_RspQueue = {
    .count = 0,
    .front = NULL,
    .rear = NULL,
};

void CmdEnqueue(struct timeval data)
{
    struct Nodes *temp_node = (struct Nodes *)malloc(sizeof(struct Nodes));
    temp_node->data = data;
    temp_node->next_node = NULL;

    if (g_CmdQueue.count == 0) {
        g_CmdQueue.front = g_CmdQueue.rear = temp_node;
    } else {
        g_CmdQueue.rear->next_node = temp_node;
        g_CmdQueue.rear = temp_node;
    }

    g_CmdQueue.count++;
}

struct timeval CmdDequeue(void)
{
    struct Nodes *temp_node = g_CmdQueue.front;
    struct timeval data = g_CmdQueue.front->data;
    if(g_CmdQueue.count > 0) {
        g_CmdQueue.front = g_CmdQueue.front->next_node;
    }

    free(temp_node);
    g_CmdQueue.count--;
    return data;
}

struct Nodes *CmdQueueNodeGet(void) 
{
    return g_CmdQueue.front;
}

bool IsCmdQueueFull(void)
{
    if (g_CmdQueue.count == 100) {
        return true;
    }
    return false;
}

bool IsCmdQueueEmpty(void)
{
    if (g_CmdQueue.count == 0) {
        return true;
    }
    return false;    
}

void RespEnqueue(struct timeval data)
{
    struct Nodes *temp_node = (struct Nodes *)malloc(sizeof(struct Nodes));
    temp_node->data = data;
    temp_node->next_node = NULL;

    if (g_RspQueue.count == 0) {
        g_RspQueue.front = g_RspQueue.rear = temp_node;
    } else {
        g_RspQueue.rear->next_node = temp_node;
        g_RspQueue.rear = temp_node;
    }

    g_RspQueue.count++;
}

struct timeval RespDequeue(void)
{
    struct Nodes *temp_node = g_RspQueue.front;
    struct timeval data = g_RspQueue.front->data;
    if(g_RspQueue.count > 0) {
        g_RspQueue.front = g_RspQueue.front->next_node;
    }

    free(temp_node);
    g_RspQueue.count--;
    return data;
}

struct Nodes *RespQueueNodeGet(void) {
    return g_RspQueue.front;
}

bool IsRespQueueFull(void)
{
    if (g_RspQueue.count == 100) {
        return true;
    }
    return false;
}

bool IsRespQueueEmpty(void)
{
    if (g_RspQueue.count == 0) {
        return true;
    }
    return false;    
}