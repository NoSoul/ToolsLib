#include "FIFOStd.h"
#include <pthread.h>
#include <semaphore.h>

const int loop = 1000;
FIFOStd<int> FIFO;
sem_t Sem;

void *Add(void *arg)
{
    for(int i = 0; i < loop; ++i) {
        *(FIFO.m_WritePtr) = i;
        FIFO.Push();
        sem_post(&Sem);
    }
    return arg;
}

void *Sub(void *arg)
{
    int i = 0;
    while(1) {
        sem_wait(&Sem);
        FIFO.Pop();
        printf("%d\n", FIFO.GetLength());
        if(++i == loop) {
            break;
        }
    }
    return arg;
}

int main()
{
    FIFOStd<int> C[100][10];
    FIFOStd<int> A;
    FIFOStd<double> B;
    for(int i = 0; i < 100; ++i) {
        for(int j = 0; j < 10; ++j) {
            C[i][j].ReSize(4);
        }
    }
    A.ReSize(16);
    B.ReSize(16);
    *(A.m_WritePtr) = 1;
    A.Push();
    *(A.m_WritePtr) = 2;
    A.Push();
    *(B.m_WritePtr) = 0.3;
    B.Push();
    *(B.m_WritePtr) = 0.4;
    B.Push();
    printf("len: %d\n", A.GetLength());
    printf("Tail: %d\n", *A.Pop());
    printf("len: %d\n", A.GetLength());
    A.Clear();
    printf("len: %d\n", A.GetLength());

    printf("\n");
    printf("len: %d\n", B.GetLength());
    printf("Tail: %lf\n", *B.Pop());
    printf("len: %d\n", B.GetLength());
    B.Clear();
    printf("len: %d\n", B.GetLength());

    *(C[0][0].m_WritePtr) = 1;
    C[0][0].Push();
    printf("len: %d\n", C[0][0].GetLength());

    sem_init(&Sem, 0, 0);
    FIFO.ReSize(1024);
    pthread_t taskAdd, taskSub;
    pthread_create(&taskAdd, NULL, Add, NULL);
    pthread_create(&taskSub, NULL, Sub, NULL);
    pthread_join(taskSub, NULL);
    pthread_join(taskAdd, NULL);
    sem_destroy(&Sem);
    return 0;
}
