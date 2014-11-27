#include "OBPool.h"
#define MAXN    20
class A
{
public:
    A()
    {
        mem = new char[1024];
        Initialize();
    }
    ~A()
    {
        delete[] mem;
    }
    A& operator=(const A &other)
    {
        num = other.num;
        memcpy(mem, other.mem, sizeof(char) * 1024);
        return *this;
    }
    void Initialize()
    {
        num = -1;
    }
    char *mem;
    int num;
};

class B
{
public:
    void Initialize()
    {
        for(int i = 0; i < MAXN; ++i) {
            m_RM[i].Initialize();
        }
    }
    A m_RM[MAXN];
};

int main()
{
    OBPool<B> testPool;
    testPool.ReSize(2);
    int Len = 0;
    int Idx[MAXN];
    for(int i = 0; i < MAXN; ++i)
    {
        if(rand() % 3)
        {
            Idx[Len] = testPool.AllocOB();
            for(int j = 0; j < MAXN; ++j)
            {
                testPool[Idx[Len]].m_RM[j].num = i;
            }
            printf("I'am %d %d\n", i, Idx[Len]);
            ++Len;
        }
    }
    for(int i = 0; i < Len; ++i)
    {
        printf("%d\t", Idx[i]);
        for(int j = 0; j < MAXN; ++j)
        {
            printf("%d ", testPool[Idx[i]].m_RM[j].num);
        }
        puts("");
        testPool.FreeOB(Idx[i]);
    }
    return 0;
}
