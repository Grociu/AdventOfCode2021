#include "Matrix.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

// read input for single digit entries not separated by sepatrators
void parse_input(std::ifstream& ifs, Matrix& data) {
	std::string line;
	//for each line
	while (std::getline(ifs, line)) {
		std::vector<int> nums;
		std::istringstream iss(line);
		char c;
		while (iss >> c) {
			int i = c - '0'; //converts digit to int
			nums.push_back(i);
		}
		data.add_row(nums);
	}
}

int min(std::vector<int> v) {
	int m = v[0];
	for (int i : v) if (i < m) m = i;
	return m;

}

int main() {
	const std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };
	Matrix heatmap{ 0, 0 };
	parse_input(ifs, heatmap);

	int sum_risk_level{ 0 };
	
	// for each row
	for (int r = 0; r < heatmap.num_rows(); r++) {
		// for each column
		for (int c = 0; c < heatmap.num_columns(); c++) {
			int heat = heatmap.get_data(r, c);
			if (heat < min(heatmap.get_adjacent_data(r, c))) {
				sum_risk_level += heat + 1;
			}
		}
	}

	// output to console
	std::cout << "Risk level is equal to: " << sum_risk_level << std::endl;
}