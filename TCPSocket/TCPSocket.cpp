#include "TCPSocket.h"

TCPSocket::TCPSocket(unsigned short port)
{
    m_Port = port;
    m_ListenFd = -1;
    m_ConnFd = -1;
    m_Reconn = false;
    sigset_t set;
    sigprocmask(SIG_SETMASK, NULL, &set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

TCPSocket::~TCPSocket()
{
    shutdown(m_ConnFd, SHUT_RDWR);
}

void TCPSocket::InitialServer()
{
    m_ListenFd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(m_ListenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(m_Port);

    bind(m_ListenFd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(m_ListenFd, 20);

    struct sockaddr_in cliaddr;
    socklen_t cliaddrLen = sizeof(cliaddr);
    puts("Accepting connections ...");
    m_ConnFd = accept(m_ListenFd, (struct sockaddr *)&cliaddr, &cliaddrLen);
    puts("Connected!");
}

void TCPSocket::InitialClient(const char *hostIP)
{
    m_ConnFd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(m_ConnFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, hostIP, &servaddr.sin_addr);
    servaddr.sin_port = htons(m_Port);

    puts("Request connections ...");
    while(connect(m_ConnFd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0);
    puts("Connected!");
}

void TCPSocket::ReconnTCPSocket()
{
    if(m_Reconn == false) {
        m_Reconn = true;
        shutdown(m_ConnFd, SHUT_RDWR);
        shutdown(m_ListenFd, SHUT_RDWR);
        InitialServer();
        m_Reconn = false;
    }
}

int TCPSocket::TCPSocketWrite(const char *buffer, int size)
{
    int len = size;
    while(len > 0) {
        int nwrite = send(m_ConnFd, buffer, len, TCPSocket_SEND_FLAG);
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
        int nread = recv(m_ConnFd, buffer, len, TCPSocket_RECV_FLAG);
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
        int nread = recv(m_ConnFd, &data, 1, TCPSocket_RECV_FLAG);
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
