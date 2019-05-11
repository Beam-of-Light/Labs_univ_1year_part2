#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <chrono>

class simple_timer
{
public:
	simple_timer();
	double get_duration();

private:
	std::chrono::time_point<std::chrono::steady_clock> start, finish;
};



class my_point
{
private:
	double x, y, z;

public:
	my_point(const double &x = 0, const double &y = 0, const double &z = 0);

	friend std::ostream& operator<<(std::ostream&, const my_point&);
	friend std::istream& operator>>(std::istream&, my_point&);
};

template <typename T>
void write_num(T &data);

void interactive();
void interactive_stack(class stack *st);
void demo(class stack *st);
void benchmark();
void benchmark_stack(class stack *test, std::ofstream& fout);
#endif //PCH_H
