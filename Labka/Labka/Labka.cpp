#include "pch.h"
#include "message_base.h"



int main()
{
	try
	{
		srand(time(NULL));
		uint number;
		while (true)
		{
			std::cout << "Write number 1-3:\n1 - Interactive\n2 - Demo\n3 - Benchmark of the binary save\n4 - Benchmark of the text save\n";
			write_num(number);

			if (number == 1) interactive();
			else if (number == 2) demo();
			else if (number == 3) benchmark_binary();
			else if (number == 4) benchmark_text();
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
		std::cout << ex.what();
	}

	return 0;
}