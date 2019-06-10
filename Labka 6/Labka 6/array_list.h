#ifndef ARRAY_LIST
#define ARRAY_LIST
#include "ordered_list.h"

class array_list :
	public ordered_list
{
private:
	std::vector<node> list;

public:
	void print() const override;
	void add(const complex& data) override;
	void add_n_random(size_t n) override;
	bool pop(const complex& data) override;
	std::vector<complex>* find_by_value(double value, double e = 0) const override;
};

#endif /* ARRAY_LIST */