#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <list>
#include <deque>
#include <ctime>

template <typename T>
void write_num(T& data);
void print_result(std::deque<struct task>* result);

void interactive();
void demo();

#endif //PCH_H
