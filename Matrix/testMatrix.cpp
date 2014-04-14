#include "Matrix.h"

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
            Show(A[i][j]);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
