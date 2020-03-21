#ifndef _POSIXLib_H_
#define _POSIXLib_H_
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
class Mutex
{
public:
    Mutex(int = 0);
    ~Mutex();
    void Lock();
    void Unlock();
private:
    pthread_mutex_t m_Handle;
    pthread_mutexattr_t m_Attr;
};
class Sem
{
public:
    Sem(int = 0, unsigned = 0);
    ~Sem();
    void Post();
    void Wait();
    int TimedWait(long, long);
private:
    sem_t m_Handle;
};
#endif
