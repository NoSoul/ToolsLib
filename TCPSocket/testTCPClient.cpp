#include "TCPSocket.h"
#include <pthread.h>

TCPSocket *SocketHandle;

void *Recv(void *arg)
{
    int msgLen;
    char ReceiveBuffer[1024] = {0};
    while(1) {
        msgLen = SocketHandle->TCPSocketRead(ReceiveBuffer, 11);
        if(msgLen > 0) {
            printf("Client Recv<%d>: %s\n", msgLen, ReceiveBuffer);
        }
    }
    return arg;
}

void *Send(void *arg)
{
    while(1) {
        SocketHandle->TCPSocketWrite("I'm Client!\n", 12);
        sleep(1);
    }
    return arg;
}

int main()
{
    SocketHandle = new TCPSocket(7777);
    SocketHandle->InitialClient("127.0.0.1", NULL, NULL, NULL, NULL);
    pthread_t recv, send;
    pthread_create(&recv, NULL, Recv, NULL);
    pthread_create(&send, NULL, Send, NULL);
    while(1) {
        char cmd = getchar();
        if(cmd == 'q') {
            break;
        }
    }
    pthread_cancel(send);
    pthread_cancel(recv);
    pthread_join(send, NULL);
    pthread_join(recv, NULL);
    delete SocketHandle;
    return 0;
}
