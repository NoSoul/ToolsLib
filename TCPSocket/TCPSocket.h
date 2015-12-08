#ifndef _TCPSocket_H_
#define _TCPSocket_H_
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#define TCPSocket_RECV_FLAG 0
#define TCPSocket_SEND_FLAG 0
class TCPSocket
{
public:
    TCPSocket(unsigned short);
    virtual ~TCPSocket();
    void InitialServer();
    void InitialClient(const char*);
    void ReconnTCPSocket();
    int  TCPSocketWrite(const char*, int);
    int  TCPSocketRead(char*, int);
    int  TCPSocketReadLine(char*, int);
private:
    unsigned short m_Port;
    int m_ListenFd;
    int m_ConnFd;
    bool m_Reconn;
};
#endif
