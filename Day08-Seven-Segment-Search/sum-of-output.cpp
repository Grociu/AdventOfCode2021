#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

// sorts characters in a string alphabethically
void char_sort(std::string& s) {
	std::sort(s.begin(), s.end());
}

class Entry {
public:
	void add_in(std::string i) { 
		char_sort(i);
		input.push_back(i); 
	}
	void add_out(std::string o) {
		char_sort(o);
		output.push_back(o);
	}
	void solve();
	int value();

	std::vector<std::string>input;
	std::vector<std::string>output;
	bool solved{ false };
	std::map<std::string, int> cypher;
};


// checks string base if it contains all the characters of string filter
bool contains_all_chars_in(const std::string& base, const std::string& filter) {
	for (char c : filter) if (base.find(c) == std::string::npos) return false;
	return true;
}

// solved the Entry, constructing a cypher decoding all the string values
void Entry::solve() {
	// solve only if not yet solved and there is input
	if (solved || input.size() == 0) return;
	// build a set of unique entries in input (contains all 10 possible inputs)
	std::set<std::string> unique;
	for (std::string s : input) unique.insert(s);
	// this will hold the string corresponding to the integer for easier lookup
	std::map<int, std::string> reverse_cypher;

	// BUILD the CYPHER

	// Basic
	// 1 only entry with length 2
	for (std::string s : unique) if (s.length() == 2) { cypher[s] = 1; reverse_cypher[1] = s; unique.erase(s); break; }
	// 4 only entry with length 4
	for (std::string s : unique) if (s.length() == 4) { cypher[s] = 4; reverse_cypher[4] = s; unique.erase(s); break; }
	// 8 only entry with length 7
	for (std::string s : unique) if (s.length() == 7) { 
		cypher[s] = 8; 
		//reverse_cypher[8] = s; // this entry was unused in the algorithm
		unique.erase(s); 
		break; 
	}
	// 7 only entry with length 3
	for (std::string s : unique) if (s.length() == 3) {
		cypher[s] = 7; 
		//reverse_cypher[7] = s;
		unique.erase(s);
		break; 
	}

	// constructive
	// remaining digits are 0 (size 6), 2 (size 5), 5 (size 5), 6 (size 6), 3 (size 5), 9 (size 6)
	// 5 is the only number of size 5, that contains the L-shaped segment remaining after subtracting representation of 1 from representation of 4
	std::string el{ "" };
	for (char c4 : reverse_cypher[4]) {
		bool ch_unique{ true };
		for (char c1 : reverse_cypher[1]) {
			if (c4 == c1) { ch_unique = false; break; }
		}
		if (ch_unique) el += c4;
	}
	for (std::string s : unique) if (s.length() == 5 && contains_all_chars_in(s, el)) {
		cypher[s] = 5;
		reverse_cypher[5] = s;
		unique.erase(s);
		break;
	}
	// 9 is a size 6 character that contains all letters of 5 ans all letters of 1
	for (std::string s : unique) if (s.length() == 6 && contains_all_chars_in(s, reverse_cypher[5]) && contains_all_chars_in(s, reverse_cypher[1])) { 
		cypher[s] = 9; 
		//reverse_cypher[9] = s;
		unique.erase(s); break;
	}
	// remaining digits are 0 (size 6), 2 (size 5), 6 (size 6), 3 (size 5)
	// 6 is the remaining size 6 character that contains 5
	for (std::string s : unique) if (s.length() == 6 && contains_all_chars_in(s, reverse_cypher[5])) {
		cypher[s] = 6;
		//reverse_cypher[6] = s;
		unique.erase(s);
		break;
	}
	// 0 is the remainin size 6 character
	for (std::string s : unique) if (s.length() == 6) {
		cypher[s] = 0;
		//reverse_cypher[0] = s;
		unique.erase(s);
		break;
	}
	// remaining digits are 2 (size 5), 3 (size 5)
	// 3 contains 1
	for (std::string s : unique) {
		if (contains_all_chars_in(s, reverse_cypher[1])) {
			cypher[s] = 3;
			//reverse_cypher[3] = s;
		}
		else {
			cypher[s] = 2;
			//reverse_cypher[2] = s;
		}
	}
	// no numbes remain, the entry is solved
	solved = true;
}

// returns the value of an entry, by reading the letters and checking them against the cypher
int Entry::value() {
	solve();
	if (!solved) throw std::runtime_error("Entry::solve() did not produce result. Solving before input?");
	int sum{ 0 };
	for (int i = 0; i < output.size(); i++) {
		sum += cypher[output[i]] * pow(10, output.size() - i - 1);
	}
	return sum;
}

// define an input operator for an Entry object
std::istream& operator>>(std::istream& ifs, Entry& e) {
	bool in{ true };
	char c;
	// check each characcter
	while (ifs >> c) {
		// it's a letter
		if (isalpha(c)) {
			ifs.putback(c);
			std::string word;
			ifs >> word;
			if (in) e.add_in(word);
			else e.add_out(word);
		}
		else if (c == '|') in = false;
	}
	return ifs;
}

// reads a file stream into a vector of entries
void parse_input(std::ifstream& ifs, std::vector<Entry>& data) {
	std::string line;
	//for each line
	while (std::getline(ifs, line)) {
		Entry e;
		std::istringstream iss(line);
		iss >> e;
		data.push_back(e);
	}
}


int main() {
	// parse input
	const std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };
	std::vector<Entry> entries;
	parse_input(ifs, entries);
	
	// calculate result
	int sum_of_entries{0};
	for (Entry& e : entries) sum_of_entries += e.value();

	// output result to console
	std::cout << "Sum of all entries is: " << sum_of_entries << std::endl;
}
