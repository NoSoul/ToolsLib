#include "Manacher.h"

int main()
{
    int i;
    for(i = 0; i < 20; ++i) {
        int num = (rand() & 31) + 1;
        char *str = (char*)malloc(sizeof(char) * (num + 1));
        int j;
        for(j = 0; j < num; ++j) {
            str[j] = rand() % 26 + 'a';
        }
        str[num] = '\0';
        Manacher(str);
        free(str);
    }
    return 0;
}
