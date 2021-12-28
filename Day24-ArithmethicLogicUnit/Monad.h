#pragma once
#include <vector>

struct Monad {
public:
	Monad() { update_digits(); }
	long long num() const { return number; }
	bool has_zero() const { return contains_zero; }
	std::vector<int> digits() const { return monad_digits; }
	
	void decrement();
	
private:
	void update_digits();
	long long number{ 999'999'999'999'99 };
	bool contains_zero;
	std::vector<int> monad_digits;
};