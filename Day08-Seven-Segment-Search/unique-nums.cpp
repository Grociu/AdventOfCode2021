#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


class Entry {
public:
	void add_in(std::string i) { input.push_back(i); }
	void add_out(std::string o) { output.push_back(o); }

	std::vector<std::string>input;
	std::vector<std::string>output;
};

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

int count_output_strings_of_size_n(const int n, std::vector<Entry>& data) {
	int counter{ 0 };
	for (Entry& e : data)
		for (std::string& s : e.output)
			if (s.length() == n)
				counter++;
	return counter;
}

int count_occurence_in_output(const int n, std::vector<Entry>& data) {
	switch (n) {
	case 1: return count_output_strings_of_size_n(2, data);
	case 4: return count_output_strings_of_size_n(4, data);
	case 7: return count_output_strings_of_size_n(3, data);
	case 8: return count_output_strings_of_size_n(7, data);
	default: throw std::runtime_error("Not implemented!");
	}
}

int main() {
	// parse input
	const std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };
	std::vector<Entry> entries;
	parse_input(ifs, entries);

	// calculate result
	int result { 0 };
	result += count_occurence_in_output(1, entries);
	result += count_occurence_in_output(4, entries);
	result += count_occurence_in_output(7, entries);
	result += count_occurence_in_output(8, entries);
	
	// output result to console
	std::cout << "Outputs that ar 1,4,7,8 : " << result << std::endl;
}
