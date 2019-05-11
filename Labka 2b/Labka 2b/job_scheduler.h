#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H


struct task
{
	unsigned int wait_time, burst_time;

	task(const int& wait_time = (rand() % 100), const int& burst_time = (rand() % 10 + 1))
	{
		this->wait_time = wait_time;
		this->burst_time = burst_time;
	}
};



class job_scheduler
{
public:

	bool is_empty();
	void push(const int& wait_time = rand() % 100, const int& burst_time = rand() % 10 + 1);
	void push_rand(const int& n);

	std::deque<task>* first_come_first_served();	/*task 26*/
	std::deque<task>* shortest_job_first();
	std::deque<task>* round_robin();	/*task 28*/

private:
	std::list<task> tasks;
};

#endif //JOB_SCHEDULER_H