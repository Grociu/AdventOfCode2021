#include "Alu.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>


void Alu::inp(const char& first, const int& num) {
	*get_ref(first) = num;
}

void Alu::inp(const char& first, const char& second) {
	inp(first, *get_ref(second));
}

void Alu::add(const char& first, const int& num) {
	*get_ref(first) += num;
}

void Alu::add(const char& first, const char& second) {
	add(first, *get_ref(second));
}

void Alu::mul(const char& first, const int& num) {
	*get_ref(first) *= num;
}
	
void Alu::mul(const char& first, const char& second) {
	mul(first, *get_ref(second));
}

void Alu::div(const char& first, const int& num) {
	if (num == 0) throw std::invalid_argument("Divided by zero!");
	*get_ref(first) /= num; // integer division
}

void Alu::div(const char first, const char& second) {
	div(first, *get_ref(second));
}

void Alu::mod(const char& first, const int& num) {
	if (*get_ref(first) < 0 || num <= 0 ) throw std::invalid_argument("Modulo operation on a<0 or b<= 0!");
	*get_ref(first) %= num;
}

void Alu::mod(const char& first, const char& second) {
	mod(first, *get_ref(second));
}

void Alu::eql(const char& first, const int& num) {
	*get_ref(first) = *get_ref(first) == num ? 1 : 0;
}

void Alu::eql(const char& first, const char& second) {
	eql(first, *get_ref(second));
}


int* Alu::get_ref(const char& c) {
	switch (c) {
	case 'w': return &w;
	case 'x': return &x;
	case 'y': return &y;
	case 'z': return &z;
	default: throw std::invalid_argument("Invalid variable, w, x, y, z are valid, asked for " + c);
	}
}


void Alu::execute_program(const Program& p, const std::vector<int>& input) {
	clear();
	int input_i{ 0 };
	for (const Instruction& instr : p.instructions) {
		switch (instr.i_type) {
		case 'i': {
			inp(instr.first, input[input_i]);
			input_i++;
			break;
		}
		case 'a': {
			switch (instr.second_c) {
			case 'n': add(instr.first, instr.second_i); break;
			default: add(instr.first, instr.second_c);
			}
			break;
		}
		case 'm': {
			switch (instr.second_c) {
			case 'n': mul(instr.first, instr.second_i); break;
			default: mul(instr.first, instr.second_c);
			}
			break;
		}
		case 'd': {
			switch (instr.second_c) {
			case 'n': div(instr.first, instr.second_i); break;
			default: div(instr.first, instr.second_c);
			}
			break;
		}
		case 'e': {
			switch (instr.second_c) {
			case 'n': eql(instr.first, instr.second_i); break;
			default: eql(instr.first, instr.second_c);
			}
			break;
		}
		default: throw std::invalid_argument("Unrecognized operation.");
		}
	}
}


void read_program_from_file(const std::string& filename, Program& p) {
	std::ifstream ifs{ filename };
	std::string line;
	while (std::getline(ifs, line)) {
		std::istringstream iss{ line };
		char i, c2, c3;
		iss >> i >> c2 >> c3;
		char f, s{'n'};
		int n{ 0 };
		iss >> f;
		switch (i) {
		case 'i':  break;
		default: {
			iss >> s;
			if (isdigit(s) || s == '-') { iss.putback(s); s = 'n'; iss >> n; }
		}
		}
		p.instructions.push_back(Instruction(i, f, s, n));
	}
}