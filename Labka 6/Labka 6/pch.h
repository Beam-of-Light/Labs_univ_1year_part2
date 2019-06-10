#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>

int generate_int(const int low = 0, const int high = 100);
double generate_real(const double low = 0.0, const double high = 1.0);

class complex
{
private:
	double a, b; /* z = a + bi */

public:
	complex();
	complex(double a, double b);
	double get_a() const;
	double get_b() const;

	double calc_value() const;
	void print() const;

	friend complex operator+(const complex& z, const complex& w);
	friend complex operator-(const complex& z, const complex& w);
	friend complex operator*(const complex& z, const complex& w);
	friend complex operator*(int integer, const complex& w);
	friend bool operator==(const complex& z, const complex& w);
	friend class ordered_list;
};

#endif /* PCH_H */