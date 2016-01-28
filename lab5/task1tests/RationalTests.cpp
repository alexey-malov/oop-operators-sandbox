﻿// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}



/*
  Рациональное число:
	равно нулю по умолчанию (0/1)
	может быть созданно из целого в формате (n / 1)
	может быть задано с указанием числителя и знаменателя
	хранится в нормализованном виде
	*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(may_not_have_zero_denominator)
	{
		BOOST_CHECK_THROW(CRational(1, 0), std::invalid_argument);
	}




//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
	{
		const double epsilon = 1e-5;
		BOOST_CHECK_CLOSE_FRACTION(CRational(3, 5).ToDouble(), 0.6, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(CRational(3, -5).ToDouble(), -0.6, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(CRational(-3, 5).ToDouble(), -0.6, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(CRational(1, 3).ToDouble(), 0.3333333, epsilon);
	}



//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_unary_minus)
	{
		VerifyRational(-CRational(5, 7), -5, 7);
		VerifyRational(-CRational(20, 25), -4, 5);
		VerifyRational(-CRational(-7, 10), 7, 10);
		VerifyRational(-CRational(0, 1), 0, 1);
		VerifyRational(-CRational(0, 7), 0, 1);
	}

	BOOST_AUTO_TEST_CASE(has_unary_plus)
	{
		VerifyRational(+CRational(8, 15), 8, 15);
		VerifyRational(+CRational(10, 15), 2, 3);
		VerifyRational(+CRational(-15, 23), -15, 23);
		VerifyRational(+CRational(0, 1), 0, 1);
		VerifyRational(+CRational(0, 25), 0, 1);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_binary_addition_operation)
	{
		VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 2) + 1, 3, 2);
		VerifyRational(1 + CRational(1, 2), 3, 2);
		VerifyRational(CRational(1, 2) + CRational(1, 2), 1, 1);
	}

	BOOST_AUTO_TEST_CASE(does_not_changed_when_zero_is_added)
	{
		VerifyRational(CRational(1, 2) + CRational(), 1, 2);
		VerifyRational(CRational(1, 2) + 0, 1, 2);
		VerifyRational(0 + CRational(1, 2), 1, 2);
	}



//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(operator_binary_minus)
{
	CRational const r1_2(1, 2);
	CRational const r1_6(1, 6);
	VerifyRational(r1_2 - r1_6, 1, 3);
	VerifyRational(r1_2 - 1, -1, 2);
	VerifyRational(1 - r1_2, 1, 2);
	VerifyRational(0 - r1_2, -1, 2);
	VerifyRational(r1_6 - 0, 1, 6);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_adding_assignment_operator)
	{
		VerifyRational((CRational(1, 2) += CRational(1, 6)), 2, 3);
		VerifyRational((CRational(1, 2) += 1), 3, 2);
		VerifyRational((CRational(8, -16) += CRational(1, 6)), -1, 3);
	}


//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_be_decreased_by_another_rational_with_same_denominator)
	{
		VerifyRational(CRational(2, 3) -= CRational(1, 3),  1, 3);
		VerifyRational(CRational(1, 7) -= CRational(5, 7),  -4, 7);
		VerifyRational(CRational(3, 8) -= CRational(-2, 8), 5, 8);
	}

	BOOST_AUTO_TEST_CASE(can_be_decreased_by_another_rational_with_coprime_denominator)
	{
		VerifyRational(CRational(1, 3) -= CRational(1, 2),   -1, 6);
		VerifyRational(CRational(-3, 5) -= CRational(1, 9),  -32, 45);
		VerifyRational(CRational(3, 14) -= CRational(2, 15), 17, 210);
	}

	BOOST_AUTO_TEST_CASE(can_be_decreased_by_another_rational_and_stays_normalized)
	{
		VerifyRational(CRational(1, 2) -= CRational(1, 6),  1, 3);
		VerifyRational(CRational(2, 7) -= CRational(2, 7),  0, 1);
		VerifyRational(CRational(12, 7) -= CRational(5, 7), 1, 1);
	}

	BOOST_AUTO_TEST_CASE(can_be_decreased_by_integer)
	{
		VerifyRational(CRational(1, 2) -= 1, -1, 2);
		VerifyRational(CRational(2, 3) -= 2, -4, 3);
		VerifyRational(CRational(3, 5) -= 0, 3, 5);
	}

	BOOST_AUTO_TEST_CASE(can_be_decreased_several_times_and_the_original_variable_is_updated)
	{
		CRational minued(1, 2);
		(minued -= CRational(1, 6)) -= CRational(5, 7);
		VerifyRational(minued, -8, 21);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	(7*2) / 3     = (14/3)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_binary_multiply)
	{
		VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
		VerifyRational(CRational(1, 2) * CRational(-3), -3, 2);
		VerifyRational(CRational(7) * CRational(1, 21), 1, 3);
		VerifyRational(CRational(0) * CRational(-10, 15), 0, 1);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_division_operation)
	{
		VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) / 5, 1, 10);
		VerifyRational(7 / CRational(2, 3), 21, 2);

		VerifyRational(CRational(1, 2) / 1, 1, 2);
		VerifyRational(1 / CRational(1, 2), 2, 1);
	}




//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(operator_multiply_equals)
{
	CRational r1_2(1, 2);
	CRational const r2_3(2, 3);
	VerifyRational(r1_2 *= r2_3, 1, 3);
	r1_2 = CRational(1, 2);
	VerifyRational(r1_2 *= 3, 3, 2);
	r1_2 = CRational(1, 2);
	VerifyRational(r1_2 *= 0, 0, 1);
	r1_2 = CRational(1, 2);
	VerifyRational(r1_2 *= -2, -1, 1);
}




//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_assignment_with_division_operation)
	{
		VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) /= 3, 1, 6);

		VerifyRational(CRational(1, 2) /= 1, 1, 2);
	}



//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_equal_and_not_equal_operators)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2)); //-V501
		BOOST_CHECK(CRational(4, 1) == 4);
		BOOST_CHECK(3 == CRational(3, 1));
		BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
		BOOST_CHECK(CRational(1, 2) != 7);
		BOOST_CHECK(3 != CRational(2, 3));
	}



//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_comparison_operators)
		BOOST_AUTO_TEST_CASE(operator_less_than)
		{
			BOOST_CHECK(CRational(1, 2) < 7);
			BOOST_CHECK(CRational(-1, 2) < 0);
			BOOST_CHECK(0 < CRational(1, 2));
			BOOST_CHECK(CRational(-1, 2) < CRational(1, 2));
			BOOST_CHECK(!(CRational(7, 2) < CRational(1, 2)));
		}

		BOOST_AUTO_TEST_CASE(operator_greater_than)
		{
			BOOST_CHECK(CRational(3, 1) > 2);
			BOOST_CHECK(CRational(3, 1) > 0);
			BOOST_CHECK(0 > CRational(-3, 5));
			BOOST_CHECK(CRational(-1, 10) > CRational(-1, 2));
			BOOST_CHECK(!(CRational(5, 3) > CRational(5, 2)));
		}

		BOOST_AUTO_TEST_CASE(operator_less_than_or_equal)
		{
			BOOST_CHECK(3 <= CRational(7, 2));
			BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
			BOOST_CHECK(CRational(7, 2) <= CRational(7, 2)); //-V501
			BOOST_CHECK(CRational(1, 2) <= 1);
			BOOST_CHECK(0 <= CRational(1, 2));
		}

		BOOST_AUTO_TEST_CASE(operator_greater_than_or_equal)
		{
			BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
			BOOST_CHECK(!(3 >= CRational(8, 2)));
			BOOST_CHECK(CRational(7, 2) >= CRational(7, 2)); //-V501
			BOOST_CHECK(CRational(1, 2) >= 0);
			BOOST_CHECK(5 >= CRational(1, 2));
		}
	BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_write_into_output_stream)
	{
		std::ostringstream outstream;
		outstream << CRational(7, 15);
		BOOST_CHECK_EQUAL(outstream.str(), "7/15");
	}



//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_be_entered_with_input_stream)
	{
		CRational rational;		

		std::istringstream normalNumber("7/15");
		normalNumber >> rational;
		VerifyRational(rational, 7, 15);

		std::istringstream negativeNumber("-5/13");
		negativeNumber >> rational;
		VerifyRational(rational, -5, 13);

		std::istringstream doubleNegativeNumber("-4/-27");
		doubleNegativeNumber >> rational;
		VerifyRational(rational, 4, 27);

		std::istringstream numberWithWrongSyntax("4 7");
		numberWithWrongSyntax >> rational;
		numberWithWrongSyntax.clear();
		int denominatorLeft = 0;
		numberWithWrongSyntax >> denominatorLeft;
		BOOST_CHECK_EQUAL(denominatorLeft, 7);
	}


BOOST_AUTO_TEST_SUITE_END()
