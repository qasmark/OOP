#pragma once

#include <iostream>
#include <string>

using Days = unsigned;
using Year = unsigned;

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

struct DateValues
{
	Days day;
	Month month;
	Year year;
};

const Days MAX_AVAILABLE_DAY = 2932896;

const Year MIN_AVAILABLE_YEAR = 1970;
const Year MAX_AVAILABLE_YEAR = 9999;

const int MONTHS_OFFSET[2][12] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 },
};

class CDate
{
public:
	// => Constructors
	CDate(Days day, Month month, Year year);
	CDate(Days timestamp = 0);

	// => Methods
	Days GetDay() const;
	Month GetMonth() const;
	Year GetYear() const;
	WeekDay GetWeekDay() const;

	bool IsValid() const;

	// => Operators
	bool operator==(CDate const& otherDate) const;
	bool operator!=(CDate const& otherDate) const;
	bool operator<(CDate const& otherDate) const;
	bool operator<=(CDate const& otherDate) const;
	bool operator>(CDate const& otherDate) const;
	bool operator>=(CDate const& otherDate) const;


	CDate& operator++();
	CDate& operator--();
	CDate const operator++(int);
	CDate const operator--(int);

	CDate& operator+=(Days days);
	CDate& operator-=(Days days);

	CDate const operator+(Days days) const;
	CDate const operator-(Days days) const;
	Days const operator-(CDate const& otherDate) const;

	friend std::istream& operator>>(std::istream& stream, CDate& date);
private:
	static DateValues StringToDateValues(std::string const& str);
	Days ConvertDateToDays(Days day, Month month, Year year) const;
	DateValues ConvertDaysToDateValues(Days days) const;
	bool IsLeapYear(Year year) const;

	Days m_days;
};

std::ostream& operator<<(std::ostream& stream, CDate const& date);
std::istream& operator>>(std::istream& stream, CDate& date);