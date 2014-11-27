#include "PtEvent.h"
#include <stdio.h>
#include <unistd.h>

PtEvent SysEvent(10);

void *Fun2(void *arg)
{
    while(1)
    {
        SysEvent.Wait(1);
        printf("0\n");
    }
    return NULL;
}
void *Fun1(void *arg)
{
    while(1)
    {
        for(int i = 0; i < 10; ++i)
        {
            printf("Set %d\n", i);
            SysEvent.Set(i);
            sleep(1);
        }
    }
    return NULL;
}

int main()
{
    pthread_t id2;
    pthread_create(&id2, NULL, Fun2, NULL);
    pthread_t id1;
    pthread_create(&id1, NULL, Fun1, NULL);
    pthread_join(id1, NULL);
    return 0;
}
