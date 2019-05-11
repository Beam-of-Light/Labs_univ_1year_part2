#include "pch.h"
#include "stack.h"


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





my_point::my_point(const double &x, const double &y, const double &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

std::ostream& operator<<(std::ostream &out, const my_point &this_point)
{
	out << "x:  " << this_point.x << "\ty:  " << this_point.y << "\tz:  " << this_point.z;

	return out;
}

std::istream& operator>>(std::istream &in, my_point &this_point)
{
	in >> this_point.x >> this_point.y >> this_point.z;

	return in;
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





void interactive()
{
	std::cout << "\nWhen we're out of range it will cause an exception\n";
	unsigned int number;
	while (true)
	{
		std::cout << "\nChoose kind of stack:\n1 - static array\n2 - dynamic array\n3 - list\n";
		write_num(number);

		if (number == 1)
		{
			stack_static st;
			interactive_stack(&st);
		}
		else if (number == 2)
		{
			stack_dynamic st;
			interactive_stack(&st);
		}
		else if (number == 3)
		{
			stack_list st;
			interactive_stack(&st);
		}
		else
		{
			std::cout << "\nWrite number again please:\n";
			continue;
		}
		break;
	}
}





void interactive_stack(stack *st)
{
	if (typeid(stack_static) == typeid(*st)) std::cout << "\n\nBe careful. Your MAX size is " << stack_static::MAX << std::endl;

	unsigned int number;
	while (true)
	{
		std::cout << "\nWrite number 0-7:\n1 - Add point\n2 - Add random point\n3 - Delete point\n4 - Peek point\n5 - Check empty\n6 - Check size\n7 - Print and delete stack\n\n0 - Exit\n";
		write_num(number);

		if (number == 1)
		{
			double x, y, z;
			std::cout << "\nWrite x, y, z:\n";
			write_num(x);
			write_num(y);
			write_num(z);

			st->push(x, y, z);
			continue;
		}
		if (number == 2)
		{
			st->push_rand();
			continue;
		}
		else if (number == 3)
		{
			st->pop();
			continue;
		}
		else if (number == 4)
		{
			std::cout << std::endl << st->peek() << std::endl;
			continue;
		}
		else if (number == 5)
		{
			std::cout << "\nStack is" << ((st->is_empty()) ? " empty\n" : "n't empty\n") << std::endl;
			continue;
		}
		else if (number == 6)
		{
			std::cout << "\nSize is " << st->size() << std::endl;
			continue;
		}
		else if (number == 7)
		{
			std::cout << "\nStack:\n";
			st->print_and_del();
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





void demo(class stack *st)
{
	std::cin.get();
	std::cout << "\nWe create 10 elements, print and delete. Also we check for empty and size\n";
	std::cin.get();

	for (size_t i = 0; i < 10; i++)
	{
		st->push_rand();
	}
	std::cout << "\nStack is" << ((st->is_empty()) ? " empty\n" : "n't empty\n") << "Size is " << st->size() << std::endl;
	st->print_and_del();
	std::cout << "\nStack is" << ((st->is_empty()) ? " empty\n" : "n't empty\n") << "Size is " << st->size() << std::endl;
	std::cin.get();
}




void benchmark()
{
	std::ofstream fout;	/* file for result */
	fout.open("benchmark_result.txt");
	if (!fout.is_open()) { throw std::exception("File isn't open"); }

	fout << "Stack based on static array:\n";
	stack_static test1;
	benchmark_stack(&test1, fout);

	fout << "\nStack based on dynamic array:\n";
	stack_dynamic test2;
	benchmark_stack(&test2, fout);

	fout << "\nStack based on list:\n";
	stack_list test3;
	benchmark_stack(&test3, fout);

	fout.close();
	std::cout << "\nBenchmark is complited\n";
}


void benchmark_stack(stack* test, std::ofstream& fout)
{
	double check_time = 0;
	simple_timer t; /* check start */
	for (size_t i = 0; i < 10000; i++)
	{
		test->push_rand();
	}
	for (size_t i = 0; i < 10000; i++)
	{
		test->pop();
	}

	check_time = t.get_duration(); /* check finish */
	fout << "For 10000 elements added and deleted:\tTime - " << check_time << std::endl;
}