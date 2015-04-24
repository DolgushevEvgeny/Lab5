// CRationalNumberTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../CRationalNumber/Rational.h"
#include <iostream>

using namespace std;

struct RationalFixture
{
	CRational defaultRational;
};

/*
	Рациональное число:
		равно нулю по умолчанию (0/1)
		может быть создано из целого в формате (n / 1) 
		может быть задано с указанием числителя и знаменателя
		хранится в нормализованном виде
*/

BOOST_FIXTURE_TEST_SUITE(Rational, RationalFixture)

BOOST_AUTO_TEST_CASE(IsEqualToZeroByDefault)
{
	BOOST_CHECK_EQUAL(defaultRational.GetNumerator(), 0);
	BOOST_CHECK_EQUAL(defaultRational.GetDenominator(), 1);
}

BOOST_AUTO_TEST_CASE(CanBeConstructedFromInteger)
{
	{
		CRational positive(10);
		BOOST_CHECK_EQUAL(positive.GetNumerator(), 10);
		BOOST_CHECK_EQUAL(positive.GetDenominator(), 1);
	}
	{
		CRational negative(-10);
		BOOST_CHECK_EQUAL(negative.GetNumerator(), -10);
		BOOST_CHECK_EQUAL(negative.GetDenominator(), 1);
	}
	{
		CRational zero(0);
		BOOST_CHECK_EQUAL(zero.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(zero.GetDenominator(), 1);
	}
}

BOOST_AUTO_TEST_CASE(CanBeDefinedByNumeratorAndDenominator)
{
	{
		CRational rational(5, 2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational rational(-5, 2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), -5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational rational(-5, -2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational rational(5, -2);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), -5);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
}

BOOST_AUTO_TEST_CASE(CanReturnDecimal)
{
	CRational rational(3, 5);
	BOOST_CHECK_CLOSE(rational.ToDouble(), 0.6, DBL_EPSILON);
}

BOOST_AUTO_TEST_CASE(OperatorUnaryMinusChangeRationalNumberToTheOpposite)
{
	{
		CRational positive = -CRational(-2, 3);
		BOOST_CHECK_EQUAL(positive.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(positive.GetDenominator(), 3);
	}
	{
		CRational negative = -CRational(2, 3);
		BOOST_CHECK_EQUAL(negative.GetNumerator(), -2);
		BOOST_CHECK_EQUAL(negative.GetDenominator(), 3);
	}
}

BOOST_AUTO_TEST_CASE(OperatorUnaryPlusDntChangeRationalNumber)
{
	{
		CRational rational = +CRational(-2, 3);
		BOOST_CHECK_EQUAL(rational.GetNumerator(), -2);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 3);
	}
	{
		CRational negative = +CRational(2, 3);
		BOOST_CHECK_EQUAL(negative.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(negative.GetDenominator(), 3);
	}
}

BOOST_AUTO_TEST_CASE(TestBinaryPlus)
{
	{
		CRational const rational1(1, 2), rational2(1, 6);
		CRational rational = rational1 + rational2;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 3);
	}
	{
	CRational const rational1(1, 4);
	CRational rational = rational1 + 2;

	BOOST_CHECK_EQUAL(rational.GetNumerator(), 9);
	BOOST_CHECK_EQUAL(rational.GetDenominator(), 4);
}
	{
		CRational const rational1(1, 2);
		CRational rational = 1 + rational1;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 2);
	}
	{
		CRational const rational1(1, 2), rational2(-1, 3);
		CRational rational = rational1 + rational2;
		BOOST_CHECK_EQUAL(rational.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), 6);
	}
}

BOOST_AUTO_TEST_CASE(TestBinaryMinusOperator)
{
	{
		CRational r = CRational(1, 2) - CRational(1, 6);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 3);
	}

	{
	CRational r = CRational(1, 2) - 1;
	BOOST_CHECK_EQUAL(r.GetNumerator(), -1);
	BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
}

	{
		CRational r = 1 - CRational(1, 2);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
}

BOOST_AUTO_TEST_CASE(MultiplicationTwoRationalNumbers)
{
	{
		CRational result = CRational(1, 2) * CRational(2, 3);
		BOOST_CHECK_EQUAL(result.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(result.GetDenominator(), 3);
	}
	{
		CRational result = CRational(1, 2) * -3;
		BOOST_CHECK_EQUAL(result.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(result.GetDenominator(), 2);
	}
	{
		CRational result = 7 * 2 * CRational(1, 3);
		BOOST_CHECK_EQUAL(result.GetNumerator(), 14);
		BOOST_CHECK_EQUAL(result.GetDenominator(), 3);
	}
}

BOOST_AUTO_TEST_CASE(DivisionTwoRationalNumbers)
{
	{
		CRational result = CRational(1, 2) / CRational(2, 3);
		BOOST_CHECK_EQUAL(result.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(result.GetDenominator(), 4);
	}
	{
		CRational result = CRational(1, 2) / 5;
		BOOST_CHECK_EQUAL(result.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(result.GetDenominator(), 10);
	}
	{
		CRational result = 7 / CRational(2, 3);
		BOOST_CHECK_EQUAL(result.GetNumerator(), 21);
		BOOST_CHECK_EQUAL(result.GetDenominator(), 2);
	}
}

BOOST_AUTO_TEST_CASE(AssigningAddition)
{
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		r1 += r2;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 3);
	}
	{
		CRational r1(1, 2);
		r1 += 1;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 2);
	}
}

BOOST_AUTO_TEST_CASE(AssigningSubtraction)
{
	{
		CRational r1(1, 2);
		CRational r2(1, 6);
		r1 -= r2;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 3);
	}
	{
		CRational r1(1, 2);
		r1 -= 1;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), -1);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 2);
	}
}

BOOST_AUTO_TEST_CASE(AssigningMultiplication)
{
	{
		CRational r1(1, 2);
		CRational r2(2, 3);
		r1 *= r2;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 3);
	}
	{
		CRational r1(1, 2);
		r1 *= 3;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 2);
	}
}

BOOST_AUTO_TEST_CASE(AssigningDivision)
{
	{
		CRational r1(1, 2);
		CRational r2(2, 3);
		r1 /= r2;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 4);
	}
	{
		CRational r1(1, 2);
		r1 /= 3;
		BOOST_CHECK_EQUAL(r1.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(r1.GetDenominator(), 6);
	}
}

BOOST_AUTO_TEST_CASE(TestEqualNumbers)
{
	{
		CRational const rational1(1, 2), rational2(1, 2);
		BOOST_CHECK_EQUAL(rational1 == rational2, true);
		BOOST_CHECK_EQUAL(rational1 != rational2, false);
	}
	{
		CRational const rational1(1, 4), rational2(4, 16);
		BOOST_CHECK_EQUAL(rational1 == rational2, true);
		BOOST_CHECK_EQUAL(rational1 != rational2, false);
	}
	{
		CRational const rational1(1, 4);
		BOOST_CHECK_EQUAL(rational1 == 2, false);
		BOOST_CHECK_EQUAL(rational1 != 2, true);
	}
	{
		CRational const rational1(3);
		BOOST_CHECK_EQUAL(3 == rational1, true);
		BOOST_CHECK_EQUAL(3 != rational1, false);
	}
}

BOOST_AUTO_TEST_CASE(TestLessMore)
{
	{
		CRational const rational1(1, 2), rational2(3, 4);
		BOOST_CHECK_EQUAL(rational1 < rational2, true);
		BOOST_CHECK_EQUAL(rational2 < rational1, false);
	}
	{
		CRational const rational(3, 5);
		BOOST_CHECK_EQUAL(rational < 1, true);
		BOOST_CHECK_EQUAL(1 < rational, false);
	}
	{
		CRational const rational(7, 4);
		BOOST_CHECK_EQUAL(rational < 1, false);
		BOOST_CHECK_EQUAL(1 < rational, true);
	}
	{
		CRational const rational1(1, 2), rational2(3, 4);
		BOOST_CHECK_EQUAL(rational2 > rational1, true);
		BOOST_CHECK_EQUAL(rational1 > rational2, false);
	}
	{
		CRational const rational(5, 3);
		BOOST_CHECK_EQUAL(rational > 1, true);
		BOOST_CHECK_EQUAL(1 > rational, false);
	}
	{
		CRational const rational(7, 4);
		BOOST_CHECK_EQUAL(2 > rational, true);
		BOOST_CHECK_EQUAL(rational > 2, false);
	}
}

BOOST_AUTO_TEST_CASE(TestLessOrEqual_MoreOrEqual)
{
	{
		CRational const rational1(1, 2), rational2(3, 4);
		BOOST_CHECK_EQUAL(rational1 <= rational2, true);
	}
	{
		CRational const rational1(1, 2), rational2(3, 6);
		BOOST_CHECK_EQUAL(rational1 <= rational2, true);
	}
	{
		CRational const rational(3, 5);
		BOOST_CHECK_EQUAL(rational <= 1, true);
	}
	{
		CRational const rational(7, 4);
		BOOST_CHECK_EQUAL(rational <= 1, false);
	}
	{
		CRational const rational1(1, 2), rational2(3, 4);
		BOOST_CHECK_EQUAL(rational1 >= rational2, false);
		BOOST_CHECK_EQUAL(rational2 >= rational1, true);
	}
	{
		CRational const rational1(1, 2), rational2(3, 6);
		BOOST_CHECK_EQUAL(rational1 <= rational2, true);
		BOOST_CHECK_EQUAL(rational2 >= rational1, true);
	}
	{
		CRational const rational(3, 5);
		BOOST_CHECK_EQUAL(rational <= 1, true);
		BOOST_CHECK_EQUAL(rational >= 1, false);
	}
	{
		CRational const rational(7, 4);
		BOOST_CHECK_EQUAL(rational <= 1, false);
		BOOST_CHECK_EQUAL(rational >= 1, true);
	}
}

BOOST_AUTO_TEST_CASE(LeadTwoRationalNumbersToCommonDenominator)
{
	{
		CRational first(2, 3);
		CRational second(2, 5);
		LeadToCommonDenominator(first, second);
		BOOST_CHECK_EQUAL(first.GetDenominator(), 15);
		BOOST_CHECK_EQUAL(first.GetNumerator(), 10);
		BOOST_CHECK_EQUAL(second.GetDenominator(), 15);
		BOOST_CHECK_EQUAL(second.GetNumerator(), 6);
	}
	{
		CRational first(2, 9);
		CRational second(2, 3);
		LeadToCommonDenominator(first, second);
		BOOST_CHECK_EQUAL(first.GetDenominator(), 9);
		BOOST_CHECK_EQUAL(first.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(second.GetDenominator(), 9);
		BOOST_CHECK_EQUAL(second.GetNumerator(), 6);
	}
	{
		CRational first(2, 5);
		CRational second(4, 9);
		LeadToCommonDenominator(first, second);
		BOOST_CHECK_EQUAL(first.GetDenominator(), 45);
		BOOST_CHECK_EQUAL(first.GetNumerator(), 18);
		BOOST_CHECK_EQUAL(second.GetDenominator(), 45);
		BOOST_CHECK_EQUAL(second.GetNumerator(), 20);
	}
}

BOOST_AUTO_TEST_CASE(TestOutputRationalNumber)
{
	CRational rational(2, 5);
	cout << rational;
}

BOOST_AUTO_TEST_CASE(RationalToCompound)
{
	CRational rational(9, 4);
	std::pair<int, CRational> compound = rational.ToCompoundFraction();
	BOOST_CHECK_EQUAL(compound.first, 2);
	BOOST_CHECK_EQUAL(compound.second.GetNumerator(), 1);
	BOOST_CHECK_EQUAL(compound.second.GetDenominator(), 4);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(TestGCD)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1);
}