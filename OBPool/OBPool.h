#ifndef _OBPool_H_
#define _OBPool_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
template <typename OB_t>
class OBPool
{
public:
    OBPool(const char *name)
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
        m_AddBlockDelta = 1;
        memcpy(m_Name, name, strlen(name));
    }
    virtual ~OBPool()
    {
        pthread_mutex_lock(&m_Mutex);
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
        pthread_mutex_unlock(&m_Mutex);
        pthread_mutex_destroy(&m_Mutex);
    }
    virtual size_t size()
    {
        return sizeof(int);
    }
    void SetParm(unsigned blockNum, unsigned int blockSize, int addDelta)
    {
        if(m_BlockSize != 0 || m_BlockNum != 0) {
            printf("%s double %s\n", m_Name, __func__);
            quick_exit(0);
        }
        for(m_BitShift = 1; m_BitShift < 32; ++m_BitShift) {
            if(blockSize == (1u << m_BitShift)) {
                break;
            }
        }
        if(m_BitShift == 32) {
            printf("%s The blockSize is not 2^N or too big\n", m_Name);
            quick_exit(0);
        }
        if(blockNum == 0) {
            printf("%s The blockNum equal 0\n", m_Name);
            quick_exit(0);
        }
        if(addDelta < 1) {
            printf("%s The addDelta less then 1\n", m_Name);
            quick_exit(0);
        }
        m_BlockNum = blockNum;
        m_BlockSize = blockSize;
        m_AddBlockDelta = addDelta;
        printf("OBPool:: %s SetBlockSize %zu\n", m_Name, (size() + sizeof(bool)) * m_BlockNum * m_BlockSize);
        m_FastModLen = m_BlockSize - 1;
        m_Data = new OB_t*[m_BlockNum];
        m_Flag = new bool*[m_BlockNum];
        for(unsigned i = 0; i < m_BlockNum; ++i) {
            m_Data[i] = new OB_t[m_BlockSize];
            m_Flag[i] = new bool[m_BlockSize]();
        }
        m_LastAllocIdx = 0;
        m_Count = m_BlockSize * m_BlockNum;
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
            printf("%s OBPool Idx %u invalid\n", m_Name, idx);
            quick_exit(0);
        }
        return m_Data[idx >> m_BitShift][0].Get(idx & m_FastModLen);
    }
    void FindSameElememt(OB_t **ans, OB_t *key, unsigned int keyIdx)
    {
        int cnt = 0;
        pthread_mutex_lock(&m_Mutex);
        for(auto idx = 0u; idx < m_BlockNum * m_BlockSize; ++idx) {
            unsigned int x = idx >> m_BitShift;
            unsigned int y =  idx & m_FastModLen;
            if(m_Flag[x][y] && idx != keyIdx) {
                if(*key == *(m_Data[idx >> m_BitShift][0].Get(idx & m_FastModLen))) {
                    ans[cnt++] = m_Data[idx >> m_BitShift][0].Get(idx & m_FastModLen);
                }
            }
        }
        pthread_mutex_unlock(&m_Mutex);
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
    int m_AddBlockDelta;
    char m_Name[512];

    void Expand()
    {
        printf("OBPool:: %s Expand %zu\n", m_Name, (size() + sizeof(bool)) * (m_BlockNum + m_AddBlockDelta)*m_BlockSize);
        OB_t **dataMem = new OB_t*[m_BlockNum + m_AddBlockDelta];
        bool **flagMem = new bool*[m_BlockNum + m_AddBlockDelta];
        memcpy(dataMem, m_Data, sizeof(OB_t *) * m_BlockNum);
        memcpy(flagMem, m_Flag, sizeof(bool *) * m_BlockNum);
        for(int i = 0; i < m_AddBlockDelta; ++i) {
            dataMem[m_BlockNum + i] = new OB_t[m_BlockSize];
            flagMem[m_BlockNum + i] = new bool[m_BlockSize]();
        }
        OB_t **delData = m_Data;
        bool **delFlag = m_Flag;
        m_Data = dataMem;
        m_Flag = flagMem;
        delete[] delData;
        delete[] delFlag;
        m_LastAllocIdx = m_BlockNum * m_BlockSize;
        m_BlockNum += m_AddBlockDelta;
        m_Count = m_BlockSize * m_AddBlockDelta;
    }
};
#endif
