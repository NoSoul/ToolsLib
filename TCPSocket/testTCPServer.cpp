#include "TCPSocket.h"
#include <pthread.h>

TCPSocket *SocketHandle;

void *Recv(void *arg)
{
    int MsgLen;
    char ReceiveBuffer[1024];
    while(1)
    {
        while((MsgLen = SocketHandle->TCPSocketReadLine(ReceiveBuffer, 1024)) != -1)
        {
            printf("Server Recv<%d>: %s", MsgLen, ReceiveBuffer);
        }
        SocketHandle->ReconnTCPSocket();
    }
    return NULL;
}

void *Send(void *arg)
{
    pthread_detach(pthread_self());
    int MsgLen;
    while(1)
    {
        while((MsgLen = SocketHandle->TCPSocketWrite("I'm Server!", 11)) != -1)
        {
            sleep(1);
        }
        SocketHandle->ReconnTCPSocket();
    }
    return NULL;
}

int main()
{
    SocketHandle = TCPSocket::GetInstance();
    SocketHandle->InitialServer();
    pthread_t recv, send;
    pthread_create(&recv, NULL, Recv, NULL);
    pthread_create(&send, NULL, Send, NULL);
    pthread_join(recv, NULL);
    return 0;
}
