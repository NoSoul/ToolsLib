#include "TCPSocket.h"

TCPSocket::TCPSocket(unsigned short port, unsigned writeBound)
{
    m_Port = port;
    m_RemainWriteBound = writeBound;
    m_ListenFd = -1;
    m_ConnFd = -1;
    m_InReconnect = true;
    m_IsServer = true;
    m_BeforeReconnectFuncPtr = NULL;
    m_AfterReconnectFuncPtr = NULL;
    m_Sem = new Sem();
    sigset_t set;
    sigprocmask(SIG_SETMASK, NULL, &set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);
    pthread_create(&m_ReconnectTask, NULL, FuncProcessReconnect, this);
}

TCPSocket::~TCPSocket()
{
    pthread_cancel(m_ReconnectTask);
    pthread_join(m_ReconnectTask, NULL);
    delete m_Sem;
    shutdown(m_ConnFd, SHUT_RDWR);
}

void *TCPSocket::FuncProcessReconnect(void *arg)
{
    TCPSocket *pThis = (TCPSocket *)arg;
    pThis->ProcessReconnect();
    return arg;
}

void TCPSocket::InitialServer(void (*beforeFuncPtr)(void *), void *beforeFuncArg, void (*afterFuncPtr)(void *), void *afterFuncArg)
{
    m_BeforeReconnectFuncPtr = beforeFuncPtr;
    m_BeforeReconnectFuncArg = beforeFuncArg;
    m_AfterReconnectFuncPtr = afterFuncPtr;
    m_AfterReconnectFuncArg = afterFuncArg;
    m_IsServer = true;
    m_ListenFd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(m_ListenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(m_Port);
    bind(m_ListenFd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(m_ListenFd, 2);

    struct sockaddr_in cliaddr;
    socklen_t cliaddrLen = sizeof(cliaddr);
    puts("Accepting connections ...");
    m_ConnFd = accept(m_ListenFd, (struct sockaddr *)&cliaddr, &cliaddrLen);
    m_InReconnect = false;
    puts("Connected!");
}

void TCPSocket::InitialClient(const char *hostIP, void (*beforeFuncPtr)(void *), void *beforeFuncArg, void (*afterFuncPtr)(void *), void *afterFuncArg)
{
    m_BeforeReconnectFuncPtr = beforeFuncPtr;
    m_BeforeReconnectFuncArg = beforeFuncArg;
    m_AfterReconnectFuncPtr = afterFuncPtr;
    m_AfterReconnectFuncArg = afterFuncArg;
    m_IsServer = false;
    strcpy(m_HostIP, hostIP);
    m_ConnFd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(m_ConnFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, hostIP, &servaddr.sin_addr);
    servaddr.sin_port = htons(m_Port);
    puts("Request connections ...");
    while(connect(m_ConnFd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        Delay();
    }
    m_InReconnect = false;
    puts("Connected!");
}

int TCPSocket::TCPSocketWrite(const char *buffer, int size)
{
    int len = size;
    if(m_ConnFd == -1) {
        Delay();
        return 0;
    }
    while(~m_ConnFd && len > 0) {
        int nwrite = send(m_ConnFd, buffer, len, TCPSocket_SEND_FLAG);
        if(nwrite < 0) {
            if(errno == EINTR) {
                printf("%s ERROR %s!\n", __func__, strerror(errno));
                nwrite = 0;
            } else {
                if(RequestReconnect()) {
                    printf("%s ERROR %s!\n", __func__, strerror(errno));
                }
                Delay();
                return -1;
            }
        } else if(nwrite == 0) {
            printf("%s nwrite %d\n", __func__, nwrite);
        }
        len -= nwrite;
        buffer += nwrite;
    }
    unsigned remainLen;
    ioctl(m_ConnFd, SIOCOUTQ, &remainLen);
    if(remainLen >= m_RemainWriteBound) {
        if(RequestReconnect()) {
            printf("%s remainLen %u!\n", __func__, remainLen);
        }
    }
    return ~m_ConnFd ? size : 0;
}

int TCPSocket::TCPSocketRead(char *buffer, int size)
{
    int len = size;
    if(m_ConnFd == -1) {
        Delay();
        return 0;
    }
    while(~m_ConnFd && len > 0) {
        int nread = recv(m_ConnFd, buffer, len, TCPSocket_RECV_FLAG);
        if(nread == 0) {
            if(RequestReconnect()) {
                printf("%s broken pipe!\n", __func__);
            }
            Delay();
            return 0;
        } else if(nread < 0) {
            if(errno == EINTR) {
                printf("%s ERROR %s!\n", __func__, strerror(errno));
                nread = 0;
            } else {
                if(RequestReconnect()) {
                    printf("%s ERROR %s!\n", __func__, strerror(errno));
                }
                Delay();
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
    if(m_ConnFd == -1) {
        Delay();
        return 0;
    }
    while(~m_ConnFd) {
        int nread = recv(m_ConnFd, &data, 1, TCPSocket_RECV_FLAG);
        if(nread == 0) {
            if(RequestReconnect()) {
                printf("%s broken pipe!\n", __func__);
            }
            Delay();
            return 0;
        } else if(nread < 0) {
            if(errno == EINTR) {
                printf("%s ERROR %s!\n", __func__, strerror(errno));
                nread = 0;
            } else {
                if(RequestReconnect()) {
                    printf("%s ERROR %s!\n", __func__, strerror(errno));
                }
                Delay();
                return -1;
            }
        } else if(nread == 1) {
            buffer[len++] = data;
            if(data == '\n' || data == '\r') {
                break;
            }
            if(len == MaxReadLength) {
                printf("%s OverFlow, Skip Data!\n", __func__);
                RequestReconnect();
                return -1;
            }
        }
    }
    return len;
}

void TCPSocket::ProcessReconnect()
{
    while(1) {
        m_Sem->Wait();
        m_Mutex.Lock();
        m_InReconnect = true;
        m_Mutex.Unlock();
        shutdown(m_ConnFd, SHUT_RDWR);
        m_ConnFd = -1;
        shutdown(m_ListenFd, SHUT_RDWR);
        if(m_BeforeReconnectFuncPtr) {
            m_BeforeReconnectFuncPtr(m_BeforeReconnectFuncArg);
        }
        if(m_IsServer) {
            InitialServer(m_BeforeReconnectFuncPtr, m_BeforeReconnectFuncArg, m_AfterReconnectFuncPtr, m_AfterReconnectFuncArg);
        } else {
            char tempIP[256];
            strcpy(tempIP, m_HostIP);
            InitialClient(tempIP, m_BeforeReconnectFuncPtr, m_BeforeReconnectFuncArg, m_AfterReconnectFuncPtr, m_AfterReconnectFuncArg);
        }
        if(m_AfterReconnectFuncPtr) {
            m_AfterReconnectFuncPtr(m_AfterReconnectFuncArg);
        }
        delete m_Sem;
        m_Sem = new Sem();
    }
}

bool TCPSocket::RequestReconnect()
{
    bool ret = false;
    m_Mutex.Lock();
    if(!m_InReconnect) {
        m_Sem->Post();
        ret = true;
    }
    m_Mutex.Unlock();
    return ret;
}

void TCPSocket::Delay()
{
    usleep(1000);
}
