#include "CPPSet.h"
#include <set>
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
            memcpy(mema, src.mema, sizeof(char)*4);
        }
        A& operator=(const A &src)
        {
            a = src.a;
            memcpy(mema, src.mema, sizeof(char)*4);
            return *this;
        }
        bool operator<(const A &src)const
        {
            return a<src.a;
        }
        bool operator==(const A &src)const
        {
            return a==src.a;
        }
        ~A()
        {
            delete[] mema;
        }
};

int main()
{
    CPPSet<A> Set0;
    set<A> Set1;
    A ob;
    struct timeval startexe, endexe;
    int LOOP = 10000;
	gettimeofday(&startexe, NULL);
	for(int j=0; j<LOOP; ++j)
    {
        for(int i=0; i<20; ++i)
        {
            ob.a = i;
            Set0.insert(ob);
            //printf("%d\n", Set0.find(ob)->a);
        }
        for(int i=50-1; i>=20; --i)
        {
            ob.a = i;
            Set0.insert(ob);
            //printf("%d\n", Set0.find(ob)->a);
        }
        for(int i=50; i<100; ++i)
        {
            ob.a = i;
            Set0.insert(ob);
            //printf("%d\n", Set0.find(ob)->a);
        }
        //for(A *it = Set0.begin(); it<=Set0.end(); ++it)
        //{
        //    printf("%d ", it->a);
        //}
        //puts("");
        for(int i=0; i<20; ++i)
        {
            ob.a = i;
            Set0.erase(ob);
        }
        for(int i=50-1; i>=20; --i)
        {
            ob.a = i;
            Set0.erase(ob);
        }
        for(int i=50; i<100; ++i)
        {
            ob.a = i;
            Set0.erase(ob);
        }
    }
    gettimeofday(&endexe, NULL);
    printf("New Set %ld\n", 1000000*(endexe.tv_sec-startexe.tv_sec)+endexe.tv_usec-startexe.tv_usec);
    gettimeofday(&startexe, NULL);
    for(int j=0; j<LOOP; ++j)
    {
        for(int i=0; i<100; ++i)
        {
            ob.a = i;
            Set1.insert(ob);
        }
        for(int i=0; i<100; ++i)
        {
            ob.a = i;
            Set1.erase(ob);
        }
    }
    gettimeofday(&endexe, NULL);
    printf("STL Set %ld\n", 1000000*(endexe.tv_sec-startexe.tv_sec)+endexe.tv_usec-startexe.tv_usec);
    return 0;
}
