#ifndef _HeapSlideWin_H_
#define _HeapSlideWin_H_
#include <string.h>
template <typename HeapSlideWinType_t>
class HeapSlideWin
{
public:
    HeapSlideWin(unsigned long long size, unsigned long long heapSize, bool desc)
    {
        m_Size = size;
        m_HeapSize = heapSize;
        m_Desc = desc;
        m_OriginData = new HeapSlideWinType_t[m_Size];
        m_InHeap = new bool[m_Size];
        HeapSlideWinClear();
    }
    virtual ~HeapSlideWin()
    {
        delete[] m_OriginData;
        delete[] m_InHeap;
    }
    void HeapSlideWinClear()
    {
        m_HeapSum = 0;
        m_Count = 0;
        m_HeapCount = 0;
        m_WritePos = 0;
        memset(m_InHeap, 0, m_Size);
    }
    void HeapSlideWinPush(const HeapSlideWinType_t& value)
    {
        if(m_InHeap[m_WritePos]) {
            m_InHeap[m_WritePos] = false;
            m_HeapSum -= m_OriginData[m_WritePos];
            --m_HeapCount;
        }
        m_OriginData[m_WritePos] = value;
        if(++m_Count >= m_Size) {
            m_Count = m_Size;
        }
        unsigned long long minIdx = m_Size + 1, maxIdx = m_Size + 1;
        for(unsigned long long i = 0; i < m_Count; ++i) {
            unsigned long long idx;
            if(m_WritePos >= i) {
                idx = m_WritePos - i;
            } else {
                idx = m_Size - i + m_WritePos;
            }
            if((m_InHeap[idx] && m_Desc) || (!m_InHeap[idx] && !m_Desc)) {
                if(minIdx == m_Size + 1 || m_OriginData[idx] < m_OriginData[minIdx]) {
                    minIdx = idx;
                }
            } else {
                if(maxIdx == m_Size + 1) {
                    maxIdx = idx;
                } else {
                    if(m_OriginData[idx] > m_OriginData[maxIdx]) {
                        maxIdx = idx;
                    }
                }
            }
        }
        unsigned long long oldIdx, newIdx;
        if(m_Desc) {
            oldIdx = minIdx;
            newIdx = maxIdx;
        } else {
            oldIdx = maxIdx;
            newIdx = minIdx;
        }
        if(m_HeapCount < m_HeapSize) {
            m_InHeap[newIdx] = true;
            m_HeapSum += m_OriginData[newIdx];
            ++m_HeapCount;
        } else {
            if(oldIdx != m_Size + 1 && newIdx != m_Size + 1) {
                bool replace = false;
                if(m_Desc && m_OriginData[newIdx] > m_OriginData[oldIdx]) {
                    replace = true;
                }
                if(!m_Desc && m_OriginData[newIdx] < m_OriginData[oldIdx]) {
                    replace = true;
                }
                if(replace) {
                    m_InHeap[oldIdx] = false;
                    m_HeapSum -= m_OriginData[oldIdx];
                    m_InHeap[newIdx] = true;
                    m_HeapSum += m_OriginData[newIdx];
                }
            }
        }
        if(++m_WritePos == m_Size) {
            m_WritePos = 0;
        }
    }
    HeapSlideWinType_t HeapSlideWinGetVal()
    {
        if(m_HeapCount == 0) {
            return m_HeapSum;
        }
        return m_HeapSum / m_HeapCount;
    }
protected:
    unsigned long long m_Size;
    unsigned long long m_HeapSize;
    bool m_Desc;
    HeapSlideWinType_t *m_OriginData;
    bool *m_InHeap;
    HeapSlideWinType_t m_HeapSum;
    unsigned long long m_Count;
    unsigned long long m_HeapCount;
    unsigned long long m_WritePos;
};
#endif
