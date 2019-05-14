#include "pch.h"

int generate_int(const int& low, const int& high) {
	static std::random_device rd; // Will be used to obtain a seed for the random number engine
	static std::seed_seq seed{ rd(), (unsigned)time(nullptr) }; // Works even if rd() is deterministic
	static std::mt19937 gen(seed); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(low, high);
	return dis(gen);
}

double generate_real() {
	static std::random_device rd; // Will be used to obtain a seed for the random number engine
	static std::seed_seq seed{ rd(), (unsigned)time(nullptr) }; // Works even if rd() is deterministic
	static std::mt19937 gen(seed); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);
	return dis(gen);
}