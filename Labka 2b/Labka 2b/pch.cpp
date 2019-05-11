#include "pch.h"
#include "job_scheduler.h"

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

void print_result(std::deque<task>* result)
{
	std::cout << "\nList of tasks is cleared\nResult:\n";

	for (int i = 0, size = result->size(); i < size; i++)
	{
		std::cout << "Wait time: " << result->back().wait_time << "\tBurst time:" << result->back().burst_time << "\n\n";
		result->pop_back();
	}
	delete result;
}



void interactive()
{
	unsigned int number;
	job_scheduler scheduler;

	while (true)
	{
		std::cout << "\nWrite number 0-5:\n1 - Push n random elements\n2 - Add your own elements\n3 - First come first served(FCFS)\n4 - Shortest job first(SJF)\n5 - Round Robin\n\n0 - Exit\n";
		write_num(number);
		
		if (number == 1)
		{
			std::cout << "\nWrite number of elements: ";
			write_num(number);

			scheduler.push_rand(number);
			continue;
		}
		else if (number == 2)
		{
			std::cout << "\nWrite wait and burst time:\n";
			unsigned int wait, burst;
			write_num(wait);
			write_num(burst);

			scheduler.push(wait, burst);
			continue;
		}
		else if (number == 3)
		{
			if (scheduler.is_empty())
			{
				std::cout << "\nTasks are absent\n";
				continue;
			}

			std::cout << "\nList of tasks is cleared\n";
			std::deque<task>* result = scheduler.first_come_first_served();
			print_result(result);
			continue;
		}
		else if (number == 4)
		{
			if (scheduler.is_empty())
			{
				std::cout << "\nTasks are absent\n";
				continue;
			}

			std::cout << "\nList of tasks is cleared\n";
			std::deque<task>* result = scheduler.shortest_job_first();
			print_result(result);
			continue;
		}
		else if (number == 5)
		{
			if (scheduler.is_empty())
			{
				std::cout << "\nTasks are absent\n";
				continue;
			}

			std::cout << "\nList of tasks is cleared\n";
			std::deque<task>* result = scheduler.round_robin();
			print_result(result);
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
	std::cout << "\nPress any key to continue\nCreate 10 tasks and do FCFS(First come first served)\n";
	std::cin.get();
	std::cin.get();

	job_scheduler scheduler;
	scheduler.push_rand(10);
	std::deque<task>* result = scheduler.first_come_first_served();
	print_result(result);


	std::cout << "\nCreate 30 tasks and do SJF(Shortest job first)\n";
	std::cin.get();

	scheduler.push_rand(30);
	result = scheduler.shortest_job_first();
	print_result(result);

	std::cout << "\nCreate 10 tasks and do Round Robin\n";
	std::cin.get();

	scheduler.push_rand(10);
	result = scheduler.round_robin();
	print_result(result);

	std::cout << "\n\nDemonstration is finished\n";
	std::cin.get();
}
