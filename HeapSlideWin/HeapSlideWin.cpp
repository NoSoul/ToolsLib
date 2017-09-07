#include "HeapSlideWin.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sys/time.h>
using namespace std;

int main()
{
    const int n = 800;
    const int m = 400;
    const int l = 3 * n;
    int resA[l], resB[l];
    int origin[l];
    int array[n], writeIdx = 0, count = 0, arrayBefore[n];
    for(int i = 0; i < l; ++i) {
        origin[i] = rand() & 65535;
    }
    HeapSlideWin<int> curTest(n, m, true);
    struct timeval startexe, endexe;
    gettimeofday(&startexe, NULL);
    for(int i = 0; i < l; ++i) {
        curTest.HeapSlideWinPush(origin[i]);
        resA[i] = curTest.HeapSlideWinGetVal();
    }
    gettimeofday(&endexe, NULL);
    printf("Takes %ld us\n", 1000000 * (endexe.tv_sec - startexe.tv_sec) + endexe.tv_usec - startexe.tv_usec);
    gettimeofday(&startexe, NULL);
    for(int i = 0; i < l; ++i) {
        arrayBefore[writeIdx] = origin[i];
        if(++writeIdx == n) {
            writeIdx = 0;
        }
        if(++count >= n) {
            count = n;
        }
        memcpy(array, arrayBefore, count * sizeof(int));
        sort(array, array + count);
        int len = count < m ? count : m;
        int sum = 0;
        for(int j = 0; j < len; ++j) {
            sum += array[count - 1 - j];
        }
        resB[i] = sum / len;
    }
    gettimeofday(&endexe, NULL);
    printf("Takes %ld us\n", 1000000 * (endexe.tv_sec - startexe.tv_sec) + endexe.tv_usec - startexe.tv_usec);
    for(int i = 0; i < l; ++i) {
        if(resA[i] != resB[i]) {
            printf("ERROR %d %d %d\n", i, resA[i], resB[i]);
            return 0;
        }
    }
    return 0;
}
