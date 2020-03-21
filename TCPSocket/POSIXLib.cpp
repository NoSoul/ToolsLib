#include "POSIXLib.h"

Mutex::Mutex(int pshared)
{
    int err;
    err = pthread_mutexattr_init(&m_Attr);
    assert(err == 0);
    err = pthread_mutexattr_setpshared(&m_Attr, pshared == 0 ? PTHREAD_PROCESS_PRIVATE : PTHREAD_PROCESS_SHARED);
    assert(err == 0);
    err = pthread_mutex_init(&m_Handle, &m_Attr);
    assert(err == 0);
}

Mutex::~Mutex()
{
    int err;
    err = pthread_mutex_destroy(&m_Handle);
    assert(err == 0);
    err = pthread_mutexattr_destroy(&m_Attr);
    assert(err == 0);
}

void Mutex::Lock()
{
    int err = pthread_mutex_lock(&m_Handle);
    assert(err == 0);
}

void Mutex::Unlock()
{
    int err = pthread_mutex_unlock(&m_Handle);
    assert(err == 0);
}

Sem::Sem(int pshared, unsigned value)
{
    int err = sem_init(&m_Handle, pshared, value);
    assert(err == 0);
}

Sem::~Sem()
{
    int err = sem_destroy(&m_Handle);
    assert(err == 0);
}

void Sem::Post()
{
    int err = sem_post(&m_Handle);
    assert(err == 0);
}

void Sem::Wait()
{
    int err = sem_wait(&m_Handle);
    assert(err == 0);
}

int Sem::TimedWait(long sec, long nsec)
{
    struct timespec waitDelay;
    waitDelay.tv_sec = sec;
    waitDelay.tv_nsec = nsec;
    return sem_timedwait(&m_Handle, &waitDelay);
}
