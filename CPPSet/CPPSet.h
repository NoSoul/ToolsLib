#ifndef _CPPSet_H_
#define _CPPSet_H_
#include <stdio.h>
#include <string.h>
#define CPP_SET_ADD_VALUE   50
template <typename KEY_t>
class CPPSet
{
    private:
        KEY_t *mKey;
        unsigned int mCapacity;
        unsigned int mSize;
    public:
        CPPSet()
        {
            mSize = 0;
            mCapacity = 0;
            mKey = NULL;
        }
        ~CPPSet()
        {
            if(mKey)
            {
                delete[] mKey;
            }
        }
        unsigned int size()
        {
            return mSize;
        }
        void insert(const KEY_t& x)
        {
            if(find(x) == NULL)
            {
                if(mSize+1 >= mCapacity)
                {
                    KEY_t *key_mem = new KEY_t[mCapacity+CPP_SET_ADD_VALUE];
                    int i;
                    for(i=0; i<mSize; ++i)
                    {
                        if(mKey[i] < x)
                        {
                            key_mem[i] = mKey[i];
                        }
                        else
                        {
                            break;
                        }
                    }
                    key_mem[i] = x;
                    for(; i<mSize; ++i)
                    {
                        key_mem[i+1] = mKey[i];
                    }
                    ++mSize;
                    if(mKey)
                    {
                        delete[] mKey;
                    }
                    mKey = key_mem;
                    mCapacity += CPP_SET_ADD_VALUE;
                }
                else
                {
                    int Left, Right, Mid;
                    Left = 0;
                    Right = mSize-1;
                    while(Left < Right)
                    {
                        Mid = (Left+Right)>>1;
                        if(mKey[Mid] < x)
                        {
                            Left = Mid+1;
                        }
                        else
                        {
                            Right = Mid;
                        }
                    }
                    if(mKey[Left] < x)
                    {
                        ++Left;
                    }
                    char ktemp[sizeof(KEY_t)];
                    memcpy(ktemp, &mKey[mSize], sizeof(KEY_t));
                    memmove(mKey+Left+1, mKey+Left, (mSize-Left)*sizeof(KEY_t));
                    memcpy(&mKey[Left], ktemp, sizeof(KEY_t));
                    mKey[Left] = x;
                    ++mSize;
                }
            }
        }
        void erase(const KEY_t& x)
        {
            KEY_t *point = find(x);
            if(point != NULL)
            {
                int idx = point-mKey;
                char ktemp[sizeof(KEY_t)];
                memcpy(ktemp, &mKey[idx], sizeof(KEY_t));
                memmove(mKey+idx, mKey+idx+1, (mSize-1-idx)*sizeof(KEY_t));
                memcpy(&mKey[mSize-1], ktemp, sizeof(KEY_t));
                --mSize;
            }
            else
            {
                printf("CPPSet erase ERROR\n");
            }
        }
        KEY_t* find(const KEY_t& x)
        {
            if(mSize == 0)
            {
                return NULL;
            }
            int Left, Right, Mid;
            Left = 0;
            Right = mSize-1;
            while(Left <= Right)
            {
                Mid = (Left+Right)>>1;
                if(mKey[Mid] == x)
                {
                    return &mKey[Mid];
                }
                else if(mKey[Mid] < x)
                {
                    Left = Mid+1;
                }
                else
                {
                    Right = Mid-1;
                }
            }
            return NULL;
        }
        KEY_t* begin()
        {
            if(mSize == 0)
            {
                return NULL;
            }
            return mKey;
        }
        KEY_t* end()
        {
            if(mSize == 0)
            {
                return NULL;
            }
            return &mKey[mSize-1];
        }
};
#endif
