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
    FIFOType_t *mWritePtr;
    FIFOStd()
    {
        mData = NULL;
        mWritePtr = NULL;
        mReadPos = 0;
        mWritePos = 0;
        mSize = 0;
    }
    ~FIFOStd()
    {
        if(mData) {
            delete[] mData;
            mData = NULL;
        }
    }
    void ReSize(const unsigned int size)
    {
        int i;
        for(i = 1; i < 32; ++i) {
            if(size == (1 << i)) {
                break;
            }
        }
        if(i == 32) {
            puts("The size of FIFOStd is not 2^N or too big");
            exit(0);
        }
        assert(mData == NULL);
        mData = new FIFOType_t[size];
        assert(mData);
        mReadPos = 0;
        mWritePos = 0;
        mWritePtr = &mData[mWritePos];
        mSize = size;
    }
    void Clear()
    {
        mReadPos = 0;
        mWritePos = 0;
        if(mData == NULL) {
            mWritePtr = NULL;
        } else {
            mWritePtr = &mData[mWritePos];
        }
    }
    void Push()
    {
        unsigned int newWritePos = (mWritePos + 1) & (mSize - 1);
        if(newWritePos == mReadPos) {
            puts("FIFOStd Full!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            exit(0);
        }
        mWritePos = newWritePos;
        mWritePtr = &mData[mWritePos];
    }
    FIFOType_t *Pop()
    {
        FIFOType_t *result = &mData[mReadPos];
        mReadPos = (mReadPos + 1) & (mSize - 1);
        return result;
    }
    unsigned int GetLength()
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
