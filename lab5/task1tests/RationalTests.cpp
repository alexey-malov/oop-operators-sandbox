// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"

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

	BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
	{
		const double epsilon = 1e-5;
		BOOST_CHECK_CLOSE_FRACTION(CRational(3, 5).ToDouble(), 0.6, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(CRational(3, -5).ToDouble(), -0.6, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(CRational(-3, 5).ToDouble(), -0.6, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(CRational(1, 3).ToDouble(), 0.3333333, epsilon);
	}

	BOOST_AUTO_TEST_CASE(has_unary_subtraction_operator)
	{
		VerifyRational(-CRational(5, 7), -5, 7);
		VerifyRational(-CRational(20, 25), -4, 5);
		VerifyRational(-CRational(-7, 10), 7, 10);
		VerifyRational(-CRational(0, 1), 0, 1);
		VerifyRational(-CRational(0, 7), 0, 1);
	}

	BOOST_AUTO_TEST_CASE(has_unary_addition_operator)
	{
		VerifyRational(+CRational(8, 15), 8, 15);
		VerifyRational(+CRational(10, 15), 2, 3);
		VerifyRational(+CRational(-15, 23), -15, 23);
		VerifyRational(+CRational(0, 1), 0, 1);
		VerifyRational(+CRational(0, 25), 0, 1);
	}

	BOOST_AUTO_TEST_CASE(has_addition_operator)
	{
		VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 2) + 1, 3, 2);
		VerifyRational(1 + CRational(1, 2), 3, 2);
		VerifyRational(CRational(1, 2) + CRational(1, 2), 1, 1);

        VerifyRational(CRational(1, 2) + CRational(), 1, 2);
        VerifyRational(CRational(1, 2) + 0, 1, 2);
        VerifyRational(0 + CRational(1, 2), 1, 2);
	}

    BOOST_AUTO_TEST_CASE(has_subtraction_operator)
    {
	    VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
	    VerifyRational(CRational(1, 2) - 1, -1, 2);
	    VerifyRational(1 - CRational(1, 2), 1, 2);
	    VerifyRational(0 - CRational(1, 2), -1, 2);
	    VerifyRational(CRational(1, 6) - 0, 1, 6);
    }

	BOOST_AUTO_TEST_CASE(has_assignment_with_addition_operator)
	{
		VerifyRational((CRational(1, 2) += CRational(1, 6)), 2, 3);
		VerifyRational((CRational(1, 2) += 1), 3, 2);
		VerifyRational((CRational(8, -16) += CRational(1, 6)), -1, 3);
	}

    BOOST_AUTO_TEST_CASE(has_assignment_with_substraction_operator)
    {
        VerifyRational((CRational(1, 2) -= CRational(1, 6)), 1, 3);
        VerifyRational((CRational(1, 2) -= 1), -1, 2);
        VerifyRational((CRational(-8, 16) -= CRational(1, 2)), -1, 1);
    }

	BOOST_AUTO_TEST_CASE(has_multiplication_operator)
	{
		VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
		VerifyRational(CRational(1, 2) * CRational(-3), -3, 2);
		VerifyRational(CRational(7) * CRational(1, 21), 1, 3);
		VerifyRational(CRational(0) * CRational(-10, 15), 0, 1);
	}

	BOOST_AUTO_TEST_CASE(has_division_operator)
	{
		VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) / 5, 1, 10);
		VerifyRational(7 / CRational(2, 3), 21, 2);

		VerifyRational(CRational(1, 2) / 1, 1, 2);
		VerifyRational(1 / CRational(1, 2), 2, 1);
	}

    BOOST_AUTO_TEST_CASE(has_assignment_with_multiplication_operator)
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

	BOOST_AUTO_TEST_CASE(has_assignment_with_division_operator)
	{
		VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) /= 3, 1, 6);

		VerifyRational(CRational(1, 2) /= 1, 1, 2);
	}

	BOOST_AUTO_TEST_CASE(has_equal_and_not_equal_operators)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
		BOOST_CHECK(CRational(4, 1) == 4);
		BOOST_CHECK(3 == CRational(3, 1));
		BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
		BOOST_CHECK(CRational(1, 2) != 7);
		BOOST_CHECK(3 != CRational(2, 3));
	}

    BOOST_AUTO_TEST_CASE(has_other_logical_operators)
    {
        BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
        BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
        BOOST_CHECK(CRational(3, 1) > 2);
        BOOST_CHECK(CRational(1, 2) < 7);
        BOOST_CHECK(3 <= CRational(7, 2));
        BOOST_CHECK(!(3 >= CRational(8, 2)));
    }

    BOOST_AUTO_TEST_CASE(can_write_into_output_stream)
	{
		std::ostringstream outstream = std::ostringstream();
		outstream << CRational(7, 15);
		BOOST_CHECK_EQUAL(outstream.str(), "7/15");
	}

    BOOST_AUTO_TEST_CASE(can_read_from_input_stream)
    {
        std::istringstream instream = std::istringstream("7/15");
        CRational rational;
        instream >> rational;
        VerifyRational(rational, 7, 15);
    }


BOOST_AUTO_TEST_SUITE_END()
