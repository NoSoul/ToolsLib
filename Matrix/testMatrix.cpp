#include <stdio.h>
#include "Matrix.h"

void Init(Matrix<float> &A, Matrix<float> &B)
{
    for(int i=0; i<A.row; ++i)
    {
        for(int j=0; j<A.column; ++j)
        {
            A.Set(i, j, (i*3 + j+1)*10000);
        }
    }
    for(int i=0; i<B.row; ++i)
    {
        for(int j=0; j<B.column; ++j)
        {
            B.Set(i, j, (i*2 + j)*10000);
        }
    }
}

void Show(Matrix<float> &A)
{
    for(int i=0; i<A.row; ++i)
    {
        for(int j=0; j<A.column; ++j)
        {
            printf("%f ", A.mData[i*A.column + j]);
        }
        printf("\n");
    }
}

int main()
{
    Matrix<float> A(2, 3);
    Matrix<float> B(3 ,2);
    Matrix<float> D(3, 3);
    Init(A, B);
    Show(A);
    Show(B);
    printf("\n");

    A.Add(A, A);
    B.Mus(B, B);
    Show(A);
    Show(B);
    printf("\n");

    Init(A, B);
    D.Mul(B, A);
    Show(D);
    printf("\n");

    D.Inv3x3();
    Show(D);
    printf("\n");

    Init(A, B);
    Show(A);
    Show(B);
    printf("\n");
    B.Atr(A);
    Show(B);
    printf("\n");

    return 0;
}
