#ifndef _TCPSocket_H_
#define _TCPSocket_H_
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include "POSIXLib.h"
#define TCPSocket_RECV_FLAG 0
#define TCPSocket_SEND_FLAG 0
class TCPSocket
{
public:
    TCPSocket(unsigned short, unsigned = 16384);
    virtual ~TCPSocket();
    void InitialServer(void (*)(void *), void *, void (*)(void *), void *);
    void InitialClient(const char *, void (*)(void *), void *, void (*)(void *), void *);
    int TCPSocketWrite(const char *, int);
    int TCPSocketRead(char *, int);
    int TCPSocketReadLine(char *, int);
    bool RequestReconnect();
private:
    unsigned short m_Port;
    int m_ListenFd;
    int m_ConnFd;
    bool m_IsServer;
    char m_HostIP[128];
    bool m_InReconnect;
    Mutex m_Mutex;
    Sem *m_Sem;
    void (*m_BeforeReconnectFuncPtr)(void *);
    void (*m_AfterReconnectFuncPtr)(void *);
    void *m_BeforeReconnectFuncArg;
    void *m_AfterReconnectFuncArg;
    unsigned m_RemainWriteBound;
    pthread_t m_ReconnectTask;
    void Delay();
    void ProcessReconnect();
    static void *FuncProcessReconnect(void *);
};
#endif
