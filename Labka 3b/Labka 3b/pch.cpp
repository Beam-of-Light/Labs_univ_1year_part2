#include "pch.h"
#include "message_base.h"

simple_timer::simple_timer()
{
	start = std::chrono::high_resolution_clock::now();
}

double simple_timer::get_duration()
{
	finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = finish - start;
	return duration.count();
}




bool check_message_fragment(const std::string& message, const std::string& fragment)
{
	int size = fragment.length();
	if (message.length() >= size)
	{
		for (int i = 0; i < size; i++)
		{
			if (message[i] != fragment[i]) return false;
		}
	}
	else return false;

	return true;
}

template <typename T>
void write_num(T & data)
{
	while (!(std::cin >> data))
	{
		std::cin.clear(); /* Clear errors (like the failbit flag) */
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); /* Throw away the rest of the line */
		std::cout << "\n\nWrong input, please enter a data again: ";
	}
}

void write_message(std::string & message)
{
	while (true)
	{
		std::cin.get();
		char ch = std::cin.get();
		if (ch == '~')
		{
			std::cout << "\nWrite your message again:\n";
			continue;
		}
		while (ch != '~')
		{
			message.push_back(ch);
			ch = std::cin.get();
		}
		break;
	}
}

std::streampos check_file_size(std::iostream & fios)
{
	fios.seekp(0, std::ios::end);
	std::streampos size = fios.tellp();
	std::cout << "\nSize - " << size << std::endl;
	return size;
}




void interactive()
{
	uint number;
	message_base test;
	while (true)
	{
		std::cout << "\nWrite number 0-16:\n1 - Create random list\n2 - Add your own elements\n3 - Write in the file\n4 - Read from the file\n5 - Write in the binary file\n6 - Read from the binary file\n7 - Search for a time interval\n8 - Search for a type and a system loading\n9 - Search for a text fragment\n10 - Write to console\n11 - Delete last message\n12 - Delete for message\n13 - Overwrite message\n14 - Clear the file\n15 - Clear the binary file\n16 - Clear the list\n17 - Sort\n\n0 - Exit\n";
		write_num(number);

		if (number == 1)
		{
			std::cout << "\nWrite number of elements: ";
			write_num(number);
			test.create_rand_list(number);
			continue;
		}
		else if (number == 2)
		{
			std::string message;
			std::cout << "\nEnter message. Press \"~ + Enter\" to stop:\n";
			write_message(message);

			test.push_back(message_base::data_msg(message));
			continue;
		}
		else if (number == 3)
		{
			std::ofstream fout;
			fout.open("text.txt", std::ofstream::app | std::ofstream::out);
			if (!fout.is_open()) { throw std::exception("File isn't open"); }
			fout << test;
			fout.close();
			continue;
		}
		else if (number == 4)
		{
			std::ifstream fin;
			fin.open("text.txt", std::ifstream::in);
			fin >> test;
			fin.close();
			continue;
		}
		else if (number == 5)
		{
			test.bin_out();
			continue;
		}
		else if (number == 6)
		{
			test.bin_in();
			continue;
		}
		else if (number == 7)
		{
			uint year1, month1, day1, hours1, minutes1, year2, month2, day2, hours2, minutes2;
			message_base::data_msg::date_time date1;
			message_base::data_msg::date_time date2;
			while (true)
			{
				std::cout << "\nWrite first date\nWrite year, month, day, hours, minutes:\n";
				write_num(year1);
				write_num(month1);
				write_num(day1);
				write_num(hours1);
				write_num(minutes1);
				std::cout << "\n\nWrite second date\nWrite year, month, day, hours, minutes:\n";
				write_num(year2);
				write_num(month2);
				write_num(day2);
				write_num(hours2);
				write_num(minutes2);

				message_base::data_msg::date_time date1(year1, month1, day1, hours1, minutes1);
				message_base::data_msg::date_time date2(year2, month2, day2, hours2, minutes2);

				if (!date1.check_date() || !date2.check_date() || !(date1 < date2))
				{
					std::cout << "\n\nWrong dates. Please write again:";
					continue;
				}
				else break;
			}

			message_base* temp = test.search_for_time_interval(date1, date2);
			if (temp == nullptr) std::cout << "\nMessages aren't found\n";
			else std::cout << std::endl << *temp;

			delete temp;
			continue;
		}
		else if (number == 8)
		{
			uint type;
			double system_loading;

			while (true)
			{
				std::cout << "\nWrite message type:\n0 - Debug\n1 - Error\n2 - Fatal\n3 - Info\n4 - Warning\n";
				write_num(type);

				std::cout << "\n\nWrite system loading from 0 to 1:\n";
				write_num(system_loading);

				if (!(type <= 4 && type >= 0 && system_loading <= 1 && system_loading >= 0))
				{
					std::cout << "\n\nWrong dates. Please write again:";
					continue;
				}
				else break;
			}

			message_base* temp = test.search_for_type_and_system_loading(type, system_loading);
			if (temp == nullptr) std::cout << "\nMessages aren't found\n";
			else std::cout << std::endl << *temp;

			delete temp;
			continue;
		}
		else if (number == 9)
		{
			std::string fragment;
			std::cout << "\nEnter message. Press \"~ + Enter\" to stop:\n";
			write_message(fragment);

			message_base* temp = test.search_for_fragment(fragment);
			if (temp == nullptr) std::cout << "\nMessages aren't found\n";
			else std::cout << std::endl << *temp;

			delete temp;
			continue;
		}
		else if (number == 10)
		{
			if (test.list.empty()) std::cout << "\nList is empty\n";
			std::cout << std::endl << test;
			continue;
		}
		else if (number == 11)
		{
			test.pop_back();
			continue;
		}
		else if (number == 12)
		{
			std::string message;
			std::cout << "\nWrite a message for delete.\nPress \"~ + Enter\" to stop:\n";
			write_message(message);
			test.pop_for_message(message);
			continue;
		}
		else if (number == 13)
		{
			std::string old_message, new_message;
			std::cout << "\nWrite a message for overwrite.\nPress \"~ + Enter\" to stop:\n";
			write_message(old_message);
			std::cout << "\nWrite a new message.\nPress \"~ + Enter\" to stop:\n";
			write_message(new_message);
			test.modificate_message(old_message, new_message);
			continue;
		}
		else if (number == 14)
		{
			std::ofstream fout;
			fout.open("text.txt");
			fout.close();
			continue;
		}
		else if (number == 15)
		{
			std::ofstream fout;
			fout.open("binary.bin", std::ofstream::binary);
			fout.close();
			continue;
		}
		else if (number == 16)
		{
			test.list.clear();
			continue;
		}
		else if (number == 17)
		{
			sort(test);
			continue;
		}
		else if (number == 0) return;
		else
		{
			std::cout << "\nSomesing is wrong. Write again please:\n";
			continue;
		}
		break;
	}
}

void sort(message_base& test)
{
	uint number;
	while (true)
	{
		std::cout << "\nWrite number 1-3:\n1 - Counting sort\n2 - Radix sort\n3 - Sort by different fields\n";
		write_num(number);
		switch (number)
		{
		case 1:
			test.counting_sort();
			return;
		case 2:
			test.radix_sort();
			return;
		case 3:
			sort_by_fields(test);
			return;
		default:
			std::cout << "\nWrite number again\n";
			continue;
		}
	}
}





bool reverse_and_check(uint& number)
{
	if (number > 10000) return false;
	int reversed = 0;
	while (number > 0)
	{
		if (!(number % 10 <= 4 && number % 10 != 0)) return false;
		reversed = reversed * 10 + number % 10;
		number /= 10;
	}
	number = reversed;
	return true;
};

bool cmp(const message_base::data_msg& a, const message_base::data_msg& b, uint& number)
{
	switch (number % 10)
	{
	case 1:
		if(a.date == b.date)
		{
			number /= 10;
			return cmp(a, b, number);
		}
		else return (a.date < b.date);
	case 2:
		if (a.priority == b.priority)
		{
			number /= 10;
			return cmp(a, b, number);
		}
		else return (a.priority < b.priority);
	case 3:
		if (a.type == b.type)
		{
			number /= 10;
			return cmp(a, b, number);
		}
		else return (a.type < b.type);
	case 4:
		if (a.system_loading == b.system_loading)
		{
			number /= 10;
			return cmp(a, b, number);
		}
		else return (a.system_loading < b.system_loading);
	default:
		return false;
	}
}

void sort_by_fields(message_base& test)
{
	uint number;
	while (true)
	{
		std::cout << "\nWrite number 1-4:\n1 - Date\n2 - Priority\n3 - Type\n4 - System loading\nYou can sort by 1 or more fields\nExample: 134 - 1, 3, 4 fields\n";
		write_num(number);
		if (!reverse_and_check(number))
		{
			std::cout << "\nWrite number again\n";;
			continue;
		}

		std::stable_sort(test.list.begin(), test.list.end(), 
			[&](const message_base::data_msg & a, const message_base::data_msg & b)->bool
			{
				return cmp(a, b, number);
			});
		return;
	}
}


void demo()
{
	
}