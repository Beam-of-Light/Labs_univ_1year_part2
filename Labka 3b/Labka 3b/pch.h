#ifndef PCH_H
#define PCH_H

enum MONTH { January = 1, February, March, April, May, June, July, August, September, October, November, December };
enum MSG_TYPE { Debug, Info, Warning, Error, Fatal };

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <functional>


class simple_timer
{
public:
	simple_timer();
	double get_duration();

private:
	std::chrono::time_point<std::chrono::steady_clock> start, finish;
};


bool check_message_fragment(const std::string& message, const std::string& fragment);

template <typename T>
void write_num(T& data);
void write_message(std::string& message);

void interactive();
void sort(class message_base& test);
void sort_by_fields(message_base& test);
void demo();
void benchmark();

#endif