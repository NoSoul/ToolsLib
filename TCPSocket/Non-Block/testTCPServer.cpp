#include "TCPSocket.h"
#include <pthread.h>

TCPSocket *SocketHandle;

void *Recv(void *arg)
{
    int msgLen;
    char recvBuffer[1024];
    while(1) {
        msgLen = SocketHandle->TCPSocketReadLine(recvBuffer, 1024);
        if(msgLen > 0) {
            printf("Server Recv<%d>: %s", msgLen, recvBuffer);
        }
        if(msgLen <= 0) {
            sleep(1);
        }
    }
    return arg;
}

void *Send(void *arg)
{
    int msgLen;
    while(1) {
        msgLen = SocketHandle->TCPSocketWrite("I'm Server!", 11);
        printf("Server Send %d\n", msgLen);
        sleep(1);
    }
    return arg;
}

int main()
{
    SocketHandle = new TCPSocket(7777, 0, 0);
    SocketHandle->InitialServer();
    pthread_t recv, send;
    pthread_create(&recv, NULL, Recv, NULL);
    pthread_create(&send, NULL, Send, NULL);
    while(1) {
        char cmd = getchar();
        if(cmd == 'q') {
            break;
        }
    }
    pthread_cancel(recv);
    pthread_join(recv, NULL);
    pthread_cancel(send);
    pthread_join(send, NULL);
    delete SocketHandle;
    return 0;
}
