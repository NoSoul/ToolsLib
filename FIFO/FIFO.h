#ifndef _FIFO_H_
#define _FIFO_H_
#include <stdio.h>
#include <assert.h>
#include <string.h>
template <typename FIFOType_t>
class FIFO
{
public:
    FIFO()
    {
        mData = NULL;
        mReadPos = 0;
        mWritePos = 0;
        mSize = 0;
        mCount = 0;
    }
    ~FIFO()
    {
        if(mData)
        {
            delete[] mData;
            mData = NULL;
        }
    }
    void ReSize(const int size)
    {
        if(mData)
        {
            delete[] mData;
            mData = NULL;
        }
        mData = new FIFOType_t[size];
        assert(mData);
        mReadPos = 0;
        mWritePos = 0;
        mSize = size;
        mCount = 0;
    }
    FIFO &operator=(const FIFO &source)
    {
        if(mData)
        {
            delete[] mData;
            mData = NULL;
        }
        mData = new FIFOType_t[source.mSize];
        memcpy(mData, source.mData, sizeof(FIFOType_t)*source.mSize);
        assert(mData);
        mReadPos = source.mReadPos;
        mWritePos = source.mWritePos;
        mSize = source.mSize;
        mCount = source.mCount;
        return *this;
    }
    void Clear()
    {
        mReadPos = 0;
        mWritePos = 0;
        mCount = 0;
    }
    void Push(const FIFOType_t& value)
    {
        mData[mWritePos] = value;
        ++mWritePos;
        ++mCount;
        if(mWritePos == mSize)
        {
            mWritePos = 0;
        }
        if(mCount >= mSize)
        {
            mCount = mSize;
            mReadPos = mWritePos;
        }
    }
    FIFOType_t Pop()
    {
        assert(mCount > 0);
        FIFOType_t result = mData[mReadPos];
        ++mReadPos;
        --mCount;
        if(mReadPos == mSize)
        {
            mReadPos = 0;
        }
        return result;
    }
    bool Exist(const FIFOType_t& value)
    {
        for(int curr = mReadPos, i = 0; i < mCount; ++i)
        {
            if(mData[curr] == value)
            {
                return true;
            }
            if(++curr == mSize)
            {
                curr = 0;
            }
        }
        return false;
    }
    bool Empty() {
        return mCount == 0;
    }
    int GetLength() {
        return mCount;
    }
    FIFOType_t GetAvgValue()
    {
        FIFOType_t Sum(0);
        for(int curr = mReadPos, i = 0; i < mCount; ++i)
        {
            Sum += mData[curr];
            if(++curr == mSize)
            {
                curr = 0;
            }
        }
        return Sum / mCount;
    }
    FIFOType_t GetMaxValue()
    {
        assert(mCount);
        FIFOType_t ans = mData[mReadPos];
        for(int curr = mReadPos, i = 0; i < mCount; ++i)
        {
            if(mData[curr] > ans)
            {
                ans = mData[curr];
            }
            if(++curr == mSize)
            {
                curr = 0;
            }
        }
        return ans;
    }
    FIFOType_t GetMinValue()
    {
        assert(mCount);
        FIFOType_t ans = mData[mReadPos];
        for(int curr = mReadPos, i = 0; i < mCount; ++i)
        {
            if(mData[curr] < ans)
            {
                ans = mData[curr];
            }
            if(++curr == mSize)
            {
                curr = 0;
            }
        }
        return ans;
    }
private:
    FIFOType_t *mData;
    int mReadPos;
    int mWritePos;
    int mSize;
    int mCount;
};
#endif
