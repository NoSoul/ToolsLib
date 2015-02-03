#ifndef _OBPool_H_
#define _OBPool_H_
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#define OB_POOL_ADD_BLOCK   3
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
    }
    ~OBPool()
    {
        if(m_BlockSize) {
            FreeOB(0);
        }
        for(int i = 0; i < m_BlockNum; ++i) {
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
        assert(m_BlockSize == 0);
        m_BlockSize = blockSize;
        m_Data = new OB_t*[OB_POOL_ADD_BLOCK];
        m_Flag = new bool*[OB_POOL_ADD_BLOCK];
        for(int i = 0; i < OB_POOL_ADD_BLOCK; ++i) {
            m_Data[i] = new OB_t[m_BlockSize];
            m_Flag[i] = new bool[m_BlockSize];
            memset(m_Flag[i], 0, sizeof(bool)*m_BlockSize);
        }
        m_LastAllocIdx = m_BlockNum * m_BlockSize;
        m_BlockNum += OB_POOL_ADD_BLOCK;
        m_Count = m_BlockSize * OB_POOL_ADD_BLOCK;
        AllocOB();
    }
    unsigned int AllocOB()
    {
        assert(m_BlockSize != 0);
        pthread_mutex_lock(&m_Mutex);
        if(m_Count == 0) {
            Expand();
        }
        unsigned int x, y;
        x = m_LastAllocIdx / m_BlockSize;
        y = m_LastAllocIdx % m_BlockSize;
        while(m_Flag[x][y]) {
            ++m_LastAllocIdx;
            m_LastAllocIdx %= m_BlockNum * m_BlockSize;
            x = m_LastAllocIdx / m_BlockSize;
            y = m_LastAllocIdx % m_BlockSize;
        }
        assert(!m_Flag[x][y]);
        m_Flag[x][y] = true;
        --m_Count;
        unsigned int ret = m_LastAllocIdx;
        pthread_mutex_unlock(&m_Mutex);
        return ret;
    }
    void FreeOB(const unsigned int idx)
    {
        pthread_mutex_lock(&m_Mutex);
        assert(idx < m_BlockSize * m_BlockNum);
        assert(m_Flag[idx / m_BlockSize][idx % m_BlockSize]);
        m_Flag[idx / m_BlockSize][idx % m_BlockSize] = false;
        m_Data[idx / m_BlockSize][idx % m_BlockSize].Initialize();
        ++m_Count;
        pthread_mutex_unlock(&m_Mutex);
    }
    auto Get(const unsigned int idx)->decltype(OB_t::m_ForDeclGet)
    {
        assert(idx < m_BlockSize * m_BlockNum);
        if(!m_Flag[idx / m_BlockSize][idx % m_BlockSize]) {
            printf("OBPool Idx invald, return %u => 0\n", idx);
            return m_Data[0][0].Get(0);
        }
        return m_Data[idx / m_BlockSize][0].Get(idx % m_BlockSize);
    }
private:
    OB_t **m_Data;
    bool **m_Flag;
    unsigned int m_BlockSize;
    unsigned int m_BlockNum;
    unsigned int m_LastAllocIdx;
    unsigned int m_Count;
    pthread_mutex_t m_Mutex;

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
