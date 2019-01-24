#include "TCPSocket.h"

TCPSocket::TCPSocket(unsigned short port, int recvFlag, int sendFlag)
{
    m_Port = port;
    m_RecvFlag = recvFlag;
    m_SendFlag = sendFlag;
    m_ListenFd = -1;
    m_ConnFd = -1;
    m_BrokenPipe = false;
    sigset_t set;
    sigprocmask(SIG_SETMASK, NULL, &set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

TCPSocket::~TCPSocket()
{
    pthread_cancel(m_WaitTask);
    pthread_join(m_WaitTask, NULL);
    if(~m_ConnFd) {
        close(m_ConnFd);
        m_ConnFd = -1;
    }
}

void TCPSocket::InitialServer()
{
    m_ListenFd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&m_ServerAddr, 0, sizeof(m_ServerAddr));
    m_ServerAddr.sin_family = AF_INET;
    m_ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_ServerAddr.sin_port = htons(m_Port);
    bind(m_ListenFd, (struct sockaddr *)&m_ServerAddr, sizeof(m_ServerAddr));
    listen(m_ListenFd, 1);
    int flags = fcntl(m_ListenFd, F_GETFL, 0);
    fcntl(m_ListenFd, F_SETFL, flags | O_NONBLOCK);
    pthread_create(&m_WaitTask, NULL, WaitClientFunc, this);
}

void *TCPSocket::WaitClientFunc(void *arg)
{
    ((TCPSocket*)arg)->WaitClient();
    return arg;
}

void TCPSocket::WaitClient()
{
    while(1) {
        fd_set readFS;
        FD_ZERO(&readFS);
        FD_SET(m_ListenFd, &readFS);
        puts("TCPSocket: Accepting connections ...");
        select(FD_SETSIZE, &readFS, NULL, NULL, NULL);
        if(FD_ISSET(m_ListenFd, &readFS)) {
            puts("TCPSocket: Try accept ...");
            m_ConnFd = accept(m_ListenFd, NULL, NULL);
            puts("TCPSocket: Connected!");
        }
    }
}

void TCPSocket::InitialClient(const char *hostIP)
{
    m_ConnFd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&m_ServerAddr, 0, sizeof(m_ServerAddr));
    m_ServerAddr.sin_family = AF_INET;
    inet_pton(AF_INET, hostIP, &m_ServerAddr.sin_addr);
    m_ServerAddr.sin_port = htons(m_Port);
    int flags = fcntl(m_ConnFd, F_GETFL, 0);
    fcntl(m_ConnFd, F_SETFL, flags | O_NONBLOCK);
    pthread_create(&m_WaitTask, NULL, WaitServerFunc, this);
}

void *TCPSocket::WaitServerFunc(void *arg)
{
    ((TCPSocket*)arg)->WaitServer();
    return arg;
}

void TCPSocket::WaitServer()
{
    while(1) {
        puts("TCPSocket: Request connections ...");
        while(connect(m_ConnFd, (struct sockaddr*)&m_ServerAddr, sizeof(m_ServerAddr)) != 0) {
            usleep(1000);
        }
        puts("TCPSocket: Connected!");
    }
}

int TCPSocket::TCPSocketWrite(const char *buffer, int size)
{
    int len = size;
    while(len > 0) {
        fd_set writeFS;
        FD_ZERO(&writeFS);
        FD_SET(m_ConnFd, &writeFS);
        select(FD_SETSIZE, NULL, &writeFS, NULL, NULL);
        if(FD_ISSET(m_ConnFd, &writeFS)) {
            int nwrite = send(m_ConnFd, buffer, len, m_SendFlag);
            if(nwrite < 0) {
                if(errno == EINTR) {
                    nwrite = 0;
                    puts("TCPSocket: send EINTR");
                } else {
                    //puts("TCPSocket: send ERROR!");
                    return  -1;
                }
            }
            len -= nwrite;
            buffer += nwrite;
        } else {
            puts("TCPSocket: send fail!");
            return 0;
        }
    }
    return size;
}

int TCPSocket::TCPSocketRead(char *buffer, int size)
{
    int len = size;
    while(len > 0) {
        fd_set readFS;
        FD_ZERO(&readFS);
        FD_SET(m_ConnFd, &readFS);
        select(FD_SETSIZE, &readFS, NULL, NULL, NULL);
        if(FD_ISSET(m_ConnFd, &readFS)) {
            int nread = recv(m_ConnFd, buffer, len, m_RecvFlag);
            if(nread == 0) {
                if(!m_BrokenPipe) {
                    m_BrokenPipe = true;
                    puts("TCPSocket: broken pipe!");
                }
                return 0;
            }
            if(nread < 0) {
                if(errno == EINTR) {
                    nread = 0;
                    puts("TCPSocket: recv EINTR");
                } else {
                    //puts("TCPSocket: recv ERROR!");
                    return -1;
                }
            }
            m_BrokenPipe = false;
            len -= nread;
            buffer += nread;
        } else {
            puts("TCPSocket: recv fail!");
            return 0;
        }
    }
    if(len == 0) {
        return size;
    }
    return 0;
}

int TCPSocket::TCPSocketReadLine(char *buffer, int MaxReadLength)
{
    int len = 0;
    char data;
    while(1) {
        fd_set readFS;
        FD_ZERO(&readFS);
        FD_SET(m_ConnFd, &readFS);
        select(FD_SETSIZE, &readFS, NULL, NULL, NULL);
        if(FD_ISSET(m_ConnFd, &readFS)) {
            int nread = recv(m_ConnFd, &data, 1, m_RecvFlag);
            if(nread == 0) {
                if(!m_BrokenPipe) {
                    m_BrokenPipe = true;
                    puts("TCPSocket: broken pipe!");
                }
                return 0;
            }
            if(nread < 0) {
                if(errno == EINTR) {
                    nread = 0;
                    puts("TCPSocket: recv EINTR");
                } else {
                    //puts("TCPSocket: recv ERROR!");
                    return -1;
                }
            }
            if(nread == 1) {
                m_BrokenPipe = false;
                buffer[len++] = data;
                if(data == '\n' || data == '\r') {
                    break;
                }
                if(len == MaxReadLength) {
                    puts("TCPSocket: recv OverFlow, Skip Data!");
                    return -1;
                }
            }
        } else {
            puts("TCPSocket: recv fail!");
            return 0;
        }
    }
    return len;
}
