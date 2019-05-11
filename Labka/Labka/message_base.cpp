#include "pch.h"
#include "message_base.h"



bool message_base::data_msg::date_time::leap(cuint& year)
{
	return (year % 4 == 0) && ((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 400 != 0));
}

bool message_base::data_msg::date_time::check_day(cuint& year, cuint& month, cuint& day)
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

bool message_base::data_msg::date_time::check_date(cuint& year, cuint& month, cuint& day, cuint& hours, cuint& minutes)
{
	if (month >= 1 && month <= 12 && day >= 1 && day <= 31 && hours >= 0 && hours <= 23 && minutes >= 0
		&& minutes <= 59 && check_day(year, month, day)) return true;
	else return false;
}

bool message_base::data_msg::date_time::check_date() const
{
	if (month >= 1 && month <= 12 && day >= 1 && day <= 31 && hours >= 0 && hours <= 23 && minutes >= 0
		&& minutes <= 59 && check_day(year, month, day)) return true;
	else return false;
}

message_base::data_msg::date_time::date_time()
{
	rand_date();
}

message_base::data_msg::date_time::date_time(cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes)
{
	set_date(year, month, day, hours, minutes);
}

void message_base::data_msg::date_time::set_date(cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->hours = hours;
	this->minutes = minutes;

	if (!check_date()) { throw std::exception("Wrong date"); }
}

void message_base::data_msg::date_time::rand_date()
{
	year = rand() % 2100;
	month = (rand() % 12) + 1;
	day = (rand() % 28) + 1;
	hours = rand() % 24;
	minutes = rand() % 60;
}

void message_base::data_msg::date_time::date_bin_out(std::ostream &fout) const
{
	fout.write(reinterpret_cast<const char*>(&year), sizeof(year));
	fout.write(reinterpret_cast<const char*>(&month), sizeof(month));
	fout.write(reinterpret_cast<const char*>(&day), sizeof(day));
	fout.write(reinterpret_cast<const char*>(&hours), sizeof(hours));
	fout.write(reinterpret_cast<const char*>(&minutes), sizeof(minutes));
}

void message_base::data_msg::date_time::date_bin_in(std::istream &fin)
{
	fin.read(reinterpret_cast<char*>(&year), sizeof(year));
	fin.read(reinterpret_cast<char*>(&month), sizeof(month));
	fin.read(reinterpret_cast<char*>(&day), sizeof(day));
	fin.read(reinterpret_cast<char*>(&hours), sizeof(hours));
	fin.read(reinterpret_cast<char*>(&minutes), sizeof(minutes));
}

bool message_base::data_msg::date_time::operator==(const data_msg::date_time &other_date) const
{
	if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day
		&& this->hours == other_date.hours && this->minutes == other_date.minutes) return true;
	else return false;
}

bool message_base::data_msg::date_time::operator>(const message_base::data_msg::date_time &other_date) const
{
	if (this->year > other_date.year) return true;
	else if (this->year == other_date.year && this->month > other_date.month) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day > other_date.day) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours > other_date.hours) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours == other_date.hours && this->minutes > other_date.minutes) return true;
	else return false;
}

bool message_base::data_msg::date_time::operator<(const message_base::data_msg::date_time &other_date) const
{
	if (this->year < other_date.year) return true;
	else if (this->year == other_date.year && this->month < other_date.month) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day < other_date.day) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours < other_date.hours) return true;
	else if (this->year == other_date.year && this->month == other_date.month && this->day == other_date.day && this->hours == other_date.hours && this->minutes < other_date.minutes) return true;
	else return false;
}

std::ostream& message_base::data_msg::date_time::operator<<(std::ostream& out) const
{
	if (day < 10) { out << '0'; }
	out << day << '.';
	if (month < 10) { out << '0'; }
	out << month << '.' << year << ' ';
	if (hours < 10) { out << '0'; }
	out << hours << ':';
	if (minutes < 10) { out << '0'; }
	out << minutes;

	return out;
}

std::istream& message_base::data_msg::date_time::operator>>(std::istream& in)
{
	in >> day;
	in.get();
	in >> month;
	in.get();
	in >> year >> hours;
	in.get();
	in >> minutes;

	return in;
}

message_base::data_msg::data_msg()
{
	rand_msg();
}

message_base::data_msg::data_msg(const std::string & message)
{
	this->message = message;
	this->priority = rand() % 201;
	this->type = rand() % 5;
	this->system_loading = (double)((rand() % 1001) / 1000.0);
}


message_base::data_msg::data_msg(const std::string &message, cuint &type, cuint &priority, const double &system_loading, cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes)
{
	set_data_msg(message, type, priority, system_loading, year, month, day, hours, minutes);
}

void message_base::data_msg::set_data_msg(const std::string &message, cuint &type, cuint &priority, const double &system_loading, cuint &year, cuint &month, cuint &day, cuint &hours, cuint &minutes)
{
	this->message = message;
	if (!message_base::data_msg::date_time::check_date(year, month, day, hours, minutes)) throw std::exception("Wrong date or time");
	this->date = date_time(year, month, day, hours, minutes);
	
	if(priority >= 0 && priority <= 200 && type >= Debug && type <= Fatal && 
		system_loading >= 0 && system_loading <= 1)
	{
		this->priority = priority;
		this->type = type;
		this->system_loading = system_loading;
	}
	else throw std::exception("Wrong data message");
}

void message_base::data_msg::rand_msg()
{
	this->message = "Random message";
	this->priority = rand() % 201;
	this->type = rand() % 5;
	this->system_loading = (double)((rand() % 1001) / 1000.0);
}

void message_base::data_msg::bin_out_msg(std::ostream &fout) const
{
	date.date_bin_out(fout);

	int length = message.length();
	fout.write(reinterpret_cast<const char*>(&length), sizeof(length));
	fout.write(message.c_str(), length + 1);

	fout.write(reinterpret_cast<const char*>(&priority), sizeof(priority));
	fout.write(reinterpret_cast<const char*>(&type), sizeof(type));
	fout.write(reinterpret_cast<const char*>(&system_loading), sizeof(system_loading));
}

void message_base::data_msg::bin_in_msg(std::istream &fin)
{
	date.date_bin_in(fin);

	int length;
	fin.read(reinterpret_cast<char*>(&length), sizeof(length));
	char* temp = new char[length + 1];
	fin.read(temp, length + 1);
	message = temp;
	delete[] temp;

	fin.read(reinterpret_cast<char*>(&priority), sizeof(priority));
	fin.read(reinterpret_cast<char*>(&type), sizeof(type));
	fin.read(reinterpret_cast<char*>(&system_loading), sizeof(system_loading));
}

std::ostream &message_base::data_msg::operator<<(std::ostream& out) const
{
	date << out << std::endl << message << '\0' << std::endl << priority << std::endl;
	
	switch (type)
	{
	case Debug:
		out << "Debug";
		break;
	case Error:
		out << "Error";
		break;
	case Fatal:
		out << "Fatal";
		break;
	case Info:
		out << "Info";
		break;
	case Warning:
		out << "Warning";
		break;
	}

	out << std::endl << system_loading << std::endl << std::endl;

	return out;
}

std::istream &message_base::data_msg::operator>>(std::istream& in)
{
	date >> in;
	char ch;
	in.get(ch); /* miss \n */

	message.clear();
	while (true)
	{
		in.get(ch);
		if (ch == '\0') break;
		message.push_back(ch);
	} 
	
	in >> priority;
	in.get();
	ch = in.get();
	switch (ch)
	{
	case 'D':
		type = Debug;
		break;
	case 'E':
		type = Error;
		break;
	case 'F':
		type = Fatal;
		break;
	case 'I':
		type = Info;
		break;
	case 'W':
		type = Warning;
		break;
	}

	do
	{
		in.get(ch);
	} while (ch != '\n');
	in >> system_loading;

	return in;
}

message_base::message_base()
{	// reserve 10 elements
	list.reserve(10);
}

void message_base::create_rand_list(cuint &n)
{	// create n random elements sorted by date
	for (int i = 0; i < n; i++)
	{
		insert(data_msg());
	}
}

void message_base::insert(const data_msg &new_message)
{	// add new a sorted by date element
	std::vector<data_msg>::iterator it = list.begin();
	int size = list.size();

	for (int i = 0; i < size; i++)
	{
		if (new_message.date < list[i].date)
		{
			if (i >= 1)
			{	/* check for equal messages */
				if (new_message.date == list[i - 1].date && new_message.message == list[i - 1].message && new_message.priority == list[i - 1].priority
					&& new_message.type == list[i - 1].type && new_message.system_loading == list[i - 1].system_loading)
					return;
			}
			it += i;
			list.insert(it, new_message);
			return;
		}
	}

	if (size >= 1 && new_message.date == list[size - 1].date && new_message.message == list[size - 1].message && new_message.priority == list[size - 1].priority
		&& new_message.type == list[size - 1].type && new_message.system_loading == list[size - 1].system_loading)
		return;

	it += size;
	list.insert(it, new_message);
}

void message_base::pop_back()
{
	if (list.empty()) 
	{
		std::cout << "\nBase is empty\n";
		return;
	}
	list.pop_back();
}

void message_base::pop_for_message(const std::string &message)
{	// delete all these messages
	std::vector<data_msg>::iterator it = list.begin();
	int size = list.size();
	for (int i = 0; i != size; i++)
	{
		if (list[i].message == message)
		{
			it += i;
			list.erase(it);
			it = list.begin();
			i--;
			size--;
		}
	}
}

void message_base::modificate_message(const std::string &old_message, const std::string &new_message)
{
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		if (list[i].message == old_message) 
			list[i].message = new_message;
	}
}

void message_base::bin_out() const
{	// write a data message to the binary file
	std::ofstream fout;
	fout.open("binary.bin", std::ofstream::app | std::ofstream::binary | std::ofstream::out);
	if (!fout.is_open()) { throw std::exception("File isn't open"); }

	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		list[i].bin_out_msg(fout);
	}
	fout.close();
}

void message_base::bin_in()
{	// read a data message to the list in date order
	std::ifstream fin;
	fin.open("binary.bin", std::ifstream::binary | std::ifstream::in);
	if (!fin.is_open()) { throw std::exception("File isn't open"); }
	
	data_msg temp;
	while (fin.peek() != EOF)
	{
		temp.bin_in_msg(fin);
		insert(temp);
	}
	fin.close();
}

void message_base::bin_out(std::fstream &fios) const
{
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		list[i].bin_out_msg(fios);
	}
}

void message_base::bin_in(std::fstream &fios)
{
	data_msg temp;
	while (fios.peek() != EOF)
	{
		temp.bin_in_msg(fios);
		insert(temp);
	}
}

message_base* message_base::search_for_time_interval
(const data_msg::date_time &date1, const data_msg::date_time &date2) const
{
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		if (list[i].date > date1) 
		{	/* look for first element */
			message_base *sorted_list = new message_base;
			std::vector<data_msg>::const_iterator beg = list.cbegin(), end = beg;
			beg += i;
			while (i < size && list[i].date < date2)
			{	/* look for last element */
				i++;
			}
			end += i;
			if (end == beg) return nullptr;
			
			sorted_list->list.insert(sorted_list->list.begin(), beg, end);
			return sorted_list;
		}
	}
	return nullptr;
}

message_base* message_base::search_for_type_and_system_loading
	(cuint &type, const double &system_loading) const
{
	message_base *sorted_list = new message_base;

	bool no_message = true;
	int size = list.size();
	
	for (int i = 0; i < size; i++)
	{
		if(list[i].type == type && list[i].system_loading >= system_loading)
		{
			sorted_list->list.push_back(list[i]);
			no_message = false;
		}
	}

	return (no_message ? nullptr : sorted_list);
}

message_base* message_base::search_for_fragment(const std::string &fragment) const
{
	if (fragment.empty()) return nullptr;
	message_base* sorted_list = new message_base;

	bool no_message = true;
	int message_length = fragment.length();
	int size = list.size();

	for (int i = 0; i < size; i++)
	{
		if (check_message_fragment(list[i].message, fragment))
		{
			sorted_list->list.push_back(list[i]);
			no_message = false;
		}
	}

	return (no_message ? nullptr : sorted_list);
}




std::ostream& operator<<(std::ostream &out, const message_base &base)
{	// write a message base to a file
	int size = base.list.size();
	for (int i = 0; i < size; i++)
	{
		base.list[i] << out;
	}

	return out;
}

std::istream& operator>>(std::istream &fin, message_base &base)
{	// read a message base to a sorted by date base
	fin.seekg(0, std::ios::end);
	std::streampos end = fin.tellg();
	fin.seekg(0, std::ios::beg);

	message_base::data_msg temp;
	while (end - fin.tellg() > 6)
	{
		temp >> fin;
		base.insert(temp);
	}
	return fin;
}
