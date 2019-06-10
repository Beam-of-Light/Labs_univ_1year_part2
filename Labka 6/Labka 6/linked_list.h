#ifndef LINKED_LIST
#define LINKED_LIST
#include "ordered_list.h"

class linked_list :
	public ordered_list
{
private:
	std::list<node> list;

public:
	void print() const override;
	void add(const complex& data) override;
	void add_n_random(size_t n) override;
	bool pop(const complex& data) override;
	std::vector<complex>* find_by_value(double value, double e = 0) const override;
};

#endif /* LINKED_LIST */