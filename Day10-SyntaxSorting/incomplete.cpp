#include <map>
#include <stack>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// Table of points for each syntax error
const std::map<char, int> ERROR_POINTS = {
	{')', 3},
	{']', 57},
	{'}', 1197},
	{'>', 25137}
};

// Table of syntax closers
const std::map<char, char> CLOSING_CHARACTER = {
	{ '(', ')'},
	{ '[', ']'},
	{ '{', '}'},
	{ '<', '>'}
};

// Table of points fror unhandled chunks closer
// NOTE: Due to use in code this contains 'openers' as keys instead of 'closers'
const std::map<char, int> INCOMPLETE_POINTS = {
	{'(', 1},
	{'[', 2},
	{'{', 3},
	{'<', 4}
};


int main() {

	// this will count the error score
	int error_score{ 0 };
	// this will hold the inomplete lines scores
	std::vector<long long int> incomplete_scores;
	//open file
	const std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };

	//read file lines
	std::string line;
	while (std::getline(ifs, line)) {

		// setup for evaluating the line
		std::stack<char> line_stack;
		bool line_corrupted{ false };

		// read characters in the line
		std::istringstream iss{ line };
		char c;
		while (iss >> c && !line_corrupted) {
			// character is either opening a chunk, or attempting to close a chunk
			// character is opening a chunk if it can be found in CLOSING_CHARACTER keys
			// action - add it to the STACK
			if (CLOSING_CHARACTER.find(c) != CLOSING_CHARACTER.end()) line_stack.push(c);
			// else character is attempting to close a chunk - check if top of the stack is matching the chunk closer
			// ACTION if it is, delete the stack top
			else if (line_stack.size() > 0 && CLOSING_CHARACTER.at(line_stack.top()) == c) line_stack.pop();
			// if we arrived here, we have a corrupting character 
			else {
				error_score += ERROR_POINTS.at(c);
				line_corrupted = true;
			}
		}
		// Dealing with incomplete lines here
		// Since 'all of them' have a problem, assuming all lines that got here and are not corruted are incomplete
		if (!line_corrupted) {
			long long int line_score{ 0 };
			while (line_stack.size() > 0) {
				line_score *= 5;
				line_score += INCOMPLETE_POINTS.at(line_stack.top());
				line_stack.pop();
			}
			incomplete_scores.push_back(line_score);
		}
	}
	
	// sort the incomplete scores vector - to find the middle element
	std::sort(incomplete_scores.begin(), incomplete_scores.end());
	
	// output to console
	std::cout << "Error score of this input is : " << error_score << std::endl;
	// middle element will be at index size/2 because it's integer division and it rounds down (guaranteed odd size)
	std::cout << "Middle score of incompleted lines of this input is : " << incomplete_scores[incomplete_scores.size()/2] << std::endl;
}
