#include "TCPSocket.h"
#include <pthread.h>

TCPSocket *SocketHandle;

void *Recv(void *arg)
{
    int msgLen;
    char recvBuffer[1024];
    while(1) {
        msgLen = SocketHandle->TCPSocketRead(recvBuffer, 11);
        if(msgLen > 0) {

            printf("Client Recv<%d>: %s\n", msgLen, recvBuffer);
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
        msgLen = SocketHandle->TCPSocketWrite("I'm Client!\n", 12);
        printf("Client Send %d\n", msgLen);
        sleep(1);
    }
    return arg;
}

int main()
{
    SocketHandle = new TCPSocket(7777, 0, 0);
    SocketHandle->InitialClient("192.168.1.120");
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
    pthread_cancel(send);
    pthread_join(recv, NULL);
    pthread_join(send, NULL);
    delete SocketHandle;
    return 0;
}
