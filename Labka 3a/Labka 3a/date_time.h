#ifndef DATE_TIME
#define DATE_TIME

enum MONTH { January = 1, February, March, April, May, June, July, August, September, October, November, December };
typedef unsigned int uint;
typedef const unsigned int cuint;

class date_time
{
private:
	uint year : 12, month : 4, day : 5, hours : 5, minutes : 6;

	static bool leap(cuint& year);
	static bool check_day(cuint& year, cuint& month, cuint& day);
	static bool check_date(cuint& year, cuint& month, cuint& day, cuint& hours, cuint& minutes);
	bool check_date() const;

public:

	date_time();
	date_time(cuint& year, cuint& month, cuint& day, cuint& hours, cuint& minutes);

	void set_date(cuint& year, cuint& month, cuint& day, cuint& hours, cuint& minutes);

	void rand_date();

	bool operator==(const date_time& other_date) const;
	bool operator>(const date_time& other_date) const;
	bool operator<(const date_time& other_date) const;

	friend std::ostream& operator<<(std::ostream& out, const date_time& date);
};

#endif /* DATE_TIME */