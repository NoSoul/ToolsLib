#include "ComplexMatrix.h"

void Show(ComplexMatrix &A)
{
    for(int i = 0; i < A.row; ++i)
    {
        for(int j = 0; j < A.column; ++j)
        {
            //for(int k=0; k<PARALLEL_OP; ++k)
            for(int k = 0; k < 1; ++k)
            {
                printf("%f+%fj ", A.Get(i, j).mReal[k], A.Get(i, j).mImag[k]);
            }
            printf("\t");
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    ComplexMatrix A, B, C;
    A.ReSize(3, 2);
    A = A.ComplexEye(3);
    A.Set(0, 1, 0, 1, 1);
    Show(A);
    B = A.ComplexConj();
    Show(B);
    C = A.ComplexConjAtr();
    Show(C);
    float sum[PARALLEL_OP];
    A.ComplexNorm2(sum);
    for(int i = 0; i < PARALLEL_OP; ++i)
    {
        printf("%f\n", sum[i]);
    }
    return 0;
}
