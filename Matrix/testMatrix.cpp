#include "Matrix.h"

void Show(Matrix<float> &A)
{
    for(int i=0; i<A.row; ++i)
    {
        for(int j=0; j<A.column; ++j)
        {
            printf("%f ", A.Get(i, j));
        }
        printf("\n");
    }
}

int main()
{
    Matrix<float> A[2][3];
    Matrix<float> B, D;
    B.ReSize(3, 2);
    D.ReSize(3, 3);
    for(int i=0; i<2; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            A[i][j].ReSize(4, 4);
            for(int r=0; r<A[i][j].row; ++r)
            {
                for(int c=0; c<A[i][j].column; ++c)
                {
                    A[i][j].Set(r, c, 1);
                }
            }
        }
    }
    A[0][0] = A[0][1] + A[0][2];
    Show(A[0][0]);
    A[0][0] = A[0][1] - A[0][2];
    Show(A[0][0]);
    D.Set(0, 0, 1);
    B.Set(0, 0, 1);
    A[0][0] = D*B;
    Show(A[0][0]);

    B.Set(0, 0, 10);
    Show(B);
    B = A[0][0];
    Show(B);

    D.ReSize(3, 2);
    A[0][1] = D.Atr();
    Show(B);
    Show(A[0][1]);
    return 0;
}
