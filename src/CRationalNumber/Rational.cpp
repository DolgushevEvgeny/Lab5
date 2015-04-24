#include "stdafx.h"
#include "Rational.h"
#include <algorithm>
#include <iostream>
#include <string>

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{

}

CRational::CRational(int numerator)
	: m_numerator(numerator)
	, m_denominator(1)
{

}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	m_numerator = denominator < 0 ? -m_numerator : m_numerator;
	m_denominator = denominator < 0 ? -m_denominator : m_denominator;
	int commonDenominator = GCD(numerator, denominator);
	m_numerator /= commonDenominator;
	m_denominator /= commonDenominator;
}

double  CRational::ToDouble() const
{
	return (double)m_numerator / (double)m_denominator;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

CRational const CRational::operator -() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator +() const
{
	return *this;
}

const CRational operator - (const CRational &num1, const CRational &num2)
{
	CRational first(num1);
	CRational second(num2);
	LeadToCommonDenominator(first, second);
	CRational result(first.GetNumerator() - second.GetNumerator(), first.GetDenominator());
	int commonDenominator = GCD(result.GetNumerator(), result.GetDenominator());
	return CRational((first.GetNumerator() - second.GetNumerator()) / commonDenominator, first.GetDenominator() / commonDenominator);
}

const CRational operator + (const CRational &num1, const CRational &num2)
{
	CRational first(num1);
	CRational second(num2);
	LeadToCommonDenominator(first, second);
	CRational result(first.GetNumerator() + second.GetNumerator(), first.GetDenominator());
	int commonDenominator = GCD(result.GetNumerator(), result.GetDenominator());
	return CRational((first.GetNumerator() + second.GetNumerator()) / commonDenominator, first.GetDenominator() / commonDenominator);
}

const CRational operator * (const CRational &num1, const CRational &num2)
{
	CRational result(num1.GetNumerator() * num2.GetNumerator(), num1.GetDenominator() * num2.GetDenominator());
	int commonDenominator = GCD(result.GetNumerator(), result.GetDenominator());
	return CRational(result.GetNumerator() / commonDenominator, result.GetDenominator() / commonDenominator);
}

const CRational operator / (const CRational &num1, const CRational &num2)
{
	CRational result(num1.GetNumerator() * num2.GetDenominator(), num1.GetDenominator() * num2.GetNumerator());
	int commonDenominator = GCD(result.GetNumerator(), result.GetDenominator());
	return CRational(result.GetNumerator() / commonDenominator, result.GetDenominator() / commonDenominator);
}

CRational& CRational::operator += (CRational const& rational)
{
	CRational second(rational);
	LeadToCommonDenominator(*this, second);
	m_numerator += second.m_numerator;
	int commonDenominator = GCD(m_numerator, m_denominator);
	m_numerator /= commonDenominator;
	m_denominator /= commonDenominator;
	return *this;
}

CRational& CRational::operator -= (CRational const &rational)
{
	CRational second(rational);
	LeadToCommonDenominator(*this, second);
	m_numerator -= second.m_numerator;
	int commonDenominator = GCD(m_numerator, m_denominator);
	m_numerator /= commonDenominator;
	m_denominator /= commonDenominator;
	return *this;
}

CRational& CRational::operator *= (CRational const &rational)
{
	int commonDenominator = GCD(m_numerator *= rational.m_numerator, m_denominator *= rational.m_denominator);
	m_numerator /= commonDenominator;
	m_denominator /= commonDenominator;
	return *this;
}

CRational& CRational::operator /= (CRational const &rational)
{
	int commonDenominator = GCD(m_numerator *= rational.m_denominator, m_denominator *= rational.m_numerator);
	m_numerator /= commonDenominator;
	m_denominator /= commonDenominator;
	return *this;
}

const bool operator == (const CRational &num1, const CRational &num2)
{
	return (num1.GetNumerator() == num2.GetNumerator() && num1.GetDenominator() == num2.GetDenominator());
}

const bool operator != (const CRational &num1, const CRational &num2)
{
	return !(num1 == num2);
}

const bool operator < (const CRational &num1, const CRational &num2)
{
	CRational first(num1);
	CRational second(num2);
	LeadToCommonDenominator(first, second);
	return (first.GetNumerator() < second.GetNumerator());
}

const bool operator <= (const CRational &num1, const CRational &num2)
{
	return (!(num1 > num2));
}

const bool operator > (const CRational &num1, const CRational &num2)
{
	CRational first(num1);
	CRational second(num2);
	LeadToCommonDenominator(first, second);
	return (first.GetNumerator() > second.GetNumerator());
}

const bool operator >= (const CRational &num1, const CRational &num2)
{
	return (!(num1 < num2));
}

std::istream & operator >>(std::istream & is, CRational &rational)
{	
	int numerator = 0, denominator = 0;
	if ((is >> numerator) && (is.get() == '/') && (is >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	return is;
}

std::ostream & operator << (std::ostream & os, const CRational &rational)
{
	os << rational.GetNumerator() << "/" << rational.GetDenominator();
	return os;
}

int GCD(int a, int b)
{	
	int curA = abs(a), curB = abs(b);
	while (curA != 0 && curB != 0)
	{
		int newA = curB % curA;
		int newB = curA;
		curA = newA;
		curB = newB;
	}

	const int maxVal = std::max(curA, curB);
	return (maxVal == 0) ? 1 : maxVal;
}

void LeadToCommonDenominator(CRational &first, CRational &second)
{
	int firstDenom = first.GetDenominator();
	int secondDenom = second.GetDenominator();
	if (firstDenom == secondDenom)
	{
		return;
	}
	if ((firstDenom % secondDenom) == 0)
	{
		int multiplier = firstDenom / secondDenom;
		second.m_denominator *= multiplier;
		second.m_numerator *= multiplier;
		return;
	}
	if ((secondDenom % firstDenom) == 0)
	{
		int multiplier = secondDenom / firstDenom;
		first.m_denominator *= multiplier;
		first.m_numerator *= multiplier;
		return;
	}
	first.m_denominator *= secondDenom;
	first.m_numerator *= secondDenom;
	second.m_denominator *= firstDenom;
	second.m_numerator *= firstDenom;
	return;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	std::pair<int, CRational> compound;
	CRational rational(*(this));
	compound.first = m_numerator / m_denominator;
	rational.m_numerator -= (compound.first * m_denominator);
	compound.second = rational;
	return compound;
}

CRational Normalize(int numerator, int denominator, CRational &rational)
{
	int commonDenominator = GCD(numerator, denominator);
	rational.m_numerator /= commonDenominator;
	rational.m_denominator /= commonDenominator;
	return rational;
}