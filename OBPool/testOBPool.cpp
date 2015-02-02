#include "OBPool.h"
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
    void Initialize()
    {
        for(int i = 0; i < MAXN; ++i) {
            m_RM[i].Initialize();
        }
    }
    A m_RM[MAXN];
};

OBPool<B> testPool;
map<int, unsigned int> Map;
pthread_mutex_t g_ProtectedMutex;

void *Fun(void *arg)
{
    for(int i = 0; i < 1024 * 1024; ++i) {
        int num = rand() % 50;
        pthread_mutex_lock(&g_ProtectedMutex);
        if(Map[num]) {
            testPool.FreeOB(Map[num]);
            Map[num] = 0;
        } else {
            Map[num] = testPool.AllocOB();
        }
        pthread_mutex_unlock(&g_ProtectedMutex);
    }
    return arg;
}

int main()
{
    pthread_mutex_init(&g_ProtectedMutex, NULL);
    testPool.SetBlockSize(5);
    unsigned int NULLIdx = testPool.AllocOB();
    printf("%u\n", NULLIdx);
    const int N = OB_POOL_ADD_BLOCK * 5 * 2 + 2;
    unsigned int Idx[N];
    for(int i = 0; i < N; ++i) {
        Idx[i] = testPool.AllocOB();
    }
    for(int i = 0; i < N; ++i) {
        testPool.FreeOB(Idx[i]);
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
