#include "pch.h"

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




bool check_message_fragment(const std::string &message, const std::string &fragment)
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
void write_num(T &data)
{
	while (!(std::cin >> data))
	{
		std::cin.clear(); /* Clear errors (like the failbit flag) */
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); /* Throw away the rest of the line */
		std::cout << "\n\nWrong input, please enter a data again: ";
	}
}

void write_message(std::string &message)
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

std::streampos check_file_size(std::iostream &fios)
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
		std::cout << "\nWrite number 0-16:\n1 - Create random list\n2 - Add your own elements\n3 - Write in the file\n4 - Read from the file\n5 - Write in the binary file\n6 - Read from the binary file\n7 - Search for a time interval\n8 - Search for a type and a system loading\n9 - Search for a text fragment\n10 - Write to console\n11 - Delete last message\n12 - Delete for message\n13 - Overwrite message\n14 - Clear the file\n15 - Clear the binary file\n16 - Clear the list\n\n0 - Exit\n";
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
			
			test.insert(message_base::data_msg(message));
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
		else if (number == 0) return;
		else
		{
			std::cout << "\nSomesing is wrong. Write again please:\n";
			continue;
		}
		break;
	}
}

void demo()
{
	message_base test;
	std::cout << "\nLet start. When program is stopped press Enter to continue.\nAt first we're creating 5 random and 1 fixed elements:\n\n";
	std::cin.get();
	std::cin.get();

	test.create_rand_list(5);
	test.insert(message_base::data_msg("Hello world!\nThis is fixed message", Debug, 100, 0.34, 1019, January, 10, 17, 48));
	std::cout << test;

	std::cin.get();
	std::cout << "\nYou can notice all messages are sorted for time.\nAlso we can modificate all messages\nLet overwrite \"Random message\" to \"Changed\":";
	test.modificate_message("Random message", "Changed");
	std::cin.get();

	std::cout << test << "\nAnd then delete \"Changed\":\n";
	std::cin.get();
	test.pop_for_message("Changed");
	std::cout << test << "\nAdding 5 elements:\n";
	std::cin.get();

	test.create_rand_list(5);
	std::cout << test << "\nDelete last eleement:\n";
	std::cin.get();
	test.pop_back();
	std::cout << test << "\nSearch for time interval:\n01.10.1500 23:59 - 12.08.2000 04:11\n";
	std::cin.get();

	message_base* temp = test.search_for_time_interval(message_base::data_msg::date_time(1500, October, 1, 23, 59), message_base::data_msg::date_time(2000, August, 12, 4, 11));
	if (temp == nullptr) { std::cout << "\nResult is empty\n"; }
	else 
	{
		std::cout << (*temp); 
		delete temp;
	}

	std::cout << "\nSearch for type and system loading: Error, 0.6\n";
	std::cin.get();
	temp = test.search_for_type_and_system_loading(Error, 0.6);
	if (temp == nullptr) { std::cout << "\nResult is empty\n"; }
	else
	{
		std::cout << (*temp);
		delete temp;
	}

	std::cout << "\nSearch for text fragment: \"Rand\"\n";
	std::cin.get();
	temp = test.search_for_fragment("Rand");
	if (temp == nullptr) { std::cout << "\nResult is empty\n"; }
	else
	{
		std::cout << (*temp);
		delete temp;
		temp = nullptr;
	}

	std::cout << "\nBinary write and read";
	std::cin.get();

	std::ofstream fout; /* clear binary file */
	fout.open("binary.bin", std::ofstream::binary);
	fout.close();

	test.bin_out();
	test.bin_in();

	std::cout << "Text write and read\n";
	std::cin.get();
	std::fstream fios;
	fios.open("text.txt", std::fstream::trunc | std::fstream::in | std::fstream::out);
	fios << test;
	fios >> test;
	fios.close();

	std::cout << "\nYou can notice when we add existing message it is not added:\n\n" << test;
}

void benchmark_binary()
{
	std::ofstream fout;	/* file for result */
	fout.open("benchmark_binary.txt");
	if (!fout.is_open()) { throw std::exception("File isn't open"); }
	
	std::fstream fios;
	message_base test;
	int number = 10;
	double check_time = 0;

	while (true)
	{
		test.list.reserve(number);
		simple_timer t; /* check start */
		fios.open("binary.bin", std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
		if (!fios.is_open()) { throw std::exception("File isn't open"); }

		test.list.reserve(number);
		test.create_rand_list(number);
		test.bin_out(fios);
		fios.seekg(0, std::ios::beg);
		test.bin_in(fios);

		test.search_for_time_interval(
			message_base::data_msg::date_time(1400, April, 12, 4, 53),
			message_base::data_msg::date_time(2100, December, 4, 23, 10));
		test.search_for_fragment("Rand");
		test.search_for_type_and_system_loading(Debug, 0.6);

		check_time = t.get_duration(); /* check finish */
		fout << "For " << number << " elements:\tTime - " << check_time << "s\t\tSize of file - " << check_file_size(fios) << " bytes" << std::endl;
		fios.close();
		test.list.clear();

		if (check_time < 1) number *= 2;
		else if (check_time < 10) number += number;
		else break;
	}

	fout.close();
}

void benchmark_text()
{
	std::ofstream fout;	/* file for result */
	fout.open("benchmark_text.txt");
	if (!fout.is_open()) { throw std::exception("File isn't open"); }

	std::fstream fios;
	message_base test;
	int number = 10;
	double check_time = 0;

	while (true)
	{
		test.list.reserve(number); 
		simple_timer t; /* check start */
		fios.open("text.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
		if (!fios.is_open()) { throw std::exception("File isn't open"); }

		test.create_rand_list(number);
		fios << test;
		fios.seekg(0, std::ios::beg);
		fios >> test;

		test.search_for_time_interval(
			message_base::data_msg::date_time(1400, April, 12, 4, 53),
			message_base::data_msg::date_time(2100, December, 4, 23, 10));
		test.search_for_fragment("Rand");
		test.search_for_type_and_system_loading(Debug, 0.6);

		check_time = t.get_duration(); /* check finish */
		fout << "For " << number << " elements:\tTime - " << check_time << "s\t\tSize of file - " << check_file_size(fios) << " bytes" << std::endl;
		fios.close();
		test.list.clear();

		if (check_time < 1) number *= 2;
		else if (check_time < 10) number += number;
		else break;
	}

	fout.close();
}
