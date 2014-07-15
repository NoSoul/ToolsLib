#include "Complex8.h"
#include "Complex.h"
#include <stdio.h>

Complex8 A;
Complex B[PARALLEL_OP];

void CheckMagSqr()
{
    float MagSqr[8];
    A.MagSqr(MagSqr);
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f\n", MagSqr[i], B[i].MagSqr());
        if(MagSqr[i] != B[i].MagSqr())
        {
            printf("MagSqr ERROR!\n");
        }
    }
}

void CheckMag()
{
    float Mag[8];
    A.Mag(Mag);
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f\n", Mag[i], B[i].Mag());
        if(Mag[i] != B[i].Mag())
        {
            printf("Mag ERROR!\n");
        }
    }
}

void CheckConjugate()
{
    Complex8 res = A.Conjugate();
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", res.mReal[i], res.mImag[i], B[i].Conjugate().m_real, B[i].Conjugate().m_imag);
        if(res.mReal[i]!=B[i].Conjugate().m_real || res.mImag[i]!=B[i].Conjugate().m_imag)
        {
            printf("Conjugate ERROR!\n");
        }
    }
}

void CheckOperator_Neg()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (-A).mReal[i], (-A).mImag[i], (-B[i]).m_real, (-B[i]).m_imag);
        if((-A).mReal[i]!=(-B[i]).m_real || (-A).mImag[i]!=(-B[i]).m_imag)
        {
            printf("CheckOperator_Neg ERROR\n");
        }
    }
}

void CheckOperator_equal()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        if(!A.equal(A, i) || !A.equal(A, (i+1)%PARALLEL_OP) || !(A==A))
        {
            printf("CheckOperator_equal ERROR\n");
        }
    }
}

void CheckOperator_notequal()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        if(A!=A)
        {
            printf("CheckOperator_notequal ERROR\n");
        }
    }
}

void CheckOperator_add_complex()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A+A).mReal[i], (A+A).mImag[i], (B[i]+B[i]).m_real, (B[i]+B[i]).m_imag);
        if((A+A).mReal[i]!=(B[i]+B[i]).m_real || (A+A).mImag[i]!=(B[i]+B[i]).m_imag)
        {
            printf("CheckOperator_add_complex ERROR\n");
        }
    }
}

void CheckOperator_sub_complex()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A-A).mReal[i], (A-A).mImag[i], (B[i]-B[i]).m_real, (B[i]-B[i]).m_imag);
        if((A-A).mReal[i]!=(B[i]-B[i]).m_real || (A-A).mImag[i]!=(B[i]-B[i]).m_imag)
        {
            printf("CheckOperator_sub_complex ERROR\n");
        }
    }
}

void CheckOperator_mul_complex()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A*A).mReal[i], (A*A).mImag[i], (B[i]*B[i]).m_real, (B[i]*B[i]).m_imag);
        if((A*A).mReal[i]!=(B[i]*B[i]).m_real || (A*A).mImag[i]!=(B[i]*B[i]).m_imag)
        {
            printf("CheckOperator_mul_complex ERROR\n");
        }
    }
}

void CheckOperator_div_complex()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A/A).mReal[i], (A/A).mImag[i], (B[i]/B[i]).m_real, (B[i]/B[i]).m_imag);
        if((A/A).mReal[i]!=(B[i]/B[i]).m_real || (A/A).mImag[i]!=(B[i]/B[i]).m_imag)
        {
            printf("CheckOperator_div_complex ERROR\n");
        }
    }
}

void CheckOperator_add_float()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A+2).mReal[i], (A+2).mImag[i], (B[i]+2).m_real, (B[i]+2).m_imag);
        if((A+2).mReal[i]!=(B[i]+2).m_real || (A+2).mImag[i]!=(B[i]+2).m_imag)
        {
            printf("CheckOperator_add_float ERROR\n");
        }
    }
}

void CheckOperator_sub_float()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A-2).mReal[i], (A-2).mImag[i], (B[i]-2).m_real, (B[i]-2).m_imag);
        if((A-2).mReal[i]!=(B[i]-2).m_real || (A-2).mImag[i]!=(B[i]-2).m_imag)
        {
            printf("CheckOperator_sub_float ERROR\n");
        }
    }
}

void CheckOperator_mul_float()
{
    //printf("CheckOperator_mul_float:\n");
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A*2).mReal[i], (A*2).mImag[i], (B[i]*2).m_real, (B[i]*2).m_imag);
        if((A*2).mReal[i]!=(B[i]*2).m_real || (A*2).mImag[i]!=(B[i]*2).m_imag)
        {
            printf("CheckOperator_sub_float ERROR\n");
        }
    }
}

void CheckOperator_div_float()
{
    //printf("CheckOperator_div_float:\n");
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        //printf("%f %f --- %f %f\n", (A/2).mReal[i], (A/2).mImag[i], (B[i]/2).m_real, (B[i]/2).m_imag);
        if((A/2).mReal[i]!=(B[i]/2).m_real || (A/2).mImag[i]!=(B[i]/2).m_imag)
        {
            printf("CheckOperator_sub_float ERROR\n");
        }
    }
}

int main()
{
    for(int i=0; i<PARALLEL_OP; ++i)
    {
        int a, b;
        a = rand();
        b = rand();
        A.SetData(i, a, b);
        B[i].Set((float)a, (float)b);
    }
    CheckMagSqr();
    CheckMag();
    CheckConjugate();
    CheckOperator_Neg();
    CheckOperator_equal();
    CheckOperator_notequal();
    CheckOperator_add_complex();
    CheckOperator_sub_complex();
    CheckOperator_mul_complex();
    CheckOperator_div_complex();
    CheckOperator_add_float();
    CheckOperator_sub_float();
    CheckOperator_mul_float();
    CheckOperator_div_float();
    return 0;
}
