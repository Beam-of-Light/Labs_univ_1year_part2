#ifndef ORDERED_LIST
#define ORDERED_LIST
#include "pch.h"

class ordered_list
{
protected:
	class node
	{
	public:
		complex data;
		double value;

		node()
		{
			value = data.calc_value();
		}
		node(const complex& data)
		{
			this->data = data;
			value = data.calc_value();
		}
	};
public:

	virtual void print() const = 0;
	virtual void add(const complex&) = 0;
	virtual void add_n_random(size_t n) = 0;
	virtual bool pop(const complex&) = 0;
	virtual std::vector<complex>* find_by_value(double value, double e = 0) const = 0;
	
};

#endif /* ORDERED_LIST */