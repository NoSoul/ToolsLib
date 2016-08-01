#ifndef _SlideWin_H_
#define _SlideWin_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
template <typename SlideWinType_t>
class SlideWin
{
public:
    SlideWin(): m_Sum(0)
    {
        m_Data = nullptr;
        m_Size = 0;
        Clear();
    }
    virtual ~SlideWin()
    {
        if(m_Data) {
            delete[] m_Data;
            m_Data = nullptr;
        }
    }
    void ReSize(const unsigned long long size)
    {
        if(m_Data) {
            delete[] m_Data;
            m_Data = nullptr;
        }
        m_Data = new SlideWinType_t[size];
        if(m_Data == nullptr) {
            printf("SlideWin bad alloc %d\n", __LINE__);
            quick_exit(0);
        }
        m_ReadPos = 0;
        m_WritePos = 0;
        m_WritePtr = &m_Data[m_WritePos];
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
            printf("SlideWin bad alloc %d\n", __LINE__);
            quick_exit(0);
        }
        memcpy(m_Data, source.m_Data, source.m_Size * sizeof(SlideWinType_t));
        m_ReadPos = source.m_ReadPos;
        m_WritePos = source.m_WritePos;
        m_WritePtr = &m_Data[m_WritePos];
        m_Size = source.m_Size;
        m_Count = source.m_Count;
        m_Sum = source.m_Sum;
        return *this;
    }
    void Clear()
    {
        m_ReadPos = 0;
        m_WritePos = 0;
        m_Count = 0;
        if(m_Data == nullptr) {
            m_WritePtr = nullptr;
        } else {
            m_WritePtr = &m_Data[m_WritePos];
        }
    }
    void Push(const SlideWinType_t& value)
    {
        if(m_Count == m_Size) {
            m_Sum -= m_Data[m_WritePos];
        }
        m_Data[m_WritePos] = value;
        m_Sum += value;
        ++m_WritePos;
        ++m_Count;
        if(m_WritePos == m_Size) {
            m_WritePos = 0;
        }
        if(m_Count >= m_Size) {
            m_Count = m_Size;
            m_ReadPos = m_WritePos;
        }
        m_WritePtr = &m_Data[m_WritePos];
    }
    void Push()
    {
        ++m_WritePos;
        ++m_Count;
        if(m_WritePos == m_Size) {
            m_WritePos = 0;
        }
        if(m_Count >= m_Size) {
            m_Count = m_Size;
            m_ReadPos = m_WritePos;
        }
        m_WritePtr = &m_Data[m_WritePos];
    }
    unsigned long long GetLength()
    {
        return m_Count;
    }
    SlideWinType_t GetSum()
    {
        return m_Sum;
    }
    SlideWinType_t GetAvg()
    {
        return m_Sum / m_Count;
    }
    SlideWinType_t *GetMax()
    {
        if(m_Count == 0) {
            return nullptr;
        }
        unsigned long long retIdx = m_ReadPos;
        for(unsigned long long cur = m_ReadPos, i = 0; i < m_Count; ++i) {
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
        unsigned long long retIdx = m_ReadPos;
        for(unsigned long long cur = m_ReadPos, i = 0; i < m_Count; ++i) {
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
        for(unsigned long long curr = m_ReadPos, i = 0; i < m_Count; ++i) {
            if(m_Data[curr] == value) {
                return true;
            }
            if(++curr == m_Size) {
                curr = 0;
            }
        }
        return false;
    }
protected:
    SlideWinType_t *m_Data;
    SlideWinType_t *m_WritePtr;
    SlideWinType_t m_Sum;
    unsigned long long m_ReadPos;
    unsigned long long m_WritePos;
    unsigned long long m_Size;
    unsigned long long m_Count;
};
#endif
