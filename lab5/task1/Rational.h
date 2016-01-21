#pragma once


/*
Класс, моделирующий рациональное число
*/
class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

	CRational const operator-() const;
	CRational const operator+() const;
	CRational operator+=(CRational const & rational);
    CRational operator-=(CRational const & rational);
	CRational & operator*=(CRational const & number);
	CRational & operator/=(CRational const & rational);
private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);

CRational const operator+(CRational const & rational1, CRational const & rational2);

CRational const operator/(CRational const & rational1, CRational const & rational2);

const CRational operator-(CRational const & rational1, CRational const & rational2);

CRational const operator*(CRational const& rational1, CRational const& rational2);

bool operator==(CRational const & rational1, CRational const & rational2);

bool operator!=(CRational const & rational1, CRational const & rational2);

bool operator<(CRational const & rational1, CRational const & rational2);

bool operator>(CRational const & rational1, CRational const & rational2);

bool operator<=(CRational const & rational1, CRational const & rational2);

bool operator>=(CRational const & rational1, CRational const & rational2);

std::ostream & operator<<(std::ostream & stream, CRational const & rational);

std::istream & operator>>(std::istream & stream, CRational & rational);