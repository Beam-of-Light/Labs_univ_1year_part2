#include "pch.h"

int generate_int(const int low, const int high) {
	static std::random_device rd;
	static std::seed_seq seed{ rd(), (unsigned)time(nullptr) };
	static std::mt19937 gen(seed);
	std::uniform_int_distribution<> dis(low, high);
	return dis(gen);
}

double generate_real(const double low, const double high) {
	static std::random_device rd;
	static std::seed_seq seed{ rd(), (unsigned)time(nullptr) };
	static std::mt19937 gen(seed);
	std::uniform_real_distribution<> dis(low, high);
	return dis(gen);
}






complex::complex()
{
	a = generate_real(-100.0, 100.0);
	b = generate_real(-100.0, 100.0);
}

complex::complex(double a, double b)
{
	this->a = a;
	this->b = b;
}

double complex::get_a() const
{
	return a;
}

double complex::get_b() const
{
	return b;
}

double complex::calc_value() const /* value = sqrt(a^2 + b^2) */
{	// z^2 - 20z + 19
	complex temp = (*this * *this) - (20 * *this);
	temp.a += 19;
	return sqrt(temp.a * temp.a + temp.b * temp.b);
}

void complex::print() const
{
	std::cout << a << " + " << b << 'i';
}

complex operator+(const complex& z, const complex& w)
{
	return complex(z.a + w.a, z.b + w.b);
}

complex operator-(const complex& z, const complex& w)
{
	return complex(z.a - w.a, z.b - w.b);
}

complex operator*(const complex& z, const complex& w)
{
	return complex((z.a * w.a - z.b * w.b), (z.a * w.b + z.b * w.a));
}

complex operator*(int integer, const complex & w)
{
	return complex(integer* w.a, integer* w.b);
}

bool operator==(const complex& z, const complex& w)
{
	return (z.a == w.a && z.b == w.b);
}
