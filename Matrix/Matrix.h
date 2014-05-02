#ifndef _Matrix_H_
#define _Matrix_H_
#include <stdio.h>
#include <string.h>
#include <assert.h>
template <typename Matrix_t>
class Matrix
{
    public:
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
                mData = NULL;
            }
            mData = new Matrix_t[m * n];
            assert(mData);
            row = m;
            column = n;
        }
        void Set(int i, int j, Matrix_t value)
        {
            assert(i < row);
            assert(j < column);
            mData[i*column + j] = value;
        }
        Matrix_t Get(int i, int j)
        {
            assert(i < row);
            assert(j < column);
            return mData[i*column + j];
        }
        Matrix &operator=(const Matrix &source)
        {
            if(row*column != source.row*source.column)
            {
                ReSize(source.row, source.column);
            }
            row = source.row;
            column = source.column;
            memcpy(mData, source.mData, sizeof(Matrix_t)*row*column);
            return *this;
        }
        Matrix operator+(const Matrix &A)
        {
            assert(A.row == row);
            assert(A.column == column);
            Matrix res;
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
        Matrix operator-(const Matrix &A)
        {
            assert(A.row == row);
            assert(A.column == column);
            Matrix res;
            res.ReSize(row, column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    int id = i*column + j;
                    res.mData[id] = mData[id] - A.mData[id];
                }
            }
            return res;
        }
        Matrix operator*(const Matrix &A)
        {
            assert(column == A.row);
            Matrix res;
            res.ReSize(row, A.column);
            for(int i=0; i<row; ++i)
            {
                for(int k=0; k<column; ++k)
                {
                    for(int j=0; j<A.column; ++j)
                    {
                        res.mData[i*A.column + j] += mData[i*column + k] * A.mData[k*A.column + j];
                    }
                }
            }
            return res;
        }
        Matrix operator*(const float a)
        {
            Matrix res;
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
        Matrix operator/(const float a)
        {
            Matrix res;
            res.ReSize(row, column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    int id = i*column + j;
                    res.mData[id] = mData[id] / a;
                }
            }
            return res;        
        }
        Matrix operator-()
        {
            Matrix res;
            res.ReSize(row, column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    res.mData[i*column + j] = -mData[i*column + j];
                }
            }
            return res;
        }
        Matrix &operator+=(const Matrix &A)
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
            return *this;
        }
        Matrix &operator-=(const Matrix &A)
        {
            assert(A.row == row);
            assert(A.column == column);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    int id = i*column + j;
                    mData[id] -= A.mData[id];
                }
            }
            return *this;
        }
        Matrix Inv2x2()
        {
            assert(row == 2);
            assert(column == 2);
            Matrix res;
            res.ReSize(row, column);
            Matrix_t a, b, c, d, fa;
            a = mData[0]; 
            b = mData[1]; 
            c = mData[2]; 
            d = mData[3]; 
            fa = a*d - b*c;
            res.mData[0] = d / fa;
            res.mData[1] = -b / fa;
            res.mData[2] = -c / fa;
            res.mData[3] = a / fa;
            return res;
        }
        Matrix Inv3x3()
        {
            assert(row == 3);
            assert(column == 3);
            Matrix res;
            res.ReSize(row, column);
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
            res.mData[0] = (e*i - f*h) / fa;
            res.mData[1] = (c*h - b*i) / fa;
            res.mData[2] = (b*f - c*e) / fa;
            res.mData[3] = (f*g - d*i) / fa;
            res.mData[4] = (a*i - c*g) / fa;
            res.mData[5] = (c*d - a*f) / fa;
            res.mData[6] = (d*h - e*g) / fa;
            res.mData[7] = (b*g - a*h) / fa;
            res.mData[8] = (a*e - b*d) / fa;
            return res;
        }
        Matrix Atr()
        {
            Matrix res;
            res.ReSize(column, row);
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<column; ++j)
                {
                    res.mData[j*row + i] = mData[i*column + j];
                }
            }
            return res;
        }
    private:
        Matrix_t *mData;
};
#endif
