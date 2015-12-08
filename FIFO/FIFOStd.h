#ifndef _FIFOStd_H_
#define _FIFOStd_H_
#include <stdio.h>
#include <stdlib.h>
template <typename FIFOType_t>
class FIFOStd
{
public:
    FIFOType_t *m_WritePtr;
    FIFOStd()
    {
        m_Data = NULL;
        m_WritePtr = NULL;
        m_ReadPos = 0;
        m_WritePos = 0;
        m_Size = 0;
    }
    ~FIFOStd()
    {
        if(m_Data) {
            delete[] m_Data;
            m_Data = NULL;
        }
    }
    void ReSize(const unsigned int size)
    {
        int i;
        for(i = 1; i < 32; ++i) {
            if(size == (1u << i)) {
                break;
            }
        }
        if(i == 32) {
            puts("The size of FIFOStd is not 2^N or too big");
            exit(0);
        }
        if(m_Data != NULL) {
            puts("double ReSize");
            exit(0);
        }
        m_Data = new FIFOType_t[size];
        if(m_Data == NULL) {
            puts("bad alloc");
            exit(0);
        }
        m_ReadPos = 0;
        m_WritePos = 0;
        m_WritePtr = &m_Data[m_WritePos];
        m_Size = size;
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
    bool Push()
    {
        unsigned int newWritePos = (m_WritePos + 1) & (m_Size - 1);
        if(newWritePos == ((m_ReadPos - 1) & (m_Size - 1))) {
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
    unsigned int GetLength()
    {
        return (m_WritePos + m_Size - m_ReadPos) & (m_Size - 1);
    }
protected:
    FIFOType_t *m_Data;
    unsigned int m_ReadPos;
    unsigned int m_WritePos;
    unsigned int m_Size;
};
#endif
