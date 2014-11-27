#ifndef _OBPool_H_
#define _OBPool_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OB_POOL_ADD_VALUE   50
template <typename OB_t>
class OBPool
{
public:
    OBPool()
    {
        m_Data = NULL;
        m_Flag = NULL;
        m_Size = 0;
    }
    ~OBPool()
    {
        if (m_Data) {
            delete []m_Data;
            m_Data = NULL;
        }
        if (m_Flag) {
            delete []m_Flag;
            m_Flag = NULL;
        }
    }
    void ReSize(const int size)
    {
        if(size <= m_Size)
        {
            puts("OBPool Segment Fault");
            exit(0);
        }
        OB_t *data_mem = new OB_t[size];
        bool *flag_mem = new bool[size];
        memset(flag_mem, 0, sizeof(bool)*size);
        if (m_Data) {
            for(int i = 0; i < m_Size; ++i) {
                data_mem[i] = m_Data[i];
            }
            delete []m_Data;
        }
        if (m_Flag) {
            memcpy(flag_mem, m_Flag, sizeof(bool)*m_Size);
            delete []m_Flag;
        }
        m_Data = data_mem;
        m_Flag = flag_mem;
        m_Size = size;
    }
    int AllocOB()
    {
        for(int i = 0; i < m_Size; ++i) {
            if(!m_Flag[i])
            {
                m_Flag[i] = true;
                return i;
            }
        }
        ReSize(m_Size + OB_POOL_ADD_VALUE);
        m_Flag[m_Size - OB_POOL_ADD_VALUE] = true;
        return m_Size - OB_POOL_ADD_VALUE;
    }
    void FreeOB(const int idx)
    {
        if(idx < 0 || idx >= m_Size)
        {
            return;
        }
        m_Flag[idx] = false;
        m_Data[idx].Initialize();
    }
    OB_t& operator[](const int idx)
    {
        if(idx < 0 || idx >= m_Size)
        {
            puts("OBPool Segment Fault");
            exit(0);
        }
        return m_Data[idx];
    }
    const OB_t& operator[](const int idx)const
    {
        if(idx < 0 || idx >= m_Size)
        {
            puts("OBPool Segment Fault");
            exit(0);
        }
        return m_Data[idx];
    }
private:
    OB_t *m_Data;
    bool *m_Flag;
    unsigned int m_Size;
};
#endif
