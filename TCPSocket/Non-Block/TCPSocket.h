#ifndef _TCPSocket_H_
#define _TCPSocket_H_
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
class TCPSocket
{
public:
    TCPSocket(unsigned short, int, int);
    virtual ~TCPSocket();
    void InitialServer();
    void InitialClient(const char*);
    void ReconnTCPSocket();
    int  TCPSocketWrite(const char*, int);
    int  TCPSocketRead(char*, int);
    int  TCPSocketReadLine(char*, int);
private:
    unsigned short m_Port;
    int m_RecvFlag;
    int m_SendFlag;
    int m_ListenFd;
    int m_ConnFd;
    bool m_BrokenPipe;
    struct sockaddr_in m_ServerAddr;
    pthread_t m_WaitTask;

    void WaitClient();
    void WaitServer();
    static void *WaitClientFunc(void*);
    static void *WaitServerFunc(void*);
};
#endif
