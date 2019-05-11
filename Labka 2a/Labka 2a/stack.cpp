#include "pch.h"
#include "stack.h"

stack_static::stack_static()
{
	_size = 0;
}

size_t stack_static::size() const
{
	return size_t(_size);
}

bool stack_static::is_empty() const
{
	return (_size == 0);
}

void stack_static::push(const double &x, const double &y, const double &z)
{
	if (!is_free_space()) { throw std::exception("There is no free space"); }

	array[_size] = my_point(x, y, z);
	_size++;
}

void stack_static::push(const my_point &this_point)
{
	if (!is_free_space()) { throw std::exception("There is no free space"); }

	array[_size] = this_point;
	_size++;
}

void stack_static::push_rand()
{
	if (!is_free_space()) { throw std::exception("There is no free space"); }

	array[_size] = my_point((rand() % 201 - 100), (rand() % 201 - 100), (rand() % 201 - 100));
	_size++;
}

void stack_static::pop()
{
	if (is_empty()) { throw std::exception("Stack is empty"); }

	array[_size - 1] = my_point();
	_size--;
}

const my_point& stack_static::peek() const
{
	if (is_empty()) { throw std::exception("Stack is empty"); }

	return array[_size - 1];
}

void stack_static::print_and_del()
{
	while (_size != 0)
	{
		std::cout << std::endl << peek() << std::endl;
		pop();
	}
}

bool stack_static::is_free_space() const
{	// check for free space
	return (MAX - _size > 0);
}





stack_dynamic::stack_dynamic()
{
	array.reserve(10);
	_size = 0;
}

size_t stack_dynamic::size() const
{
	return size_t(_size);
}

bool stack_dynamic::is_empty() const
{
	return (_size == 0);
}

void stack_dynamic::push(const double &x, const double &y, const double &z)
{
	array.push_back(my_point(x, y, z));
	_size++;
}

void stack_dynamic::push(const my_point &this_point)
{
	array.push_back(this_point);
	_size++;
}

void stack_dynamic::push_rand()
{
	array.push_back(my_point((rand() % 201 - 100), (rand() % 201 - 100), (rand() % 201 - 100)));
	_size++;
}

void stack_dynamic::pop()
{
	if (is_empty()) { throw std::exception("Stack is empty"); }

	array.pop_back();
	_size--;
}

const my_point& stack_dynamic::peek() const
{
	if (is_empty()) { throw std::exception("Stack is empty"); }

	return array[_size - 1];
}

void stack_dynamic::print_and_del()
{
	while (_size != 0)
	{
		std::cout << std::endl << peek() << std::endl;
		pop();
	}
}




stack_list::list_point::list_point()
{
	next = nullptr;
}

stack_list::list_point::list_point(list_point* const next, const my_point &point)
{
	this->point = point;
	this->next = next;
}

stack_list::stack_list()
{	// create empty list
	list = nullptr;
	_size = 0;
}

stack_list::~stack_list()
{	// clear list
	while (list != nullptr) { pop(); }
}

size_t stack_list::size() const
{
	return size_t(_size);
}

bool stack_list::is_empty() const
{
	return (list == nullptr);
}

void stack_list::push(const double &x, const double &y, const double &z)
{
	list_point *temp = new list_point(list, my_point(x, y, z));

	list = temp;
	_size++;
}

void stack_list::push(const my_point &this_point)
{
	list_point *temp = new list_point(list, this_point);

	list = temp;
	_size++;
}

void stack_list::push_rand()
{
	list_point *temp = new list_point(list, my_point((rand() % 201 - 100), (rand() % 201 - 100), (rand() % 201 - 100)));

	list = temp;
	_size++;
}

void stack_list::pop()
{
	if (list == nullptr) { throw std::exception("Stack is empty"); }

	list_point *temp = list;
	list = list->next;
	delete temp;
	_size--;
}

const my_point& stack_list::peek() const
{
	if (list == nullptr) { throw std::exception("Stack is empty"); }

	return list->point;
}

void stack_list::print_and_del()
{
	while (list != nullptr)
	{
		std::cout << std::endl << peek() << std::endl;
		pop();
	}
}
