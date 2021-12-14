#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


// INPUT HANDLING
void read_base_string(std::istream& is, std::string& base) { is >> base; }

void generate_pairs(const std::string& base_string, std::map<std::string, long long int>& data) {
	data.clear();
	for (int i = 0; i < base_string.size() - 1; i++) {
		std::string pair = base_string.substr(i, 2);
		try { data.at(pair)++; }
		catch (std::out_of_range) { data[pair] = 1; };
	}
}

void read_instructions(std::istream& is, std::map<std::string, char>& instr) {
	std::string key;
	std::string delimiter;
	char value;
	while (is >> key >> delimiter >> value) instr[key] = value;
}

// DEFINING A STEP
void execute_step(std::map<std::string, long long int>& data, const std::map<std::string, char>& instructions) {
	// Obviously the old approach does not scale well to this number of steps.
	// New approach:
	// Track, 'pair' occurence DO NOT track the changing string!
	// EXAMPLE:
	// TEST INPUT: NNBC ====> { NN: 1, NB: 1, BC: 1 }
	// STEP 1:
	// Since instruction is NN -> C, all NN elements get erased and converted into elements NC and CN of the same number, and one c is added to the total count for the same number and so on
	
	// this tracks the occurrence of each pair in the string AFTER this move
	std::map<std::string, long long int> next;
	// for CURRENT occurence table, iterate over each pair
	for (const std::pair<std::string, long long int>& i_pair : data) {
		// 1. find the character to be inserted, assuming it will appear in the instructions
		try {
			char c;
			c = instructions.at(i_pair.first);
			// 2. construct new strings
			std::string a = i_pair.first.substr(0, 1) + c;
			std::string b = c + i_pair.first.substr(1, 1);
			// 3. count them in the next map
			try { next.at(a) += i_pair.second; } catch (std::out_of_range) { next[a] = i_pair.second; }
			try { next.at(b) += i_pair.second; } catch (std::out_of_range) { next[b] = i_pair.second; }
		}
		catch (std::out_of_range) {
			// i_pair.first did not appear in instructions
			try { next.at(i_pair.first) += i_pair.second; } catch (std::out_of_range) { next[i_pair.first] = i_pair.second; }
		}
	}
	// since we counted everything, update data to be after the STEP
	data = next;
}

void count_occurences(const std::map<std::string, long long int>& data, std::map<char, long long int>& occurences, const std::string& base_string) {
	// constructs a map of occurences of each character appearing in the sequence
	// it will be equal to the occurences at 'first' position of the pairs
	// in addition the last character will be unaccounted for, but since we always insert in the middle - the last character of the base string will be the last char of the final string
	occurences.clear();
	for (const auto& i_pair : data) {
		char c = i_pair.first[0];
		try { occurences.at(c) += i_pair.second; }
		catch (std::out_of_range) { occurences[c] = i_pair.second; };
	}
	char c = base_string.back();
	try { occurences.at(c) += 1; }
	catch (std::out_of_range) { occurences[c] = 1; };
}

long long int calculate_result(const std::map<char, long long int>& occurences) {
	long long int max = std::max_element(occurences.begin(), occurences.end(),
		// lambda function to define the greater value
		[](const std::pair<char, long long int>& p1, const std::pair<char, long long int>& p2) {return p1.second < p2.second; }
	)->second;
	std::cout << max << std::endl;
	long long int min = std::min_element(occurences.begin(), occurences.end(),
		[](const std::pair<char, long long int>& p1, const std::pair<char, long long int>& p2) {return p1.second < p2.second; }
	)->second;
	//std::cout << min << std::endl;
	return max - min;
}


int main() {
	// READ INPUT
	const std::string input_filename = "Input.txt";
	//const std::string input_filename = "TestInput1.txt";
	std::ifstream ifs{ input_filename };
	std::string base_string;
	read_base_string(ifs, base_string);
	// this will hold the pairs of characters and the number that pair occurs in the sequence 
	std::map<std::string, long long int> polymer;
	generate_pairs(base_string, polymer);
	// this will hold the character that has to be inserted between other characters (keys) each step
	std::map<std::string, char> instructions;
	read_instructions(ifs, instructions);

	// EXECUTE STEPS
	const int NUMBER_OF_STEPS{ 40 };

	for (int i = 0; i < NUMBER_OF_STEPS; i++) {
		execute_step(polymer, instructions);
	}
	
	// COUNT LETTER OCCURENCES
	std::map<char, long long int> occurences;
	count_occurences(polymer, occurences, base_string);
	//for (const auto& p : occurences) { std::cout << p.first << " " << p.second << std::endl; }
	std::cout << "End result is " << calculate_result(occurences) << std::endl;
}