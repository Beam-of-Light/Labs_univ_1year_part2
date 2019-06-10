#include "linked_list.h"


void linked_list::print() const
{
	for (const auto& elem : list)
	{
		std::cout << "Value - " << elem.value << "\nz = ";
		elem.data.print();
		std::cout << std::endl;
	}
}

void linked_list::add(const complex& data)
{
	node temp(data);
	auto it = list.begin();
	for (size_t i = 0, size = list.size(); i < size && it->value < temp.value; ++i, ++it) { ; }
	list.emplace(it, temp);
}

void linked_list::add_n_random(size_t n)
{
	for (size_t i = 0; i < n; ++i) {
		add(complex());
	}
}

bool linked_list::pop(const complex& data)
{
	auto first = list.begin();
	for (size_t i = 0, size = list.size(); i < size; ++i, ++first) {
		if (first->data == data) {
			auto last = first;
			for (; i < size && last->data == data; ++i, ++last) { ; }
			list.erase(first, ++last);
			return true;
		}
	}
	return false;
}

std::vector<complex>* linked_list::find_by_value(double value, double e) const
{
	e = fabs(e);
	auto it = list.begin();
	for (size_t i = 0, size = list.size(); i < size && (value - it->value > -e); ++i, ++it) {
		if (fabs(it->value - value) <= e) {
			std::vector<complex>* result = new std::vector<complex>;
			while (fabs(it->value - value) <= e) {
				result->push_back(it->data);
				++it;
			}
			return result;
		}
	}
	return nullptr;
}
