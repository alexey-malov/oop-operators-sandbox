#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <assert.h>
#include <stdexcept>
#include <string>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	assert(m_denominator > 0);
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

double CRational::ToDouble() const
{
	return (static_cast<double>(m_numerator) / m_denominator);
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
    int integerPart = m_numerator / m_denominator;

    int numarator = (integerPart != 0) ? std::abs(m_numerator) : m_numerator;
    int fractionPartNumerator = numarator % m_denominator;
    CRational fractionPart = CRational(fractionPartNumerator, m_denominator);

    return std::pair<int, CRational>(integerPart, fractionPart);
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

CRational const operator+(CRational const & rational1, CRational const & rational2)
{
	int resultDenominator = rational1.GetDenominator() * rational2.GetDenominator();
	int resultNumerator1 = rational1.GetNumerator() * rational2.GetDenominator();
	int resultNumerator2 = rational2.GetNumerator() * rational1.GetDenominator();
	int resultNumerator = resultNumerator1 + resultNumerator2;
	return CRational(resultNumerator, resultDenominator);
}

const CRational operator-(CRational const & rational1, CRational const & rational2)
{
	int resultNumerator = rational1.GetNumerator() * rational2.GetDenominator() - rational2.GetNumerator() * rational1.GetDenominator();
	int resultDenominator = rational1.GetDenominator() * rational2.GetDenominator();
	return CRational(resultNumerator, resultDenominator);
}

CRational CRational::operator+=(CRational const & rational)
{
	m_numerator = (rational.GetNumerator() * m_denominator) + (m_numerator * rational.GetDenominator());
	m_denominator *= rational.GetDenominator();
	Normalize();
	return *this;
}

CRational CRational::operator-=(CRational const & rational)
{
    m_numerator = (m_numerator * rational.GetDenominator()) - (rational.GetNumerator() * m_denominator);
    m_denominator *= rational.GetDenominator();
    Normalize();
    return *this;
}

CRational const operator*(CRational const& rational1, CRational const& rational2)
{
	int resultNumerator = rational1.GetNumerator() * rational2.GetNumerator();
	int resultDenominator = rational1.GetDenominator() * rational2.GetDenominator();

	return CRational(resultNumerator, resultDenominator);
}

CRational const operator/(CRational const & rational1, CRational const & rational2)
{
    int resultDenominator = rational1.GetDenominator() * rational2.GetNumerator();
    int resultNumerator = rational1.GetNumerator() * rational2.GetDenominator();
    return CRational(resultNumerator, resultDenominator);
}

CRational & CRational::operator*=(CRational const & number)
{
	m_numerator *= number.GetNumerator();
	m_denominator *= number.GetDenominator();
	Normalize();
	return *this;
}

CRational & CRational::operator/=(CRational const & rational)
{
	m_numerator *= rational.GetDenominator();
	m_denominator *= rational.GetNumerator();
	Normalize();
	return *this;
}

bool operator==(CRational const & rational1, CRational const & rational2)
{
    bool isNumeratorEqual = (rational1.GetNumerator() == rational2.GetNumerator());
    bool isDenominatorEqual = (rational1.GetDenominator() == rational2.GetDenominator());
    return isNumeratorEqual && isDenominatorEqual;
}

bool operator!=(CRational const & rational1, CRational const & rational2)
{
	return !(rational1 == rational2);
}

bool operator<(CRational const & rational1, CRational const & rational2)
{
    int result1 = rational1.GetNumerator() * rational2.GetDenominator();
    int result2 = rational2.GetNumerator() * rational1.GetDenominator();
    return (result1 < result2);
}

bool operator>(CRational const & rational1, CRational const & rational2)
{
    int result1 = rational1.GetNumerator() * rational2.GetDenominator();
    int result2 = rational2.GetNumerator() * rational1.GetDenominator();
    return (result1 > result2);
}

bool operator<=(CRational const & rational1, CRational const & rational2)
{
    return !(rational1 > rational2);
}

bool operator>=(CRational const & rational1, CRational const & rational2)
{
    return !(rational1 < rational2);
}

std::ostream & operator<<(std::ostream & stream, CRational const & rational)
{
	stream << rational.GetNumerator() << "/" << rational.GetDenominator();
	return stream;
}

std::istream & operator>>(std::istream & stream, CRational & rational)
{
    int numerator, denominator;
    if ((stream >> numerator) && 
        (stream.get() == '/') && 
        (stream >> denominator))
    {
        rational = CRational(numerator, denominator);
    }
    else
    {
        stream.setstate(stream.rdstate() | std::ios_base::failbit);
    }
    return stream;
}

