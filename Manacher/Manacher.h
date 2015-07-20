#ifndef _Manacher_H_
#define _Manacher_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define HEADCHAR        '$'
#define SEPARATIONCHAR  '#'
char *Manacher(char *str)
{
    int originLen = strlen(str);
    int transLen = originLen << 1;
    char *transStr = (char*)malloc(sizeof(char) * (transLen + 1));
    if(transStr == NULL) {
        return NULL;
    }
    int i;
    transStr[0] = HEADCHAR;
    transStr[1] = str[0];
    for(i = 1; i < originLen; ++i) {
        transStr[i << 1] = SEPARATIONCHAR;
        transStr[i << 1 | 1] = str[i];
    }
    transStr[transLen] = '\0';
    int *P = (int*)malloc(sizeof(int) * transLen);
    if(P == NULL) {
        return NULL;
    }
    P[0] = 0;
    int id, mx, maxLen, maxId;
    id = mx = maxLen = maxId = 0;
    for(i = 1; i < transLen; ++i) {
        if(mx > i) {
            P[i] = mx - i;
            int j = (id << 1) - i;
            if(P[i] > P[j]) {
                P[i] = P[j];
            }
        } else {
            P[i] = 0;
        }
        while(transStr[i + P[i] + 1] == transStr[i - P[i] - 1]) {
            ++P[i];
        }
        if(i + P[i] > mx) {
            id = i;
            mx = i + P[i];
        }
        if(P[i] > maxLen) {
            maxLen = P[i];
            maxId = i;
        }
    }
    if(transStr[maxId - maxLen] == SEPARATIONCHAR) {
        --maxLen;
    }
    int originBeg = (maxId - maxLen) >> 1;
    if(maxLen == 0) {
        originBeg = 0;
    }
    int originEnd = originBeg + maxLen + 1;
    printf("%s\tfind: ", str);
    for(i = originBeg; i < originEnd; ++i) {
        putchar(str[i]);
    }
    puts("");
    free(P);
    free(transStr);
    return str;
}
#endif
