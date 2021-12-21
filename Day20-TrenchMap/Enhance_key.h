#pragma once
#include <vector>
#include <iostream>

struct Enhance_key
{
	Enhance_key() {
		key = std::vector<bool>(512, false);
	}
	bool get(const int i) const { return key[i]; }
	std::vector<bool> key;;
};

std::istream& operator>>(std::istream& is, Enhance_key& k);
