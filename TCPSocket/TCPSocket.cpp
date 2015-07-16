#include "TCPSocket.h"

TCPSocket::TCPSocket()
{
    connfd = -1;
    reconn = false;
    sigset_t set;
    sigprocmask(SIG_SETMASK, NULL, &set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

TCPSocket::~TCPSocket()
{
    shutdown(connfd, SHUT_RDWR);
}

TCPSocket* TCPSocket::GetInstance()
{
    static TCPSocket socketInstance;
    return (&socketInstance);
}

void TCPSocket::InitialServer()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(Socket_SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 20);

    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);
    puts("Accepting connections ...");
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    puts("Connected!");
}

void TCPSocket::InitialClient(const char *hostIP)
{
    connfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(connfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, hostIP, &servaddr.sin_addr);
    servaddr.sin_port = htons(Socket_SERV_PORT);

    puts("Request connections ...");
    while(connect(connfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0);
    puts("Connected!");
}

void TCPSocket::ReconnTCPSocket()
{
    if(reconn == false) {
        reconn = true;
        shutdown(connfd, SHUT_RDWR);
        shutdown(listenfd, SHUT_RDWR);
        InitialServer();
        reconn = false;
    }
}

int TCPSocket::TCPSocketWrite(const char *buffer, int size)
{
    int len = size;
    while(len > 0) {
        int nwrite = send(connfd, buffer, len, TCPSocket_SEND_FLAG);
        if(nwrite <= 0) {
            if(nwrite < 0 && errno == EINTR) {
                nwrite = 0;
            } else {
                puts("TCPSocket Send Error!");
                return  -1;
            }
        }
        len -= nwrite;
        buffer += nwrite;
    }
    return size;
}

int TCPSocket::TCPSocketRead(char *buffer, int size)
{
    int len = size;
    while(len > 0) {
        int nread = recv(connfd, buffer, len, TCPSocket_RECV_FLAG);
        if(nread < 0) {
            if(errno == EINTR) {
                nread = 0;
            } else {
                puts("TCPSocket Recv Error!");
                return -1;
            }
        }
        len -= nread;
        buffer += nread;
    }
    return size;
}

int TCPSocket::TCPSocketReadLine(char *buffer, int MaxReadLength)
{
    int len = 0;
    char data;
    while(1) {
        int nread = recv(connfd, &data, 1, TCPSocket_RECV_FLAG);
        if(nread < 0) {
            if(errno == EINTR) {
                nread = 0;
            } else {
                puts("TCPSocket RecvLine Error!");
                return -1;
            }
        }
        if(nread == 1) {
            buffer[len++] = data;
            if(data == '\n' || data == '\r') {
                break;
            }
            if(len == MaxReadLength) {
                puts("TCPSocket RecvLine OverFlow, Skip Data!");
                return -1;
            }
        }
    }
    return len;
}
