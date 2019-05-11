//Task 26, 28
#include "pch.h"
#include "job_scheduler.h"

int main()
{
	try
	{
		srand(time(0));
		unsigned int number;

		while (true)
		{
			std::cout << "Write number:\n1 - Interactive\n2 - Demo\n";
			write_num(number);

			if (number == 1) interactive();
			else if (number == 2) demo();
			else 
			{
				std::cout << "\n\nWrong input, please enter a number again: ";
				continue;
			}
			break;
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	return 0;
}