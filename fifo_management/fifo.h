#include <stdbool.h>

struct Nodes
{
    /* data */
    struct timeval data;
    struct Nodes *next_node;
};

struct Queue 
{
    int count;
    struct Nodes *front;
    struct Nodes *rear;
};

void CmdEnqueue(struct timeval data);
struct timeval CmdDequeue(void);
struct Nodes *CmdQueueNodeGet(void);
bool IsCmdQueueFull(void);
bool IsCmdQueueEmpty(void);

void RspEnqueue(struct timeval data);
struct timeval RspDequeue(void);
struct Nodes *RspQueueNodeGet(void);
bool IsRspQueueFull(void);
bool IsRspQueueEmpty(void);
