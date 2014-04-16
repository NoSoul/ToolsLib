#include "TCPSocket.h"
#include <pthread.h>

TCPSocket *SocketHandle;

void *Recv(void *arg)
{
	char ReceiveBuffer[1024];
	while(1)
	{
		int MsgLen = SocketHandle->TCPSocketRead(ReceiveBuffer, 11);
		if(MsgLen == -1)
		{
			break;
		}
		printf("Client Receive<%d>: %s\n", MsgLen, ReceiveBuffer);
	}
	return NULL;
}

void *Send(void *arg)
{
	pthread_detach(pthread_self());
	while(1)
	{
        int MsgLen = SocketHandle->TCPSocketWrite("I'm Client!\n", 12);
        if(MsgLen == -1)
        {
            break;
        }
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
