#include "pch.h"
#include "date_time.h"


bool date_time::leap(cuint& year)
{
	return (year % 4 == 0) && ((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 400 != 0));
}

bool date_time::check_day(cuint& year, cuint& month, cuint& day)
{
	if (day > 28)
	{
		if (day == 29 && (month == February || !leap(year))) return false;
		else if (month == February) return false;
		else if (day == 31 && (month == April || month == June || month == September || month == November))
			return false;
		else return true;
	}
	else return true;
}

bool date_time::check_date(cuint& year, cuint& month, cuint& day, cuint& hours, cuint& minutes)
{
	if (month >= 1 && month <= 12 && day >= 1 && day <= 31 && hours >= 0 && hours <= 23 && minutes >= 0
		&& minutes <= 59 && check_day(year, month, day)) return true;
	else return false;
}

bool date_time::check_date() const
{
	if (month >= 1 && month <= 12 && day >= 1 && day <= 31 && hours >= 0 && hours <= 23 && minutes >= 0
		&& minutes <= 59 && check_day(year, month, day)) return true;
	else return false;
}

date_time::date_time()
{
	rand_date();
}

date_time::date_time(cuint& year, cuint& month, cuint& day, cuint& hours, cuint& minutes)
{
	set_date(year, month, day, hours, minutes);
}

void date_time::set_date(cuint& year, cuint& month, cuint& day, cuint& hours, cuint& minutes)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->hours = hours;
	this->minutes = minutes;

	if (!check_date()) { throw std::exception("Wrong date"); }
}

void date_time::rand_date()
{
	year = rand() % 2100;
	month = (rand() % 12) + 1;
	day = (rand() % 28) + 1;
	hours = rand() % 24;
	minutes = rand() % 60;
}

bool date_time::operator==(const date_time& other_date) const
{
	return (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day
		&& this->hours == other_date.hours && this->minutes == other_date.minutes);
}

bool date_time::operator>(const date_time& other_date) const
{
	if (this->year > other_date.year) return true;
	else if (this->year == other_date.year && this->month > other_date.month) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day > other_date.day) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours > other_date.hours) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours == other_date.hours && this->minutes > other_date.minutes) return true;
	else return false;
}

bool date_time::operator<(const date_time& other_date) const
{
	if (this->year < other_date.year) return true;
	else if (this->year == other_date.year && this->month < other_date.month) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day < other_date.day) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours < other_date.hours) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours == other_date.hours && this->minutes < other_date.minutes) return true;
	else return false;
}

std::ostream& operator<<(std::ostream& out, const date_time& date)
{
	if (date.day < 10) { out << '0'; }
	out << date.day << '.';
	if (date.month < 10) { out << '0'; }
	out << date.month << '.' << date.year << ' ';
	if (date.hours < 10) { out << '0'; }
	out << date.hours << ':';
	if (date.minutes < 10) { out << '0'; }
	out << date.minutes;

	return out;
}