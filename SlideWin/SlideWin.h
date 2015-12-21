#ifndef _SlideWin_H_
#define _SlideWin_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
template <typename SlideWinType_t>
class SlideWin
{
public:
    SlideWin()
    {
        m_Data = nullptr;
        m_ReadPos = 0;
        m_WritePos = 0;
        m_Size = 0;
        m_Count = 0;
    }
    ~SlideWin()
    {
        if(m_Data) {
            delete[] m_Data;
            m_Data = nullptr;
        }
    }
    void ReSize(const int size)
    {
        if(m_Data) {
            delete[] m_Data;
            m_Data = nullptr;
        }
        m_Data = new SlideWinType_t[size];
        if(m_Data == nullptr) {
            puts("bad alloc");
            exit(0);
        }
        m_ReadPos = 0;
        m_WritePos = 0;
        m_Size = size;
        m_Count = 0;
    }
    SlideWin &operator=(const SlideWin &source)
    {
        if(&source == this) {
            return *this;
        }
        if(m_Data) {
            delete[] m_Data;
            m_Data = nullptr;
        }
        m_Data = new SlideWinType_t[source.m_Size];
        if(m_Data == nullptr) {
            puts("bad alloc");
            exit(0);
        }
        memcpy(m_Data, source.m_Data, source.m_Size * sizeof(SlideWinType_t));
        m_ReadPos = source.m_ReadPos;
        m_WritePos = source.m_WritePos;
        m_Size = source.m_Size;
        m_Count = source.m_Count;
        return *this;
    }
    void Clear()
    {
        m_ReadPos = 0;
        m_WritePos = 0;
        m_Count = 0;
    }
    void Push(const SlideWinType_t& value)
    {
        m_Data[m_WritePos] = value;
        ++m_WritePos;
        ++m_Count;
        if(m_WritePos == m_Size) {
            m_WritePos = 0;
        }
        if(m_Count >= m_Size) {
            m_Count = m_Size;
            m_ReadPos = m_WritePos;
        }
    }
    SlideWinType_t *Pop()
    {
        if(m_Count == 0) {
            return nullptr;
        }
        SlideWinType_t *result = &m_Data[m_ReadPos];
        ++m_ReadPos;
        --m_Count;
        if(m_ReadPos == m_Size) {
            m_ReadPos = 0;
        }
        return result;
    }
    int GetLength()
    {
        return m_Count;
    }
    SlideWinType_t GetAvg()
    {
        SlideWinType_t Sum(0);
        for(int cur = m_ReadPos, i = 0; i < m_Count; ++i) {
            Sum += m_Data[cur];
            if(++cur == m_Size) {
                cur = 0;
            }
        }
        return Sum / m_Count;
    }
    SlideWinType_t *GetMax()
    {
        if(m_Count == 0) {
            return nullptr;
        }
        int retIdx = m_ReadPos;
        for(int cur = m_ReadPos, i = 0; i < m_Count; ++i) {
            if(m_Data[cur] > m_Data[retIdx]) {
                retIdx = cur;
            }
            if(++cur == m_Size) {
                cur = 0;
            }
        }
        return &m_Data[retIdx];
    }
    SlideWinType_t *GetMin()
    {
        if(m_Count == 0) {
            return nullptr;
        }
        int retIdx = m_ReadPos;
        for(int cur = m_ReadPos, i = 0; i < m_Count; ++i) {
            if(m_Data[cur] < m_Data[retIdx]) {
                retIdx = cur;
            }
            if(++cur == m_Size) {
                cur = 0;
            }
        }
        return &m_Data[retIdx];
    }
    bool Exist(const SlideWinType_t& value)
    {
        for(int curr = m_ReadPos, i = 0; i < m_Count; ++i) {
            if(m_Data[curr] == value) {
                return true;
            }
            if(++curr == m_Size) {
                curr = 0;
            }
        }
        return false;
    }
private:
    SlideWinType_t *m_Data;
    int m_ReadPos;
    int m_WritePos;
    int m_Size;
    int m_Count;
};
#endif
