#include "Monad.h"

	
void Monad::decrement() {
	while (true) {
		number--;
		update_digits();
		if (!contains_zero) break;
	}
}

void Monad::update_digits() {
	monad_digits.clear();
	contains_zero = false;
	long long op = number;
	while (op != 0) {
		int digit = op % 10;
		if (digit == 0) {contains_zero = true; return;}
		monad_digits.push_back(digit);
		op /= 10;
	}
	reverse(monad_digits.begin(), monad_digits.end());
	return;
}