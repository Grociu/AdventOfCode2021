#include "Matrix.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

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

// is the element in a given vector?
bool is_in(const std::pair<int, int>& p, const std::vector<std::pair<int, int>> & data) {
	auto result = std::find(begin(data), end(data), p);
	return result != std::end(data);
}

int min(std::vector<int> v) {
	int m = v[0];
	for (int i : v) if (i < m) m = i;
	return m;

}

// for a Matrix data with a lowpoint of row coordinate r_lp and column coordinate c_lp
// count elements of it's 'basin' as defined in Instructions-Part2.
int count_elements_of_basin(const int r_lp, const int c_lp, Matrix& data) {
	// elements to process. will work like a stack, but needs to be iterated over (to avoid duplicate counting)
	//std::cout << "COUNTING BASIN: (" << r_lp << "," << c_lp << ")" << std::endl;

	std::vector < std::pair<int, int> > todo_stack;
	// add a starting element
	todo_stack.push_back({ r_lp, c_lp });

	// already processed elements, at the end will be  counted to get the size of basin
	std::vector < std::pair<int, int> > processed;
	
	while (todo_stack.size() > 0) {
		std::pair<int, int> current = todo_stack.back();
		//std::cout << "Processing: (" << current.first << "," << current.second << ")" << std::endl;
		// remove current from todo_stack
		todo_stack.pop_back();
		//std::cout << " TODO size: " << todo_stack.size() << std::endl;
		//std::cout << " Processed size: " << processed.size() << std::endl;
		int heat_value = data.get_data(current.first, current.second);
		for (std::pair<int, int>& p : data.get_adjacent_coords(current.first, current.second)) {
			int p_heat = data.get_data(p.first, p.second);
			// for each adjacent, if value is not 9, but still larger than current, and the pair is not waiting to be processed, add to processing
			if (p_heat != 9 && p_heat > heat_value && !is_in(p, todo_stack) && !is_in(p, processed)) {
				// new entry detected
				todo_stack.push_back(p);
			}
		}
		processed.push_back(current);
	}
	return processed.size();
}

int main() {
	const std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };
	Matrix heatmap{ 0, 0 };
	parse_input(ifs, heatmap);

	// build a vector of low_points
	std::vector<std::pair<int, int>> low_points;
	// for each row
	for (int r = 0; r < heatmap.num_rows(); r++) {
		// for each column
		for (int c = 0; c < heatmap.num_columns(); c++) {
			int heat = heatmap.get_data(r, c);
			// 9 is the maximum value,  will never be a low point
			if (heat != 9 && heat < min(heatmap.get_adjacent_data(r, c))) {
				low_points.push_back({ r,c });
			}
		}
	}

	// assertions
	// each point (other than 9s) are a part of exactly one basin,
	// each low-point is a part of exactly one basin
	// each basin will go 'up' in value with each step from the low-point
	// therefore we can traverse from low point going 'up' by value towards the value 9, counting points on the way
	std::vector<int> basin_sizes;

	for (std::pair<int, int>& p : low_points) {
		basin_sizes.push_back(count_elements_of_basin(p.first, p.second, heatmap));
	}

	// sort the basin sizes with reverse iteration
	std::sort(basin_sizes.rbegin(), basin_sizes.rend());

	// output to console
	std::cout << "Three largest basins sizes sum up to: " << basin_sizes[0] * basin_sizes[1] * basin_sizes[2] << std::endl;
}