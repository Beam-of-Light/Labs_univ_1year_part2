#include "pch.h"
#include "stack.h"
#include <iostream>

int main()
{
	try
	{
		srand(time(NULL));
		unsigned int number;
		while (true)
		{
			std::cout << "Write number 1-3:\n1 - Interactive\n2 - Demo\n3 - Benchmark\n";
			write_num(number);

			if (number == 1) interactive();
			else if (number == 2)
			{
				std::cout << "\nWhen we're out of range it will cause an exception\nPress Enter to continue\n\nStack based on a static array\n";
				stack_dynamic test1;
				std::cin.get();
				demo(&test1);

				std::cout << "\nStack based on a dynamic array\n";
				stack_dynamic test2;
				demo(&test2);

				std::cout << "\nStack based on a list\n";
				stack_dynamic test3;
				demo(&test3);

				std::cout << "\nLet delete element when stack is empty\n";
				std::cin.get();
				test3.pop();
			}
			else if (number == 3) benchmark();
			else
			{
				std::cout << "\n\nWrong input, please enter a number again: ";
				continue;
			}
			break;
		}
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}