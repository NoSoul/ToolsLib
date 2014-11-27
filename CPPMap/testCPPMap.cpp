#include "CPPMap.h"
#include <map>
#include <sys/time.h>
using namespace std;

class A
{
public:
    int a;
    char *mema;
    A()
    {
        a = -1;
        mema = new char[4];
    }
    A(const A& src)
    {
        a = src.a;
        mema = new char[4];
        memcpy(mema, src.mema, sizeof(char) * 4);
    }
    A& operator=(const A &src)
    {
        a = src.a;
        memcpy(mema, src.mema, sizeof(char) * 4);
        return *this;
    }
    bool operator<(const A &src)const
    {
        return a < src.a;
    }
    bool operator==(const A &src)const
    {
        return a == src.a;
    }
    ~A()
    {
        delete[] mema;
    }
};

typedef struct
{
    A mHandle[100];
} Node_t;

int main()
{
    CPPMap<int, Node_t> Map0;
    map<int, Node_t> Map1;
    struct timeval startexe, endexe;
    int LOOP = 100;
    gettimeofday(&startexe, NULL);
    for(int j = 0; j < LOOP; ++j)
    {
        for(int i = 0; i < 20; ++i)
        {
            Map0[i].mHandle[0].a = i;
            //printf("%d\n", Map0.find(i).second->mHandle[0].a);
        }
        for(int i = 50 - 1; i >= 20; --i)
        {
            Map0[i].mHandle[0].a = i;
            //printf("%d\n", Map0.find(i).second->mHandle[0].a);
        }
        for(int i = 50; i < 100; ++i)
        {
            Map0[i].mHandle[0].a = i;
            //printf("%d\n", Map0.find(i).second->mHandle[0].a);
        }
        //for(CPPMapPair_t<int, Node_t> it=Map0.begin(); it<=Map0.end(); it.next())
        //{
        //    printf("%d,%d ", *(it.first), it.second->mHandle[0].a);
        //}
        //puts("");
        for(int i = 0; i < 20; ++i)
        {
            Map0.erase(i);
        }
        for(int i = 50 - 1; i >= 20; --i)
        {
            Map0.erase(i);
        }
        for(int i = 50; i < 100; ++i)
        {
            Map0.erase(i);
        }
    }
    gettimeofday(&endexe, NULL);
    printf("New Map %ld\n", 1000000 * (endexe.tv_sec - startexe.tv_sec) + endexe.tv_usec - startexe.tv_usec);
    gettimeofday(&startexe, NULL);
    for(int j = 0; j < LOOP; ++j)
    {
        for(int i = 0; i < 100; ++i)
        {
            Map1[i].mHandle[i].a = i;
            //printf("%d\n", Map1.find(i)->second.mHandle[i].a);
        }
        for(int i = 0; i < 100; ++i)
        {
            Map1.erase(i);
        }
    }
    gettimeofday(&endexe, NULL);
    printf("STL Map %ld\n", 1000000 * (endexe.tv_sec - startexe.tv_sec) + endexe.tv_usec - startexe.tv_usec);
    return 0;
}
