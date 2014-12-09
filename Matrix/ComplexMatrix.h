#ifndef _ComplexMatrix_H_
#define _ComplexMatrix_H_
#include "Matrix.h"
#include "../Complex/Complex8.h"
class ComplexMatrix: public Matrix<Complex8>
{
public:
    ComplexMatrix &operator=(const ComplexMatrix &source)
    {
        if(row * column != source.row * source.column)
        {
            ReSize(source.row, source.column);
        }
        row = source.row;
        column = source.column;
        memcpy(mData, source.mData, sizeof(Complex8)*row * column);
        return *this;
    }
    void MulBy(const ComplexMatrix &A, const ComplexMatrix &B)
    {
        assert(A.column == B.row);
        if(row * column != A.row * B.column)
        {
            ReSize(A.row, B.column);
        }
        memset(mData, 0, sizeof(Complex8)*A.row * B.column);
        Complex8 temp;
        for(int i = 0; i < A.row; ++i)
        {
            for(int k = 0; k < A.column; ++k)
            {
                for(int j = 0; j < B.column; ++j)
                {
                    temp = A.mData[i * A.column + k] *
                           B.mData[k * B.column + j];
                    mData[i * B.column + j] += temp;
                }
            }
        }
    }
    void MulBy(const ComplexMatrix &source, const float a)
    {
        if(row * column != source.row * source.column)
        {
            ReSize(source.row, source.column);
        }
        for(int i = 0; i < source.row; ++i)
        {
            for(int j = 0; j < source.column; ++j)
            {
                int id = i * column + j;
                mData[id] = source.mData[id] * a;
            }
        }
    }
    void operator+=(const ComplexMatrix &A)
    {
        assert(A.row == row);
        assert(A.column == column);
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < column; ++j)
            {
                int id = i * column + j;
                mData[id] += A.mData[id];
            }
        }
    }
    void Set(int i, int j, int idx, float real, float imag)
    {
        assert(i < row);
        assert(j < column);
        mData[i * column + j].SetData(idx, real, imag);
    }
    void Set(int i, int j, Complex8 value)
    {
        assert(i < row);
        assert(j < column);
        mData[i * column + j] = value;
    }
    void Inv1x1By(const ComplexMatrix &source)
    {
        assert(source.row == 1);
        assert(source.column == 1);
        if(row * column != 1)
        {
            ReSize(1, 1);
        }
        mData[0] = source.mData[0].Rcp();
    }
    void Inv2x2By(const ComplexMatrix &source)
    {
        assert(source.row == 2);
        assert(source.column == 2);
        if(row * column != 4)
        {
            ReSize(2, 2);
        }
        Complex8 a, b, c, d, fa, A, B;
        a = source.mData[0];
        b = source.mData[1];
        c = source.mData[2];
        d = source.mData[3];
        A = a * d;
        B = b * c;
        fa = A - B;
        Set(0, 0, d / fa);
        Set(0, 1, -b / fa);
        Set(1, 0, -c / fa);
        Set(1, 1, a / fa);
    }
    void ConjAtrBy(const ComplexMatrix &source)
    {
        if(row * column != source.row * source.column)
        {
            ReSize(source.column, source.row);
        }
        for(int i = 0; i < source.row; ++i)
        {
            for(int j = 0; j < source.column; ++j)
            {
                mData[j * source.row + i] =
                    source.mData[i * source.column + j].Conjugate();
            }
        }
    }
    ComplexMatrix ComplexEye(const int n)
    {
        ComplexMatrix res;
        res.ReSize(n, n);
        float real_0[PARALLEL_OP] = {0};
        float real_1[PARALLEL_OP] = {1, 1, 1, 1, 1, 1, 1, 1};
        float imag[PARALLEL_OP] = {0};
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(i == j)
                {
                    res.mData[i * n + j].LoadData(real_1, imag);
                }
                else
                {
                    res.mData[i * n + j].LoadData(real_0, imag);
                }
            }
        }
        return res;
    }
};
#endif
