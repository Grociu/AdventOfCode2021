#pragma once

#include <vector>
#include <string>

struct Instruction {
public:
	Instruction(const char& t, const char& a, const char& b = 'n', const int& i = 0) : i_type{ t }, first{ a }, second_c{ b }, second_i{ i } {};
	char i_type;
	char first;
	char second_c;
	int second_i;
};

struct Program {
	std::vector<Instruction> instructions;
};

class Alu
{
public:
	// 6 instructions
	void inp(const char& first, const int& num);
	void inp(const char& first, const char& second);
	
	void add(const char& first, const int& num);
	void add(const char& first, const char& second);
	
	void mul(const char& first, const int& num);
	void mul(const char& first, const char& second);

	void div(const char& first, const int& num);
	void div(const char first, const char& second);

	void mod(const char& first, const int& num);
	void mod(const char& first, const char& second);

	void eql(const char& first, const int& num);
	void eql(const char& first, const char& second);

	void execute_program(const Program& p, const std::vector<int>& input);
	void clear() { w = 0; x = 0; y = 0; z = 0; }

	int* get_ref(const char& c);
	int w{ 0 };
	int x{ 0 };
	int y{ 0 };
	int z{ 0 };
};

void read_program_from_file(const std::string& filename, Program& p);