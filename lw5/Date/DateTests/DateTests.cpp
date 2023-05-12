#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Date/CDate.h"
#include <sstream>

SCENARIO("Testing CDate initialization ")
{
	WHEN("Inited with min timestamp")
	{
		THEN("Date is 01.01.1970")
		{
			CDate date(0);
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == MIN_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with max timestamp")
	{
		THEN("Date is 31.12.9999")
		{
			CDate date(MAX_AVAILABLE_DAY);
			REQUIRE(date.GetDay() == 31);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetYear() == MAX_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with min available date values")
	{
		THEN("Date is 01.01.1970")
		{
			CDate date(1, Month::JANUARY, MIN_AVAILABLE_YEAR);
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == MIN_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with max available date values")
	{
		THEN("Date is 31.12.9999")
		{
			CDate date(31, Month::DECEMBER, MAX_AVAILABLE_YEAR);
			REQUIRE(date.GetDay() == 31);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetYear() == MAX_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with random date values")
	{
		THEN("Date is 20.03.2023")
		{
			CDate date(20, Month::MARCH, 2023);
			REQUIRE(date.GetDay() == 20);
			REQUIRE(date.GetMonth() == Month::MARCH);
			REQUIRE(date.GetYear() == 2023);
		}
	}
}

SCENARIO("Testing isValid")
{
	WHEN("Date is valid")
	{
		CDate date(20, Month::MARCH, 2023);
		REQUIRE(date.IsValid());
	}
	WHEN("Date is not valid (date min value - 1)")
	{
		CDate date(31, Month::DECEMBER, MIN_AVAILABLE_YEAR - 1);
		REQUIRE(!date.IsValid());
	}
	WHEN("Date is not valid (date max value + 1)")
	{
		CDate date(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
		REQUIRE(!date.IsValid());
	}
}

SCENARIO("Testing Date Values Getters")
{
	Days testDay = 20;
	Month testMonth = Month::MARCH;
	Year testYear = 2023;

	CDate date(testDay, testMonth, testYear);
	WHEN("Get Day")
	{
		THEN("Day is equal to testDay")
		{
			REQUIRE(date.GetDay() == testDay);
		}
	}
	WHEN("Get Month")
	{
		THEN("Month is equal to testMonth")
		{
			REQUIRE(date.GetMonth() == testMonth);
		}
	}
	WHEN("Get Year")
	{
		THEN("Year is equal to testYear")
		{
			REQUIRE(date.GetYear() == testYear);
		}
	}
}

SCENARIO("Testing Get WeekDay")
{
	WHEN("Weekday is Monday")
	{
		CDate date(20, Month::MARCH, 2023);
		REQUIRE(date.GetWeekDay() == WeekDay::MONDAY);
	}
}

SCENARIO("Testing == operator")
{
	WHEN("Dates are the same")
	{
		THEN("They are equal")
		{
			CDate date1(20, Month::MARCH, 2023);
			CDate date2(20, Month::MARCH, 2023);
			REQUIRE(date1 == date2);
		}
	}
	WHEN("Dates are different")
	{
		THEN("They are not equal")
		{
			CDate date1(20, Month::MARCH, 2023);
			CDate date2(21, Month::MARCH, 2023);
			REQUIRE(!(date1 == date2));
		}
	}
}

SCENARIO("Testing != operator")
{
	WHEN("Dates are the same")
	{
		THEN("They are equal")
		{
			CDate date1(20, Month::MARCH, 2023);
			CDate date2(20, Month::MARCH, 2023);
			REQUIRE(!(date1 != date2));
		}
	}
	WHEN("Dates are different")
	{
		THEN("They are not equal")
		{
			CDate date1(20, Month::MARCH, 2023);
			CDate date2(21, Month::MARCH, 2023);
			REQUIRE(date1 != date2);
		}
	}
}

SCENARIO("Testing >, <, >=, <= operator")
{
	WHEN("First date is greater than second on")
	{
		CDate date1(20, Month::MARCH, 2023);
		CDate date2(19, Month::MARCH, 2023);
		REQUIRE(date1 > date2);
		REQUIRE(!(date1 < date2));
		REQUIRE(date1 >= date2);
		REQUIRE(!(date1 <= date2));
	}
	WHEN("First date is not greater than second on")
	{
		CDate date1(20, Month::MARCH, 2023);
		CDate date2(21, Month::MARCH, 2023);
		REQUIRE(!(date1 > date2));
		REQUIRE(date1 < date2);
		REQUIRE(!(date1 >= date2));
		REQUIRE(date1 <= date2);
	}
	WHEN("Dates are the same")
	{
		CDate date1(20, Month::MARCH, 2023);
		CDate date2(20, Month::MARCH, 2023);
		REQUIRE(!(date1 > date2));
		REQUIRE(!(date1 < date2));
		REQUIRE(date1 >= date2);
		REQUIRE(date1 <= date2);
	}
}

SCENARIO("Testing Prefix Increment operator")
{
	WHEN("Date is valid")
	{
		THEN("Date is bigger by 1 day")
		{
			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(21, Month::MARCH, 2023);
			REQUIRE(++date == correctOutputDate);
		}
	}
	WHEN("Date is not valid")
	{
		THEN("Date is not modified")
		{
			CDate date(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			CDate correctOutputDate(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			REQUIRE(++date == correctOutputDate);
		}
	}
}
SCENARIO("Testing Postfix Increment operator")
{
	WHEN("Date is valid")
	{
		THEN("Date is bigger by 1 day")
		{
			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(21, Month::MARCH, 2023);
			REQUIRE(date++ != correctOutputDate);
			REQUIRE(date == correctOutputDate);
		}
	}
	WHEN("Date is not valid")
	{
		THEN("Date is not modified")
		{
			CDate date(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			CDate correctOutputDate(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			REQUIRE((date++) == correctOutputDate);
			REQUIRE(date == correctOutputDate);
		}
	}
}

SCENARIO("Testing Prefix decrement operator")
{
	WHEN("Date is valid")
	{
		THEN("Date is bigger by 1 day")
		{
			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(19, Month::MARCH, 2023);
			REQUIRE(--date == correctOutputDate);
		}
	}
	WHEN("Date is not valid")
	{
		THEN("Date is not modified")
		{
			CDate date(31, Month::DECEMBER, MIN_AVAILABLE_YEAR - 1);
			CDate correctOutputDate(31, Month::DECEMBER, MIN_AVAILABLE_YEAR - 1);
			REQUIRE(--date == correctOutputDate);
		}
	}
}
SCENARIO("Testing Postfix decrement operator")
{
	WHEN("Date is valid")
	{
		THEN("Date is bigger by 1 day")
		{
			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(19, Month::MARCH, 2023);
			REQUIRE(date-- != correctOutputDate);
			REQUIRE(date == correctOutputDate);
		}
	}
	WHEN("Date is not valid")
	{
		THEN("Date is not modified")
		{
			CDate date(31, Month::DECEMBER, MIN_AVAILABLE_YEAR - 1);
			CDate correctOutputDate(31, Month::DECEMBER, MIN_AVAILABLE_YEAR - 1);
			REQUIRE((date--) == correctOutputDate);
			REQUIRE(date == correctOutputDate);
		}
	}
}

SCENARIO("Testing + operator")
{
	WHEN("Date is valid")
	{
		THEN("Date is modified")
		{
			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(1, Month::APRIL, 2023);
			REQUIRE(date + 12 == correctOutputDate);
		}
	}
	WHEN("Date is not valid")
	{
		THEN("Date is not modified")
		{
			CDate date(20, Month::MARCH, MAX_AVAILABLE_YEAR + 1);
			CDate correctOutputDate(20, Month::MARCH, MAX_AVAILABLE_YEAR + 1);
			REQUIRE(date + 12 == correctOutputDate);
		}
	}
}

SCENARIO("Testing - operator")
{
	WHEN("Date is valid and substract days")
	{
		THEN("Date is modified")
		{
			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(19, Month::MARCH, 2023);
			REQUIRE(date - 1 == correctOutputDate);
		}
	}
	WHEN("Date is not valid and substract days")
	{
		THEN("Date is not modified")
		{
			CDate date(20, Month::MARCH, MAX_AVAILABLE_YEAR + 1);
			CDate correctOutputDate(20, Month::MARCH, MAX_AVAILABLE_YEAR + 1);
			REQUIRE(date - 12 == correctOutputDate);
		}
	}
	WHEN("Date is valid and substract Date")
	{
		THEN("Date is modified")
		{
			CDate date1(20, Month::MARCH, 2023);
			CDate date2(19, Month::MARCH, 2023);
			Days correctOutputDays = 1;
			REQUIRE(date1 - date2 == correctOutputDays);
		}
	}
	WHEN("Date is not valid and substract Date")
	{
		THEN("Date is not modified")
		{
			CDate date1(MAX_AVAILABLE_DAY + 1);
			CDate date2(20, Month::MARCH, 2023);
			Days correctOutputDate = MAX_AVAILABLE_DAY + 1;
			REQUIRE(date1 - date2 == correctOutputDate);
		}
	}
}

SCENARIO("Testing += operator")
{
	WHEN("Date is valid")
	{
		THEN("Date is modified")
		{

			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(30, Month::MARCH, 2023);
			date += 10;
			REQUIRE(date == correctOutputDate);
		}
	}

	WHEN("Date is not valid")
	{
		THEN("Date is not modified")
		{
			CDate date(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			CDate correctOutputDate(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			date += 10;
			REQUIRE(date == correctOutputDate);
		}
	}
}

SCENARIO("Testing -= operator")
{
	WHEN("Date is valid")
	{
		THEN("Date is modified")
		{

			CDate date(20, Month::MARCH, 2023);
			CDate correctOutputDate(10, Month::MARCH, 2023);
			date -= 10;
			REQUIRE(date == correctOutputDate);
		}
	}

	WHEN("Date is not valid")
	{
		THEN("Date is not modified")
		{
			CDate date(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			CDate correctOutputDate(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
			date -= 10;
			REQUIRE(date == correctOutputDate);
		}
	}
}

SCENARIO("Testing << operator")
{
	WHEN("Date is valid")
	{
		std::ostringstream outputStream;
		CDate date(20, Month::MARCH, 2023);
		outputStream << date;
		REQUIRE(outputStream.str() == "20.3.2023");
	}

	WHEN("Date is not valid")
	{
		std::ostringstream outputStream;
		CDate date(1, Month::JANUARY, MAX_AVAILABLE_YEAR + 1);
		outputStream << date;
		REQUIRE(outputStream.str() == "INVALID");
	}
}

SCENARIO("Testing >> operator")
{
	WHEN("Date is valid")
	{
		std::istringstream inputStream("20.3.2023");
		CDate date;
		inputStream >> date;
		REQUIRE(date.GetDay() == 20);
		REQUIRE(date.GetMonth() == Month::MARCH);
		REQUIRE(date.GetYear() == 2023);
	}
	WHEN("Date is written wrong")
	{
		std::istringstream inputStream("aa.3.2023");
		std::ostringstream outputStream;
		CDate date;

		try
		{
			inputStream >> date;
		}
		catch (std::exception const& e)
		{
			outputStream << e.what();
		}

		REQUIRE(outputStream.str() == "Day should be a number");
	}
	WHEN("Date is written correctly but it's not valid")
	{
		std::istringstream inputStream("1.1.10000");
		std::ostringstream outputStream;
		CDate date;

		try
		{
			inputStream >> date;
		}
		catch (std::exception const& e)
		{
			outputStream << e.what();
		}

		REQUIRE(outputStream.str() == "Date is not valid. 1.1.1970 >= YOUR DATE <= 31.12.9999");
	}
}