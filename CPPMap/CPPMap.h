#ifndef _CPPMap_H_
#define _CPPMap_H_
#include <stdio.h>
#include <string.h>
#define CPP_MAP_ADD_VALUE   50
template <typename KEY_t, typename VALUE_t>
class CPPMapPair_t
{
public:
    KEY_t *first;
    VALUE_t *second;

    bool operator<=(const CPPMapPair_t& src)const
    {
        return first <= src.first && second < src.second;
    }
    void next()
    {
        first += 1;
        second += 1;
    }
};
template <typename KEY_t, typename VALUE_t>
class CPPMap
{
private:
    KEY_t *mKey;
    VALUE_t *mValue;
    unsigned int mCapacity;
    unsigned int mSize;

    VALUE_t& get(const KEY_t& x)
    {
        VALUE_t *point = find(x).second;
        if(point == NULL)
        {
            insert(x);
            point = find(x).second;
        }
        return *point;
    }
public:
    CPPMap()
    {
        mSize = 0;
        mCapacity = 0;
        mKey = NULL;
        mValue = NULL;
    }
    ~CPPMap()
    {
        if(mKey)
        {
            delete[] mKey;
        }
        if(mValue)
        {
            delete[] mValue;
        }
    }
    unsigned int size()
    {
        return mSize;
    }
    void insert(const KEY_t& x)
    {
        if(find(x).second == NULL)
        {
            if(mSize + 1 >= mCapacity)
            {
                KEY_t *key_mem = new KEY_t[mCapacity + CPP_MAP_ADD_VALUE];
                VALUE_t *val_mem = new VALUE_t[mCapacity + CPP_MAP_ADD_VALUE];
                int i;
                for(i = 0; i < mSize; ++i)
                {
                    if(mKey[i] < x)
                    {
                        key_mem[i] = mKey[i];
                        val_mem[i] = mValue[i];
                    }
                    else
                    {
                        break;
                    }
                }
                key_mem[i] = x;
                for(; i < mSize; ++i)
                {
                    key_mem[i + 1] = mKey[i];
                    val_mem[i + 1] = mValue[i];
                }
                ++mSize;
                if(mKey)
                {
                    delete[] mKey;
                }
                if(mValue)
                {
                    delete[] mValue;
                }
                mKey = key_mem;
                mValue = val_mem;
                mCapacity += CPP_MAP_ADD_VALUE;
            }
            else
            {
                int Left, Right, Mid;
                Left = 0;
                Right = mSize - 1;
                while(Left < Right)
                {
                    Mid = (Left + Right) >> 1;
                    if(mKey[Mid] < x)
                    {
                        Left = Mid + 1;
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
                char vtemp[sizeof(VALUE_t)];
                memcpy(ktemp, &mKey[mSize], sizeof(KEY_t));
                memcpy(vtemp, &mValue[mSize], sizeof(VALUE_t));
                memmove(mKey + Left + 1, mKey + Left, (mSize - Left)*sizeof(KEY_t));
                memmove(mValue + Left + 1, mValue + Left, (mSize - Left)*sizeof(VALUE_t));
                memcpy(&mKey[Left], ktemp, sizeof(KEY_t));
                memcpy(&mValue[Left], vtemp, sizeof(VALUE_t));
                mKey[Left] = x;
                ++mSize;
            }
        }
    }
    void erase(const KEY_t& x)
    {
        VALUE_t *point = find(x).second;
        if(point != NULL)
        {
            int idx = point - mValue;
            char ktemp[sizeof(KEY_t)];
            char vtemp[sizeof(VALUE_t)];
            memcpy(ktemp, &mKey[idx], sizeof(KEY_t));
            memcpy(vtemp, &mValue[idx], sizeof(VALUE_t));
            memmove(mKey + idx, mKey + idx + 1, (mSize - 1 - idx)*sizeof(KEY_t));
            memmove(mValue + idx, mValue + idx + 1, (mSize - 1 - idx)*sizeof(VALUE_t));
            memcpy(&mKey[mSize - 1], ktemp, sizeof(KEY_t));
            memcpy(&mValue[mSize - 1], vtemp, sizeof(VALUE_t));
            --mSize;
        }
        else
        {
            printf("CPPMap erase ERROR\n");
        }
    }
    CPPMapPair_t<KEY_t, VALUE_t> find(const KEY_t& x)
    {
        CPPMapPair_t<KEY_t, VALUE_t> iterator = {.first = NULL, .second = NULL};
        if(mSize == 0)
        {
            return iterator;
        }
        int Left, Right, Mid;
        Left = 0;
        Right = mSize - 1;
        while(Left <= Right)
        {
            Mid = (Left + Right) >> 1;
            if(mKey[Mid] == x)
            {
                iterator.first = &mKey[Mid];
                iterator.second = &mValue[Mid];
                return iterator;
            }
            else if(mKey[Mid] < x)
            {
                Left = Mid + 1;
            }
            else
            {
                Right = Mid - 1;
            }
        }
        return iterator;
    }
    CPPMapPair_t<KEY_t, VALUE_t> begin()
    {
        CPPMapPair_t<KEY_t, VALUE_t> iterator = {.first = NULL, .second = NULL};
        if(mSize == 0)
        {
            return iterator;
        }
        iterator.first = mKey;
        iterator.second = mValue;
        return iterator;
    }
    CPPMapPair_t<KEY_t, VALUE_t> end()
    {
        CPPMapPair_t<KEY_t, VALUE_t> iterator = {.first = NULL, .second = NULL};
        if(mSize == 0)
        {
            return iterator;
        }
        iterator.first = &mKey[mSize - 1];
        iterator.second = &mValue[mSize - 1];
        return iterator;
    }
    VALUE_t& operator[](const KEY_t& x)
    {
        return get(x);
    }
    const VALUE_t& operator[](const KEY_t& x)const
    {
        return get(x);
    }
};
#endif
