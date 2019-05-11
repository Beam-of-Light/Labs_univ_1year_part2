#include "pch.h"
#include "job_scheduler.h"


bool job_scheduler::is_empty()
{
	return tasks.empty();
}

void job_scheduler::push(const int& wait_time, const int& burst_time)
{	// push and sort by wait time and then by burst time
	task temp(wait_time, burst_time);
	std::list<task>::iterator it = tasks.begin();

	int i = 0, size = tasks.size();
	for (; i < size && temp.wait_time > it->wait_time; i++)
	{
		std::advance(it, 1);
	}
	for (; i < size && temp.wait_time == it->wait_time &&
		temp.burst_time > it->burst_time; i++)
	{
		std::advance(it, 1);
	}
	tasks.insert(it, temp);
}


void job_scheduler::push_rand(const int& n)
{
	for (int i = 0; i < n; i++)
	{
		push();
	}
}



std::deque<task>* job_scheduler::first_come_first_served()
{
	if (tasks.empty()) return nullptr;

	std::deque<task>* result = new std::deque<task>;
	while (!tasks.empty())
	{
		result->push_front(tasks.front());
		tasks.pop_front();
	}
	return result;
}



std::deque<task>* job_scheduler::shortest_job_first()
{
	if (tasks.empty()) return nullptr;

	std::deque<task>* result = new std::deque<task>;
	std::list<task>::iterator it = tasks.begin(), temp = it;
	std::list<task>::const_iterator end = tasks.cend();
	unsigned int time = it->wait_time; /* current time */
	
	while (!tasks.empty())
	{
		if (time < it->wait_time) time = it->wait_time;

		for (; it != end && time >= it->wait_time; std::advance(it, 1))
		{
			if (temp->burst_time > it->burst_time)
			{
				temp = it;
			}
		}
		time += temp->burst_time;

		result->push_front(*temp);
		tasks.erase(temp);

		temp = it = tasks.begin();
		end = tasks.cend();
	}
	return result;
}

std::deque<task>* job_scheduler::round_robin()
{
	if (tasks.empty()) return nullptr;

	std::deque<task>* result = new std::deque<task>;
	unsigned int quantum = rand() % 10 + 1;
	std::cout << "Quantum is " << quantum << std::endl;

	while (!tasks.empty())
	{
		std::list<task>::iterator temp = tasks.begin(), delete_temp;
		std::list<task>::const_iterator end = tasks.cend();

		while (temp != end)
		{
			result->push_front(*temp);

			if ((int)(temp->burst_time - quantum) <= 0)
			{
				delete_temp = temp;
				std::advance(temp, 1);
				tasks.erase(delete_temp);

				end = tasks.cend();
				continue;
			}
			else
			{
				temp->burst_time -= quantum;
				std::advance(temp, 1);
				continue;
			}
		}
	}

	return result;
}
