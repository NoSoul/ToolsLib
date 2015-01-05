#ifndef _FIFOStd_H_
#define _FIFOStd_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
template <typename FIFOType_t>
class FIFOStd
{
public:
    FIFOStd()
    {
        mData = NULL;
        mReadPos = 0;
        mWritePos = 0;
        mSize = 0;
    }
    ~FIFOStd()
    {
        if(mData)
        {
            delete[] mData;
            mData = NULL;
        }
    }
    void ReSize(const unsigned int size)
    {
        int i;
        for(i = 1; i < 32; ++i)
        {
            if(size == (1 << i))
            {
                break;
                
            }
        }
        if(i == 32)
        {
            puts("The size of FIFOStd is not 2^N or too big");
            exit(0);
        }
        assert(mData == NULL);
        mData = new FIFOType_t[size];
        assert(mData);
        mReadPos = 0;
        mWritePos = 0;
        mSize = size;
    }
    FIFOStd &operator=(const FIFOStd &source)
    {
        if(this != &source)
        {
            if(mData)
            {
                delete[] mData;
                mData = NULL;
            }
            mData = new FIFOType_t[source.mSize];
            assert(mData);
            memcpy(mData, source.mData, sizeof(FIFOType_t)*source.mSize);
            mReadPos = source.mReadPos;
            mWritePos = source.mWritePos;
            mSize = source.mSize;
        }
        return *this;
    }
    void Clear()
    {
        mReadPos = 0;
        mWritePos = 0;
    }
    void Push(const FIFOType_t& value)
    {
        unsigned int newWritePos = (mWritePos + 1) & (mSize - 1);
        if(newWritePos == mReadPos)
        {
            puts("FIFOStd Full!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            exit(0);
        }
        mData[mWritePos] = value;
        mWritePos = newWritePos;
    }
    FIFOType_t Pop()
    {
        FIFOType_t result = mData[mReadPos];
        mReadPos = (mReadPos + 1) & (mSize - 1);
        return result;
    }
    int GetLength()
    {
        return (mWritePos + mSize - mReadPos) & (mSize - 1);
    }
protected:
    FIFOType_t *mData;
    unsigned int mReadPos;
    unsigned int mWritePos;
    unsigned int mSize;
};
#endif
