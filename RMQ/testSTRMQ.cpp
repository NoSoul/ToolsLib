#include "STRMQ.h"
#include <stdlib.h>

int main()
{
    int N = 50;
    for(int i = 0; i < N; ++i) {
        Src[i] = rand();
        printf("%d,%lld\n", i, Src[i]);
    }
    puts("");
    SetSTRMQ(Dp, Src, N, &FunCmp);
    for(int i = 0; i < 20; ++i) {
        int a = rand() % N;
        int b;
        do {
            b = rand() % N;
        } while(b <= a);
        printf("%d %d\t ", a, b);
        GetSTRMQ(Dp, Src, a, b, &FunCmp);
    }
    return 0;
}
