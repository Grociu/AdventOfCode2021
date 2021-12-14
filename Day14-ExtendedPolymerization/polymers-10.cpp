#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


// INPUT HANDLING
void read_base(std::istream& is, std::string& base) {is >> base;}

void read_instructions(std::istream& is, std::map<std::string, char>& instr) {
	std::string key;
	std::string delimiter;
	char value;
	while (is >> key >> delimiter >> value) instr[key] = value;
}

void print_input(const std::string& s, const std::map<std::string, char>& i) {
	std::cout << "Sequence: " << s << std::endl;
	std::cout << "Instructions:" << std::endl;
	for (auto& in : i) std::cout << in.first << " : " << in.second << std::endl;
	std::cout << "Instructions End." << std::endl;
}

// DEFINING A STEP
void execute_step(std::string& sequence, const std::map<std::string, char>& instructions) {
	// IDEA: if characters are inserted by reverse iteration, indexes before dont change
	std::string next;
	next += sequence[0];
	// find indexes of keys in the sequence
	for (int i = 0; i < sequence.length()-1; i++) {
		std::string i_pair = sequence.substr(i, 2);
		try {next += instructions.at(i_pair);}
		catch (...) {}
		next += i_pair[1];
	}
	sequence = next;
}

void count_occurences(const std::string& sequence, std::map<char, int>& occurences) {
	occurences.clear();
	for (const char& c : sequence) {
		try { occurences.at(c)++; }
		catch (std::out_of_range) { occurences[c] = 1; };
	}
}

int calculate_result(const std::map<char, int>& occurences) {
	int max = std::max_element(occurences.begin(), occurences.end(), 
		// lambda function to define the greater value
		[](const std::pair<char, int>& p1, const std::pair<char, int>& p2) {return p1.second < p2.second;}
	)->second;
	std::cout << max << std::endl;
	int min = std::min_element(occurences.begin(), occurences.end(),
		[](const std::pair<char, int>& p1, const std::pair<char, int>& p2) {return p1.second < p2.second; }
	)->second;
	std::cout << min << std::endl;
	return max - min;
}


int main() {
	// read input
	const std::string input_filename = "Input.txt";
	//const std::string input_filename = "TestInput1.txt";
	std::ifstream ifs{ input_filename };
	std::string sequence;
	std::map<std::string, char> instructions;
	read_base(ifs, sequence);
	read_instructions(ifs, instructions);
	//DEBUG print_input(sequence, instructions);
	const int NUMBER_OF_STEPS{ 10 };
	for (int i = 0; i < NUMBER_OF_STEPS; i++) {
		execute_step(sequence, instructions);
		//std::cout << sequence << std::endl;
	}
	std::map<char, int> occurences;
	count_occurences(sequence, occurences);
	for (const auto& p : occurences) { std::cout << p.first << " " << p.second << std::endl; }
	std::cout << "End result is " << calculate_result(occurences) << std::endl;
}