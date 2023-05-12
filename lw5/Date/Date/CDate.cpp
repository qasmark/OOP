#include "CDate.h"

CDate::CDate(Days day, Month month, Year year)
	: m_days(ConvertDateToDays(day, month, year))
{
}

CDate::CDate(Days timestamp)
	: m_days(timestamp)
{
}

Days CDate::GetDay() const
{
	return ConvertDaysToDateValues(m_days).day;
}

Month CDate::GetMonth() const
{
	return ConvertDaysToDateValues(m_days).month;
}

unsigned CDate::GetYear() const
{
	return ConvertDaysToDateValues(m_days).year;
}

WeekDay CDate::GetWeekDay() const
{
	switch (m_days % 7)
	{
	case 0:
		return WeekDay::THURSDAY;
	case 1:
		return WeekDay::FRIDAY;
	case 2:
		return WeekDay::SATURDAY;
	case 3:
		return WeekDay::SUNDAY;
	case 4:
		return WeekDay::MONDAY;
	case 5:
		return WeekDay::TUESDAY;
	default:
		return WeekDay::WEDNESDAY;
	}
}

bool CDate::IsValid() const
{
	if (m_days > MAX_AVAILABLE_DAY)
	{
		return false;
	}
	return true;
}

bool CDate::operator==(CDate const& otherDate) const
{
	return m_days == otherDate.m_days;
}

bool CDate::operator!=(CDate const& otherDate) const
{
	return m_days != otherDate.m_days;
}

bool CDate::operator<(CDate const& otherDate) const
{
	return m_days < otherDate.m_days;
}

bool CDate::operator<=(CDate const& otherDate) const
{
	return m_days <= otherDate.m_days;
}

bool CDate::operator>(CDate const& otherDate) const
{
	return m_days > otherDate.m_days;
}

bool CDate::operator>=(CDate const& otherDate) const
{
	return m_days >= otherDate.m_days;
}

CDate& CDate::operator++()
{
	if (IsValid())
	{
		++m_days;
	}
	return *this;
}

CDate const CDate::operator++(int)
{
	if (!IsValid())
	{
		return *this;
	}
	CDate tempDateCopy(*this);
	++* this;
	return tempDateCopy;
}

CDate& CDate::operator--()
{
	if (IsValid())
	{
		--m_days;
	}
	return *this;
}

CDate const CDate::operator--(int)
{
	if (!IsValid())
	{
		return *this;
	}
	CDate tempDateCopy(*this);
	--* this;
	return tempDateCopy;
}

CDate& CDate::operator+=(Days days)
{
	if (IsValid())
	{
		m_days += days;
	}
	return *this;
}

CDate& CDate::operator-=(Days days)
{
	if (IsValid())
	{
		m_days -= days;
	}
	return *this;
}

CDate const CDate::operator+(Days days) const
{
	if (IsValid())
	{
		return m_days + days;
	}
	return m_days;
}

CDate const CDate::operator-(Days days) const
{
	if (IsValid())
	{
		return m_days - days;
	}
	return m_days;
}

Days const CDate::operator-(CDate const& otherDate) const
{
	if (IsValid())
	{
		return m_days - otherDate.m_days;
	}
	return m_days;
}

bool CDate::IsLeapYear(Year year) const
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

DateValues CDate::StringToDateValues(std::string const& str)
{
	Days day = 1;
	int monthIndex = 1;
	Year year = 1970;

	size_t firstDotIndex = str.find('.');

	try
	{
		day = stoi(str.substr(0, firstDotIndex));
	}
	catch (...)
	{
		throw std::invalid_argument("Day should be a number");
	}

	size_t secondDotIndex = str.find('.', firstDotIndex + 1);

	try
	{
		monthIndex = stoi(str.substr(firstDotIndex + 1, secondDotIndex - firstDotIndex));
	}
	catch (...)
	{
		throw std::invalid_argument("Month should be a number");
	}

	try
	{
		year = stoi(str.substr(secondDotIndex + 1));
	}
	catch (...)
	{
		throw std::invalid_argument("Year should be a number");
	}

	return { day, static_cast<Month>(monthIndex), year };
}

Days CDate::ConvertDateToDays(Days day, Month month, Year year) const
{
	Year yearGap = year - MIN_AVAILABLE_YEAR;
	Days daysInYearGap = yearGap * 365 + yearGap / 4 - yearGap / 100 + yearGap / 400;

	if (IsLeapYear(year - 1))
	{
		daysInYearGap++;
	}

	return daysInYearGap + MONTHS_OFFSET[IsLeapYear(year)][static_cast<Days>(month) - 1] + (day - 1);
}

DateValues CDate::ConvertDaysToDateValues(Days days) const
{
	Year year = (MIN_AVAILABLE_YEAR + 4 * days / (365 * 4 + 1)) + 1;

	int daysGap = (days - ConvertDateToDays(1, Month::JANUARY, year) + 1);
	if (daysGap <= 0)
	{
		year--;
		if (IsLeapYear(year))
		{
			daysGap += 366;
		}
		else
		{
			daysGap += 365;
		}
	}

	int monthIndex;
	Days d;

	for (monthIndex = 0; monthIndex < 12 && daysGap > MONTHS_OFFSET[IsLeapYear(year)][monthIndex]; monthIndex++)
	{
		d = daysGap - MONTHS_OFFSET[IsLeapYear(year)][monthIndex];
	}

	return { d, static_cast<Month>(monthIndex), year };
}

std::ostream& operator<<(std::ostream& stream, CDate const& date)
{
	if (!date.IsValid())
	{
		stream << "INVALID";
	}
	else
	{
		stream << date.GetDay() << "." << static_cast<int>(date.GetMonth()) << "." << date.GetYear();
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, CDate& date)
{
	std::string stringStream;
	stream >> stringStream;

	DateValues dateValues = CDate::StringToDateValues(stringStream);

	CDate newDate(dateValues.day, dateValues.month, dateValues.year);
	if (!newDate.IsValid())
	{
		throw std::invalid_argument("Date is not valid. 1.1.1970 >= YOUR DATE <= 31.12.9999");
	}
	date = newDate;

	return stream;
}