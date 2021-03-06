#include "OBPool.h"
#include <malloc.h>
#include <map>
using namespace std;
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
    static B *m_ForDeclGet;
    void Initialize()
    {
        for(int i = 0; i < MAXN; ++i) {
            m_RM[i].Initialize();
        }
    }
    B *Get(const unsigned int idx)
    {
        return (B *)this + idx;
    }
    A m_RM[MAXN];
};

class C
{
public:
    static float *m_ForDeclGet;
    void Initialize()
    {
    }
    void *operator new[](size_t size)
    {
        float *mem = (float *)memalign(32, sizeof(float) * 4 * size);
        return mem;
    }
    void operator delete[](void *p)
    {
        free(p);
    }
    float *Get(const unsigned int idx)
    {
        return (float *)this + idx * 4;
    }
private:
    void *operator new(size_t size)
    {
        if(size) {
        }
        return NULL;
    }
    void operator delete(void *p)
    {
        free(p);
    }
};

OBPool<B> testPoolX("testPoolX");
OBPool<C> testPoolY("testPoolY");
map<int, unsigned int> Map;
pthread_mutex_t g_ProtectedMutex;

void *Fun(void *arg)
{
    for(int i = 0; i < 1024; ++i) {
        int num = rand() % 50;
        pthread_mutex_lock(&g_ProtectedMutex);
        if(Map[num]) {
            testPoolX.FreeOB(Map[num]);
            Map[num] = 0;
        } else {
            Map[num] = testPoolX.AllocOB();
        }
        pthread_mutex_unlock(&g_ProtectedMutex);
    }
    return arg;
}

int main()
{
    pthread_mutex_init(&g_ProtectedMutex, NULL);
    testPoolX.SetParm(1, 8, 1);
    testPoolY.SetParm(1, 128, 1);
    const int N = 5 * 2 + 2;
    unsigned int IdxX[N], IdxY[N];
    for(int i = 0; i < N; ++i) {
        IdxX[i] = testPoolX.AllocOB();
        IdxY[i] = testPoolY.AllocOB();
    }
    float *pre, *cur;
    for(int i = 0; i < N; ++i) {
        if(i == 0) {
            pre = testPoolY.Get(IdxY[i]);
        } else {
            cur = testPoolY.Get(IdxY[i]);
            if(cur - pre != 4) {
                puts("ERROR");
            }
            pre = cur;
        }
    }
    for(int i = 0; i < N; ++i) {
        testPoolX.FreeOB(IdxX[i]);
        testPoolY.FreeOB(IdxY[i]);
    }
    const int test_threads = 4;
    pthread_t Id[test_threads];
    for(int i = 0; i < test_threads; ++i) {
        pthread_create(&Id[i], NULL, Fun, NULL);
    }
    for(int i = 0; i < test_threads; ++i) {
        pthread_join(Id[i], NULL);
    }
    pthread_mutex_destroy(&g_ProtectedMutex);
    return 0;
}
