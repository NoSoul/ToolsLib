#include "TCPSocket.h"
#include <pthread.h>

TCPSocket *SocketHandle;

void *Recv(void *arg)
{
    int MsgLen;
    char ReceiveBuffer[1024];
    while((MsgLen = SocketHandle->TCPSocketRead(ReceiveBuffer, 11)) != -1)
    {
        printf("Client Recv<%d>: %s\n", MsgLen, ReceiveBuffer);
    }
    return NULL;
}

void *Send(void *arg)
{
    pthread_detach(pthread_self());
    int MsgLen;
    while((MsgLen = SocketHandle->TCPSocketWrite("I'm Client!\n", 12)) != -1)
    {
        sleep(1);
    }
    return NULL;
}

int main()
{
    SocketHandle = TCPSocket::GetInstance();
    SocketHandle->InitialClient("127.0.0.1");
    pthread_t recv, send;
    pthread_create(&recv, NULL, Recv, NULL);
    pthread_create(&send, NULL, Send, NULL);
    pthread_join(recv, NULL);
    return 0;
}
