#ifndef _ComplexMatrix_H_
#define _ComplexMatrix_H_
#include "Matrix.h"
#include "../Complex/Complex8.h"
class ComplexMatrix:public Matrix<Complex8>
{
    public:
        ComplexMatrix &operator=(const ComplexMatrix &source)
        {
            if(row*column != source.row*source.column)
            {
                ReSize(source.row, source.column);
            }
            row = source.row;
            column = source.column;
            memcpy(mData, source.mData, sizeof(Complex8)*row*column);
            return *this;
        }
        ComplexMatrix operator+(const ComplexMatrix &A)
        {
            assert(A.row == row);
            assert(A.column == column);
            ComplexMatrix res;
            res.ReSize(row, column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    int id = i*column + j;
                    res.mData[id] = mData[id] + A.mData[id];
                }
            }
            return res;
        }
        ComplexMatrix operator*(const ComplexMatrix &A)
        {
            assert(column == A.row);
            ComplexMatrix res;
            res.ReSize(row, A.column);
            memset(res.mData, 0, sizeof(Complex8)*row*A.column);
            for(int i=0; i<row; ++i)
            {
                for(int k=0; k<column; ++k)
                {
                    for(int j=0; j<A.column; ++j)
                    {
                        Complex8 temp = mData[i*column + k] * A.mData[k*A.column + j];
                        res.mData[i*A.column + j] += temp;
                    }
                }
            }
            return res;
        }
        ComplexMatrix operator*(const float a)
        {
            ComplexMatrix res;
            res.ReSize(row, column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    int id = i*column + j;
                    res.mData[id] = mData[id] * a;
                }
            }
            return res;      
        }
        void operator+=(const ComplexMatrix A)
        {
            assert(A.row == row);
            assert(A.column == column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    int id = i*column + j;
                    mData[id] += A.mData[id];
                }
            }
        }
        void Set(int i, int j, int idx, float real, float imag)
        {
            assert(i < row);
            assert(j < column);
            mData[i*column + j].SetData(idx, real, imag);
        }
        void Set(int i, int j, Complex8 value)
        {
            assert(i < row);
            assert(j < column);
            mData[i*column + j] = value;
        }
        ComplexMatrix Inv2x2()
        {
            assert(row == 2);
            assert(column == 2);
            ComplexMatrix res;
            res.ReSize(row, column);
            Complex8 a, b, c, d, fa, A, B;
            a = mData[0]; 
            b = mData[1]; 
            c = mData[2]; 
            d = mData[3];
            A = a*d;
            B = b*c;
            fa = A - B;
            res.Set(0, 0, d / fa);
            res.Set(0, 1, -b / fa);
            res.Set(1, 0, -c / fa);
            res.Set(1, 1, a / fa);
            return res;
        }
        ComplexMatrix ComplexConj()
        {
            ComplexMatrix res;
            res.ReSize(row, column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    res.mData[i*column +j] = mData[i*column + j].Conjugate();
                }
            }
            return res;
        }
        ComplexMatrix ComplexConjAtr()
        {
            ComplexMatrix res;
            res.ReSize(column, row);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    res.mData[j*row + i] = mData[i*column + j].Conjugate();
                }
            }
            return res;
        }
        ComplexMatrix ComplexEye(const int n)
        {
            ComplexMatrix res;
            res.ReSize(n, n);
            float real_0[PARALLEL_OP] = {0};
            float real_1[PARALLEL_OP] = {1, 1, 1, 1, 1, 1, 1, 1};
            float imag[PARALLEL_OP] = {0};
            for(int i=0; i<n; ++i)
            {
                for(int j=0; j<n; ++j)
                {
                    if(i==j)
                    {
                        res.mData[i*n + j].LoadData(real_1, imag);
                    }
                    else
                    {
                        res.mData[i*n + j].LoadData(real_0, imag);
                    }
                }
            }
            return res;
        }
        void ComplexNorm2(float *res)
        {
            float sum[PARALLEL_OP];
            for(int i=0; i<PARALLEL_OP; ++i)
            {
                res[i] = 0.0f;
            }
            __m256 avx_sum, avx_res;
            avx_res = _mm256_loadu_ps(res);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    mData[i*column + j].MagSqr(sum);
                    avx_sum = _mm256_loadu_ps(sum);
                    avx_res = _mm256_add_ps(avx_res, avx_sum);
                }
            }
            _mm256_storeu_ps(res, avx_res);
        }
};
#endif
