#pragma once
#include <iostream>
class CRational final
{
public:
	CRational();
	CRational(int numerator);
	CRational(int numerator, int denominator);
	CRational const operator -() const;
	CRational const operator +() const;
	CRational& operator += (CRational const &rational);
	CRational& operator -= (CRational const &rational);
	CRational& operator *= (CRational const &rational);
	CRational& operator /= (CRational const &rational);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	void friend LeadToCommonDenominator(CRational &first, CRational &second);
	CRational friend Normalize(int numerator, int denominator, CRational &rational);
	std::pair<int, CRational> ToCompoundFraction() const;
private:
	int m_numerator;
	int m_denominator;
};


int GCD(int a, int b);
const CRational operator + (const CRational &num1, const CRational &num2);
const CRational operator - (const CRational &num1, const CRational &num2);
const CRational operator * (const CRational &num1, const CRational &num2);
const CRational operator / (const CRational &num1, const CRational &num2);
const bool operator == (const CRational &num1, const CRational &num2);
const bool operator != (const CRational &num1, const CRational &num2);
const bool operator < (const CRational &num1, const CRational &num2);
const bool operator <= (const CRational &num1, const CRational &num2);
const bool operator > (const CRational &num1, const CRational &num2);
const bool operator >= (const CRational &num1, const CRational &num2);
std::istream & operator >>(std::istream & is, CRational &rational);
std::ostream & operator <<(std::ostream & os, const CRational &rational);