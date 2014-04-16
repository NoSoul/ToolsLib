#ifndef _TCPSocket_H_
#define _TCPSocket_H_
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#define TCPSocket_RECV_FLAG 0
#define TCPSocket_SEND_FLAG 0
#define Socket_SERV_PORT	7777
class TCPSocket
{
	public:	
		static TCPSocket *GetInstance();
		void InitialServer();
		void InitialClient(const char *);
		int  TCPSocketWrite(const char *, int );
		int  TCPSocketRead(char *, int );
        int  TCPSocketReadLine(char *, int );
	private:
		int connfd;
		static TCPSocket *Socket_instance;
		TCPSocket();
		virtual ~TCPSocket();
};
#endif
