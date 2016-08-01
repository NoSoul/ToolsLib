#ifndef _FIFOStd_H_
#define _FIFOStd_H_
#include <stdio.h>
#include <stdlib.h>
template <typename FIFOType_t>
class FIFOStd
{
public:
    FIFOStd()
    {
        m_Data = NULL;
        m_WritePtr = NULL;
        m_ReadPos = 0;
        m_WritePos = 0;
        m_Size = 0;
        m_ProtectInterval = 1;
    }
    virtual ~FIFOStd()
    {
        if(m_Data) {
            delete[] m_Data;
            m_Data = NULL;
        }
    }
    void ReSize(const unsigned long long size)
    {
        int i;
        for(i = 1; i < 60; ++i) {
            if(size == (1UL << i)) {
                break;
            }
        }
        if(i == 60) {
            puts("The size of FIFOStd is not 2^N or too big");
            quick_exit(0);
        }
        if(m_Data != NULL) {
            delete[] m_Data;
        }
        m_Data = new FIFOType_t[size];
        if(m_Data == NULL) {
            puts("bad alloc FIFOStd");
            quick_exit(0);
        }
        m_ReadPos = 0;
        m_WritePos = 0;
        m_WritePtr = &m_Data[m_WritePos];
        m_Size = size;
    }
    void SetProtectInterval(const unsigned long long interval)
    {
        m_ProtectInterval = interval;
    }
    void Clear()
    {
        m_ReadPos = 0;
        m_WritePos = 0;
        if(m_Data == NULL) {
            m_WritePtr = NULL;
        } else {
            m_WritePtr = &m_Data[m_WritePos];
        }
    }
    void CommitRead(const unsigned long long size)
    {
        m_ReadPos = (m_ReadPos + size) & (m_Size - 1);
    }
    bool Push()
    {
        unsigned long long checkPos = (m_WritePos + m_ProtectInterval) & (m_Size - 1);
        unsigned long long newWritePos = (m_WritePos + 1) & (m_Size - 1);
        if(checkPos == m_ReadPos) {
            return false;
        }
        m_WritePos = newWritePos;
        m_WritePtr = &m_Data[m_WritePos];
        return true;
    }
    FIFOType_t *Pop()
    {
        FIFOType_t *result = &m_Data[m_ReadPos];
        m_ReadPos = (m_ReadPos + 1) & (m_Size - 1);
        return result;
    }
    FIFOType_t *Watch(const long long offset)
    {
        unsigned long long newReadPos = (m_ReadPos + offset + m_Size) & (m_Size - 1);
        FIFOType_t *result = &m_Data[newReadPos];
        return result;
    }
    unsigned long long GetLength()
    {
        return (m_WritePos + m_Size - m_ReadPos) & (m_Size - 1);
    }
protected:
    FIFOType_t *m_Data;
    FIFOType_t *m_WritePtr;
    unsigned long long m_ReadPos;
    unsigned long long m_WritePos;
    unsigned long long m_Size;
    unsigned long long m_ProtectInterval;
};
#endif
