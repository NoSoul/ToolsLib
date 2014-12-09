#ifndef _Complex8_H_
#define _Complex8_H_
#include <immintrin.h>
#include <string.h>
#include <assert.h>
#define PARALLEL_OP    8
class Complex8
{
public:
    Complex8()
    {
    }
    Complex8(float *real, float *imag)
    {
        memcpy(mReal, real, sizeof(mReal));
        memcpy(mImag, imag, sizeof(mImag));
    }
    Complex8 &operator=(const Complex8 &source)
    {
        memcpy(mReal, source.mReal, sizeof(mReal));
        memcpy(mImag, source.mImag, sizeof(mImag));
        return *this;
    }
    float mReal[PARALLEL_OP];
    float mImag[PARALLEL_OP];
    void SetData(int id, float r, float i)
    {
        assert(id < PARALLEL_OP && id >= 0);
        mReal[id] = r;
        mImag[id] = i;
    }
    void LoadData(float *real, float *imag)
    {
        memcpy(mReal, real, sizeof(mReal));
        memcpy(mImag, imag, sizeof(mImag));
    }

    void Mag(float *res)
    {
        __m256 avx_r, avx_i;
        avx_r = _mm256_loadu_ps(mReal);
        avx_i = _mm256_loadu_ps(mImag);
        _mm256_storeu_ps(res, _mm256_sqrt_ps(_mm256_add_ps(_mm256_mul_ps(avx_r, avx_r), _mm256_mul_ps(avx_i, avx_i))));
    }
    void MagSqr(float *res)
    {
        __m256 avx_r, avx_i;
        avx_r = _mm256_loadu_ps(mReal);
        avx_i = _mm256_loadu_ps(mImag);
        _mm256_storeu_ps(res, _mm256_add_ps(_mm256_mul_ps(avx_r, avx_r), _mm256_mul_ps(avx_i, avx_i)));
    }
    Complex8 Conjugate()
    {
        Complex8 res;
        _mm256_storeu_ps(res.mReal, _mm256_loadu_ps(mReal));
        _mm256_storeu_ps(res.mImag, _mm256_sub_ps(_mm256_set1_ps(0), _mm256_loadu_ps(mImag)));
        return res;
    }
    Complex8 Rcp()
    {
        Complex8 res;
        memset(res.mReal, 1, sizeof(float)*PARALLEL_OP);
        memset(res.mImag, 0, sizeof(float)*PARALLEL_OP);
        res /= *this;
        return res;
    }

    Complex8 operator-()
    {
        Complex8 res;
        __m256 avx_zero;
        avx_zero = _mm256_set1_ps(0);
        _mm256_storeu_ps(res.mReal, _mm256_sub_ps(avx_zero, _mm256_loadu_ps(mReal)));
        _mm256_storeu_ps(res.mImag, _mm256_sub_ps(avx_zero, _mm256_loadu_ps(mImag)));
        return res;
    }
    int operator==(Complex8 &A)
    {
        return _mm256_testc_ps(_mm256_loadu_ps(mReal), _mm256_loadu_ps(A.mReal)) && _mm256_testc_ps(_mm256_loadu_ps(mImag), _mm256_loadu_ps(A.mImag));
    }
    bool operator!=(Complex8 &A)
    {
        return _mm256_testc_ps(_mm256_loadu_ps(mReal), _mm256_loadu_ps(A.mImag)) == 0 || _mm256_testc_ps(_mm256_loadu_ps(mReal), _mm256_loadu_ps(A.mImag)) == 0;
    }
    bool equal(Complex8 &A, int idx)
    {
        return A.mReal[idx] == mReal[idx] && A.mImag[idx] == mImag[idx];
    }

    Complex8 operator+(Complex8 &A)
    {
        Complex8 res;
        _mm256_storeu_ps(res.mReal, _mm256_add_ps(_mm256_loadu_ps(mReal), _mm256_loadu_ps(A.mReal)));
        _mm256_storeu_ps(res.mImag, _mm256_add_ps(_mm256_loadu_ps(mImag), _mm256_loadu_ps(A.mImag)));
        return res;
    }
    Complex8 operator-(Complex8 &A)
    {
        Complex8 res;
        _mm256_storeu_ps(res.mReal, _mm256_sub_ps(_mm256_loadu_ps(mReal), _mm256_loadu_ps(A.mReal)));
        _mm256_storeu_ps(res.mImag, _mm256_sub_ps(_mm256_loadu_ps(mImag), _mm256_loadu_ps(A.mImag)));
        return res;
    }
    Complex8 operator*(Complex8 &A)
    {
        Complex8 res;
        __m256 avx_r, avx_i, avx_pr, avx_pi;
        avx_r = _mm256_loadu_ps(mReal);
        avx_i = _mm256_loadu_ps(mImag);
        avx_pr = _mm256_loadu_ps(A.mReal);
        avx_pi = _mm256_loadu_ps(A.mImag);
        _mm256_storeu_ps(res.mReal, _mm256_sub_ps(_mm256_mul_ps(avx_r, avx_pr), _mm256_mul_ps(avx_i, avx_pi)));
        _mm256_storeu_ps(res.mImag, _mm256_add_ps(_mm256_mul_ps(avx_r, avx_pi), _mm256_mul_ps(avx_i, avx_pr)));
        return res;
    }
    Complex8 operator/(Complex8 &A)
    {
        Complex8 res;
        __m256 avx_r, avx_i, avx_pr, avx_pi, avx_de;
        avx_r = _mm256_loadu_ps(mReal);
        avx_i = _mm256_loadu_ps(mImag);
        avx_pr = _mm256_loadu_ps(A.mReal);
        avx_pi = _mm256_loadu_ps(A.mImag);
        float div_de[PARALLEL_OP];
        bool flag[PARALLEL_OP] = {false};
        A.MagSqr(div_de);
        for(int i = 0; i < PARALLEL_OP; ++i)
        {
            if(div_de[i] == 0.0f)
            {
                div_de[i] = 1;
                flag[i] = true;
            }
        }
        avx_de = _mm256_loadu_ps(div_de);
        _mm256_storeu_ps(res.mReal, _mm256_div_ps(_mm256_add_ps(_mm256_mul_ps(avx_r, avx_pr), _mm256_mul_ps(avx_i, avx_pi)), avx_de));
        _mm256_storeu_ps(res.mImag, _mm256_div_ps(_mm256_sub_ps(_mm256_mul_ps(avx_i, avx_pr), _mm256_mul_ps(avx_r, avx_pi)), avx_de));
        for(int i = 0; i < PARALLEL_OP; ++i)
        {
            if(flag[i])
            {
                res.SetData(i, 0, 0);
            }
        }
        return res;
    }

    Complex8 operator+(float A)
    {
        Complex8 res;
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(res.mReal, _mm256_add_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(res.mImag, _mm256_add_ps(_mm256_loadu_ps(mImag), avx_a));
        return res;
    }
    Complex8 operator-(float A)
    {
        Complex8 res;
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(res.mReal, _mm256_sub_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(res.mImag, _mm256_sub_ps(_mm256_loadu_ps(mImag), avx_a));
        return res;
    }
    Complex8 operator*(float A)
    {
        Complex8 res;
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(res.mReal, _mm256_mul_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(res.mImag, _mm256_mul_ps(_mm256_loadu_ps(mImag), avx_a));
        return res;
    }
    Complex8 operator/(float A)
    {
        Complex8 res;
        if(A == 0)
        {
            memset(res.mReal, 0, sizeof(res.mReal));
            memset(res.mImag, 0, sizeof(res.mImag));
            return res;
        }
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(res.mReal, _mm256_div_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(res.mImag, _mm256_div_ps(_mm256_loadu_ps(mImag), avx_a));
        return res;
    }

    void operator+=(Complex8 &A)
    {
        _mm256_storeu_ps(mReal, _mm256_add_ps(_mm256_loadu_ps(mReal), _mm256_loadu_ps(A.mReal)));
        _mm256_storeu_ps(mImag, _mm256_add_ps(_mm256_loadu_ps(mImag), _mm256_loadu_ps(A.mImag)));
    }
    void operator-=(Complex8 &A)
    {
        _mm256_storeu_ps(mReal, _mm256_sub_ps(_mm256_loadu_ps(mReal), _mm256_loadu_ps(A.mReal)));
        _mm256_storeu_ps(mImag, _mm256_sub_ps(_mm256_loadu_ps(mImag), _mm256_loadu_ps(A.mImag)));
    }
    void operator*=(Complex8 &A)
    {
        __m256 avx_r, avx_i, avx_pr, avx_pi;
        avx_r = _mm256_loadu_ps(mReal);
        avx_i = _mm256_loadu_ps(mImag);
        avx_pr = _mm256_loadu_ps(A.mReal);
        avx_pi = _mm256_loadu_ps(A.mImag);
        _mm256_storeu_ps(mReal, _mm256_sub_ps(_mm256_mul_ps(avx_r, avx_pr), _mm256_mul_ps(avx_i, avx_pi)));
        _mm256_storeu_ps(mImag, _mm256_add_ps(_mm256_mul_ps(avx_r, avx_pi), _mm256_mul_ps(avx_i, avx_pr)));
    }
    void operator/=(Complex8 &A)
    {
        __m256 avx_r, avx_i, avx_pr, avx_pi, avx_de;
        avx_r = _mm256_loadu_ps(mReal);
        avx_i = _mm256_loadu_ps(mImag);
        avx_pr = _mm256_loadu_ps(A.mReal);
        avx_pi = _mm256_loadu_ps(A.mImag);
        float div_de[PARALLEL_OP];
        bool flag[PARALLEL_OP] = {false};
        A.MagSqr(div_de);
        for(int i = 0; i < PARALLEL_OP; ++i)
        {
            if(div_de[i] == 0.0f)
            {
                div_de[i] = 1;
                flag[i] = true;
            }
        }
        avx_de = _mm256_loadu_ps(div_de);
        _mm256_storeu_ps(mReal, _mm256_div_ps(_mm256_add_ps(_mm256_mul_ps(avx_r, avx_pr), _mm256_mul_ps(avx_i, avx_pi)), avx_de));
        _mm256_storeu_ps(mImag, _mm256_div_ps(_mm256_sub_ps(_mm256_mul_ps(avx_i, avx_pr), _mm256_mul_ps(avx_r, avx_pi)), avx_de));
        for(int i = 0; i < PARALLEL_OP; ++i)
        {
            if(flag[i])
            {
                SetData(i, 0, 0);
            }
        }
    }

    void operator+=(float A)
    {
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(mReal, _mm256_add_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(mImag, _mm256_add_ps(_mm256_loadu_ps(mImag), avx_a));
    }
    void operator-=(float A)
    {
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(mReal, _mm256_sub_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(mImag, _mm256_sub_ps(_mm256_loadu_ps(mImag), avx_a));
    }
    void operator*=(float A)
    {
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(mReal, _mm256_mul_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(mImag, _mm256_mul_ps(_mm256_loadu_ps(mImag), avx_a));
    }
    void operator/=(float A)
    {
        if(A == 0)
        {
            memset(mReal, 0, sizeof(mReal));
            memset(mImag, 0, sizeof(mImag));
            return;
        }
        __m256 avx_a;
        avx_a = _mm256_set1_ps(A);
        _mm256_storeu_ps(mReal, _mm256_div_ps(_mm256_loadu_ps(mReal), avx_a));
        _mm256_storeu_ps(mImag, _mm256_div_ps(_mm256_loadu_ps(mImag), avx_a));
    }
};
#endif
