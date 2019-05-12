#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <ctime>
#include "date_time.h"
#include "algorithms.h"
#include <chrono>
#include <fstream>

class simple_timer
{
public:
	simple_timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	double get_duration()
	{
		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = finish - start;
		return duration.count();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> start, finish;
};

template <typename T>
void write_num(T& data)
{
	while (!(std::cin >> data))
	{
		std::cin.clear(); /* Clear errors (like the failbit flag) */
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); /* Throw away the rest of the line */
		std::cout << "\n\nWrong input, please enter a data again: ";
	}
}



#endif /* PCH_H */