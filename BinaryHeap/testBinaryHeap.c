#include "BinaryHeap.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXN    11

int A[MAXN];

int main()
{
    unsigned int i = 0;
    unsigned int len = 0;
    for(i = 1; i < MAXN; ++i) {
        int num = rand();
        printf("add %d\n", num);
        BinaryHeapPush(A, &len, num);
    }
    BinaryHeapSort(A, len);
    for(i = 2; i <= len; ++i) {
        if(A[i] < A[i - 1]) {
            puts("ERROR");
        }
    }
    for(i = 1; i <= len; ++i) {
        printf("%d ", A[i]);
    }
    puts("");
    return 0;
}
