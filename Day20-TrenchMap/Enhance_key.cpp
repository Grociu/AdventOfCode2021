#include "Enhance_key.h"
#include <string>
#include <sstream>

std::istream& operator>>(std::istream& is, Enhance_key& k) {
	std::string line;
	std::getline(is, line);
	std::istringstream iss{ line };
	
	char c;
	int i{ 0 };
	while(iss >> c) {
		switch (c) {
		case '.': break;
		case '#': { k.key[i] = true; break; }
		default: return is;
		}
		i++;
	}
	return is;
}