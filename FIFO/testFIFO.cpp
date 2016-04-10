#include "FIFOStd.h"

class FIFOInt: public FIFOStd<int>
{
public:
    void SetData(int num)
    {
        *m_WritePtr = num;
        if(!Push()) {
            printf("FIFOInt full By Push %d\n", num);
            quick_exit(0);
        }
    }
};

int main()
{
    FIFOInt A[2][2];
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            A[i][j].ReSize((i + 1) * 128);
        }
    }
    A[0][0].ReSize(64);
    A[0][0].SetData(12);
    printf("A[0][0] Have %llu\n", A[0][0].GetLength());
    A[0][0].Clear();
    printf("A[0][0] Have %llu\n", A[0][0].GetLength());

    A[0][0].SetProtectInterval(5);
    for(int i = 1; i < 10; ++i) {
        A[0][0].SetData(i);
        printf("After Push %d FIFOStd Have %llu\n", i, A[0][0].GetLength());
    }
    for(int i = 10; i <= 100; ++i) {
        if(A[0][0].GetLength() > 10) {
            A[0][0].CommitRead(10);
            for(int i = -5; i <= 0; ++i) {
                printf("%d ", *A[0][0].Watch(i));
            }
            puts("");
        }
        A[0][0].SetData(i);
        printf("After Push %d FIFOStd Have %llu\n", i, A[0][0].GetLength());
    }
    return 0;
}
