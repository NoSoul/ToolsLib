#ifndef _Matrix_H_
#define _Matrix_H_
#include <stdio.h>
#include <assert.h>
template <typename Matrix_t>
class Matrix
{
    public:
        Matrix_t *mData;
        int row, column;
        Matrix()
        {
            mData = NULL;
            row = 0;
            column = 0;
        }
        ~Matrix()
        {
            if(mData)
            {
                delete[] mData;
                mData = NULL;
            }
        }
        void ReSize(int m, int n)
        {
            if(mData)
            {
                delete[] mData;
            }
            mData = new Matrix_t[m * n];
            assert(mData);
            row = m;
            column = n;
        }
        void Set(int i, int j, Matrix_t value)
        {
            mData[i*column + j] = value;
        }
        void Add(Matrix &A, Matrix &B)
        {
            assert(A.row == B.row);
            assert(A.column == B.column);
            assert(A.row == row);
            assert(A.column == column);
            for(int i=0; i<A.row; ++i)
            {
                for(int j=0; j<A.column; ++j)
                {
                    int id = i*A.column + j;
                    mData[id] = A.mData[id] + B.mData[id];
                }
            }
        }
        void Mus(Matrix &A, Matrix &B)
        {
            assert(A.row == B.row);
            assert(A.column == B.column);
            assert(A.row == row);
            assert(A.column == column);
            for(int i=0; i<A.row; ++i)
            {
                for(int j=0; j<A.column; ++j)
                {
                    int id = i*A.column + j;
                    mData[id] = A.mData[id] - B.mData[id];
                }
            }
        }
        void Mul(Matrix &A, Matrix &B)
        {
            assert(A.column == B.row);
            assert(A.row == row);
            assert(B.column == column);
            for(int i=0; i<A.row; ++i)
            {
                for(int k=0; k<A.column; ++k)
                {
                    for(int j=0; j<B.column; ++j)
                    {
                        mData[i*B.column + j] += A.mData[i*A.column + k] * B.mData[k*B.column + j];
                    }
                }
            }
        }
        void Inv3x3()
        {
            assert(row == 3);
            assert(column == 3);
            Matrix_t a, b, c, d, e, f, g, h, i, fa;
            a = mData[0]; 
            b = mData[1]; 
            c = mData[2]; 
            d = mData[3]; 
            e = mData[4]; 
            f = mData[5]; 
            g = mData[6]; 
            h = mData[7]; 
            i = mData[8]; 
            fa = (a * e * i) - (a * f * h) - (b * d * i) + (b * f * g) + (c * d * h) - (c * e * g);
            mData[0] = (e*i - f*h) / fa;
            mData[1] = (c*h - b*i) / fa;
            mData[2] = (b*f - c*e) / fa;
            mData[3] = (f*g - d*i) / fa;
            mData[4] = (a*i - c*g) / fa;
            mData[5] = (c*d - a*f) / fa;
            mData[6] = (d*h - e*g) / fa;
            mData[7] = (b*g - a*h) / fa;
            mData[8] = (a*e - b*d) / fa;
        }
        void Atr(Matrix &A)
        {
            assert(A.row == column);
            assert(A.column == row);
            for(int i=0; i<A.row; ++i)
            {
                for(int j=0; j<A.column; ++j)
                {
                    mData[j*A.row + i] = A.mData[i*A.column + j];
                }
            }
        }
};
#endif
