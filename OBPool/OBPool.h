#ifndef _OBPool_H_
#define _OBPool_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define OB_POOL_ADD_BLOCK   1
template <typename OB_t>
class OBPool
{
public:
    OBPool()
    {
        m_Data = NULL;
        m_Flag = NULL;
        m_BlockSize = 0;
        m_BlockNum = 0;
        m_LastAllocIdx = 0;
        m_Count = 0;
        pthread_mutex_init(&m_Mutex, NULL);
        m_BitShift = 0;
        m_FastModLen = 0;
    }
    ~OBPool()
    {
        if(m_BlockSize) {
            FreeOB(0);
        }
        for(auto i = 0u; i < m_BlockNum; ++i) {
            if(m_Data[i]) {
                delete[] m_Data[i];
            }
            if(m_Flag[i]) {
                delete[] m_Flag[i];
            }
        }
        if(m_Data) {
            delete[] m_Data;
        }
        if(m_Flag) {
            delete[] m_Flag;
        }
        pthread_mutex_destroy(&m_Mutex);
    }
    void SetBlockSize(unsigned int blockSize)
    {
        if(m_BlockSize != 0 || m_BlockNum != 0) {
            puts("double SetBlockSize");
            quick_exit(0);
        }
        for(m_BitShift = 1; m_BitShift < 32; ++m_BitShift) {
            if(blockSize == (1u << m_BitShift)) {
                break;
            }
        }
        if(m_BitShift == 32) {
            puts("The blockSize is not 2^N or too big");
            quick_exit(0);
        }
        m_BlockSize = blockSize;
        m_FastModLen = m_BlockSize - 1;
        m_Data = new OB_t*[OB_POOL_ADD_BLOCK];
        m_Flag = new bool*[OB_POOL_ADD_BLOCK];
        for(int i = 0; i < OB_POOL_ADD_BLOCK; ++i) {
            m_Data[i] = new OB_t[m_BlockSize];
            m_Flag[i] = new bool[m_BlockSize];
            memset(m_Flag[i], 0, sizeof(bool)*m_BlockSize);
        }
        m_LastAllocIdx = 0;
        m_BlockNum = OB_POOL_ADD_BLOCK;
        m_Count = m_BlockSize * OB_POOL_ADD_BLOCK;
    }
    unsigned int AllocOB()
    {
        pthread_mutex_lock(&m_Mutex);
        if(m_Count == 0) {
            Expand();
        }
        unsigned int x, y;
        x = m_LastAllocIdx >> m_BitShift;
        y = m_LastAllocIdx & m_FastModLen;
        while(m_Flag[x][y]) {
            if(++m_LastAllocIdx == m_BlockNum * m_BlockSize) {
                m_LastAllocIdx = 0;
            }
            x = m_LastAllocIdx >> m_BitShift;
            y = m_LastAllocIdx & m_FastModLen;
        }
        m_Flag[x][y] = true;
        --m_Count;
        unsigned int ret = m_LastAllocIdx;
        pthread_mutex_unlock(&m_Mutex);
        return ret;
    }
    void FreeOB(const unsigned int idx)
    {
        pthread_mutex_lock(&m_Mutex);
        m_Flag[idx >> m_BitShift][idx & m_FastModLen] = false;
        ++m_Count;
        pthread_mutex_unlock(&m_Mutex);
    }
    auto Get(const unsigned int idx)->decltype(OB_t::m_ForDeclGet)
    {
        if(!m_Flag[idx >> m_BitShift][idx & m_FastModLen]) {
            printf("OBPool Idx %u invalid\n", idx);
            quick_exit(0);
        }
        return m_Data[idx >> m_BitShift][0].Get(idx & m_FastModLen);
    }
private:
    OB_t **m_Data;
    bool **m_Flag;
    unsigned int m_BlockSize;
    unsigned int m_BlockNum;
    unsigned int m_LastAllocIdx;
    unsigned int m_Count;
    pthread_mutex_t m_Mutex;
    unsigned int m_BitShift;
    unsigned int m_FastModLen;

    void Expand()
    {
        OB_t **dataMem = new OB_t*[m_BlockNum + OB_POOL_ADD_BLOCK];
        bool **flagMem = new bool*[m_BlockNum + OB_POOL_ADD_BLOCK];
        memcpy(dataMem, m_Data, sizeof(OB_t*)*m_BlockNum);
        memcpy(flagMem, m_Flag, sizeof(bool*)*m_BlockNum);
        for(int i = 0; i < OB_POOL_ADD_BLOCK; ++i) {
            dataMem[m_BlockNum + i] = new OB_t[m_BlockSize];
            flagMem[m_BlockNum + i] = new bool[m_BlockSize];
            memset(flagMem[m_BlockNum + i], 0, sizeof(bool)*m_BlockSize);
        }
        OB_t **delData = m_Data;
        bool **delFlag = m_Flag;
        m_Data = dataMem;
        m_Flag = flagMem;
        delete[] delData;
        delete[] delFlag;
        m_LastAllocIdx = m_BlockNum * m_BlockSize;
        m_BlockNum += OB_POOL_ADD_BLOCK;
        m_Count = m_BlockSize * OB_POOL_ADD_BLOCK;
    }
};
#endif
