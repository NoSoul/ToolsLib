#ifndef Complex_h
#define Complex_h
#include <math.h>
class Complex
{
public:
    Complex(float real = 0.0f, float imag = 0.0f);
    ~Complex();
    inline Complex& operator=(const Complex& source);
    inline void Set(float real, float imag = 0.0f);

    inline float Mag() const;
    inline float MagSqr() const;
    inline Complex Conjugate() const;

    inline friend Complex operator+(const Complex& lhs, const Complex& rhs);
    inline Complex operator+=(const Complex& rhs);
    inline friend Complex operator-(const Complex& lhs, const Complex& rhs);
    inline Complex operator-=(const Complex& rhs);
    inline friend Complex operator*(const Complex& lhs, const Complex& rhs);
    inline friend Complex operator/(const Complex& lhs, const Complex& rhs);

    inline friend int operator==(const Complex& lhs, const Complex& rhs);
    inline friend int operator!=(const Complex& lhs, const Complex& rhs);
    Complex operator*(float fa)
    {
        return Complex(m_real * fa, m_imag * fa);
    }
    Complex operator/(float fa)
    {
        return Complex(m_real / fa, m_imag / fa);
    }
    Complex operator-()
    {
        return Complex(-m_real, -m_imag);
    }
    float   m_real;
    float   m_imag;
};

//_________________________________________________________
inline Complex::Complex(
    float real,
    float imag
)
{

    m_real = real;
    m_imag = imag;

}

//_________________________________________________________
inline Complex::~Complex()
{
}


//_________________________________________________________
inline Complex& Complex::operator=(
    const Complex& source
)
{

    m_real = source.m_real;
    m_imag = source.m_imag;
    return *this;

}

//_________________________________________________________
inline void Complex::Set(
    float real,
    float imag
)
{

    m_real = real;
    m_imag = imag;

}

//_________________________________________________________
inline float Complex::Mag() const
{

    return (float) sqrt(MagSqr());

}

//_________________________________________________________
inline float Complex::MagSqr() const
{

    return m_real * m_real + m_imag * m_imag;

}

//_________________________________________________________
inline Complex Complex::Conjugate() const
{

    return Complex(this->m_real, -1.0f * this->m_imag);

}

//_________________________________________________________
inline Complex operator+(
    const Complex& lhs,
    const Complex& rhs
)
{

    return Complex(lhs.m_real + rhs.m_real, lhs.m_imag + rhs.m_imag);

}


//_________________________________________________________
inline Complex Complex::operator+=(
    const Complex& rhs
)
{

    m_real += rhs.m_real;
    m_imag += rhs.m_imag;
    return *this;

}


//_________________________________________________________
inline Complex operator-(
    const Complex& lhs,
    const Complex& rhs
)
{

    return Complex(lhs.m_real - rhs.m_real, lhs.m_imag - rhs.m_imag);

}


//_________________________________________________________
inline Complex Complex::operator-=(
    const Complex& rhs
)
{

    m_real -= rhs.m_real;
    m_imag -= rhs.m_imag;
    return *this;

}


//_________________________________________________________
inline Complex operator*(
    const Complex& lhs,
    const Complex& rhs
)
{

    return Complex(lhs.m_real * rhs.m_real - lhs.m_imag * rhs.m_imag,
                   lhs.m_real * rhs.m_imag + lhs.m_imag * rhs.m_real);

}


//_________________________________________________________
inline Complex operator/(
    const Complex& lhs,
    const Complex& rhs
)
{

    Complex result(0.0f, 0.0f);

    float mag = (float)rhs.MagSqr();
    if (mag > 0.0f)
    {
        result.m_real = (lhs.m_real * rhs.m_real + lhs.m_imag * rhs.m_imag) / mag;
        result.m_imag = (lhs.m_imag * rhs.m_real - lhs.m_real * rhs.m_imag) / mag;
    }
    return result;

}


//_________________________________________________________
inline int operator==(
    const Complex& lhs,
    const Complex& rhs
)
{

    return ((lhs.m_real == rhs.m_real) && (lhs.m_imag == rhs.m_imag));

}


//_________________________________________________________
inline int operator!=(
    const Complex& lhs,
    const Complex& rhs
)
{

    return ((lhs.m_real != rhs.m_real) || (lhs.m_imag != rhs.m_imag));

}



#endif	//ifndef Complex_h
