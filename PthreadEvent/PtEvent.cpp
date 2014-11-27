#include "PtEvent.h"
#include <assert.h>

static int Error;

PtEvent::PtEvent(const int size)
{
    mFlag = new bool[size];
    assert(mFlag);
    mSize = size;
    mRecv = 0;
    for(int i = 0; i < mSize; ++i)
    {
        mFlag[i] = false;
    }
    Error = pthread_mutex_init(&mCondHandle.mMutex, NULL);
    assert(Error == 0);
    Error = pthread_cond_init(&mCondHandle.mCond, NULL);
    assert(Error == 0);
}

PtEvent::~PtEvent()
{
    pthread_cond_destroy(&mCondHandle.mCond);
    pthread_mutex_destroy(&mCondHandle.mMutex);
    delete[] mFlag;
}

void PtEvent::Set(const int index)
{
    assert(index < mSize);
    Error = pthread_mutex_lock(&mCondHandle.mMutex);
    assert(Error == 0);
    mFlag[index] = true;
    mRecv = 0;
    for(int i = 0; i < mSize; ++i)
    {
        mRecv += mFlag[i] ? 1 : 0;
    }
    Error = pthread_cond_signal(&mCondHandle.mCond);
    assert(Error == 0);
    Error = pthread_mutex_unlock(&mCondHandle.mMutex);
    assert(Error == 0);
}

void PtEvent::SetAll()
{
    Error = pthread_mutex_lock(&mCondHandle.mMutex);
    assert(Error == 0);
    for(int i = 0; i < mSize; ++i)
    {
        mFlag[i] = true;
    }
    mRecv = mSize;
    Error = pthread_cond_signal(&mCondHandle.mCond);
    assert(Error == 0);
    Error = pthread_mutex_unlock(&mCondHandle.mMutex);
    assert(Error == 0);

}

void PtEvent::Reset(const int index)
{
    assert(index < mSize);
    Error = pthread_mutex_lock(&mCondHandle.mMutex);
    assert(Error == 0);
    mFlag[index] = false;
    mRecv = 0;
    for(int i = 0; i < mSize; ++i)
    {
        mRecv += mFlag[i] ? 1 : 0;
    }
    Error = pthread_mutex_unlock(&mCondHandle.mMutex);
    assert(Error == 0);
}

void PtEvent::ResetAll()
{
    Error = pthread_mutex_lock(&mCondHandle.mMutex);
    assert(Error == 0);
    for(int i = 0; i < mSize; ++i)
    {
        mFlag[i] = false;
    }
    mRecv = 0;
    Error = pthread_mutex_unlock(&mCondHandle.mMutex);
    assert(Error == 0);
}

void PtEvent::WaitOnce(const int index)
{
    assert(index < mSize);
    Error = pthread_mutex_lock(&mCondHandle.mMutex);
    assert(Error == 0);
    while(!mFlag[index])
    {
        pthread_cond_wait(&mCondHandle.mCond, &mCondHandle.mMutex);
    }
    Error = pthread_mutex_unlock(&mCondHandle.mMutex);
    assert(Error == 0);
}

void PtEvent::Wait(const int index)
{
    WaitOnce(index);
    Reset(index);
}

void PtEvent::WaitAll()
{
    Error = pthread_mutex_lock(&mCondHandle.mMutex);
    assert(Error == 0);
    while(mRecv != mSize)
    {
        pthread_cond_wait(&mCondHandle.mCond, &mCondHandle.mMutex);
    }
    Error = pthread_mutex_unlock(&mCondHandle.mMutex);
    assert(Error == 0);
    ResetAll();
}

int PtEvent::WaitAnyOnce()
{
    Error = pthread_mutex_lock(&mCondHandle.mMutex);
    assert(Error == 0);
    int result = -1;
    while(!mRecv)
    {
        pthread_cond_wait(&mCondHandle.mCond, &mCondHandle.mMutex);
    }
    for(int i = 0; i < mSize; ++i)
    {
        if(mFlag[i] == true)
        {
            Error = pthread_mutex_unlock(&mCondHandle.mMutex);
            assert(Error == 0);
            result = i;
            break;
        }
    }
    assert(result != -1);
    return result;
}

int PtEvent::WaitAny()
{
    int result = WaitAnyOnce();
    Reset(result);
    return result;
}
