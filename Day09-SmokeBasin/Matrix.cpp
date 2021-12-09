#include "Matrix.h"
#include <stdexcept>
#include <iostream>


Matrix::Matrix(const int r, const int c) : rows{ r }, columns{ c } {
	for (int i = 0; i < r; i++) data.push_back(std::vector<int>(c, 0));
}

Matrix::Matrix(const std::vector<std::vector<int>> nums) {
	rows = nums[0].size();
	columns = nums.size();
	data = nums;
}

void Matrix::add_row(const std::vector<int> nums) {
	rows++;
	columns = std::max(columns, int(nums.size()));
	data.push_back(nums);
}

void Matrix::set_data(const int num, const int r, const int c) {
	if (in_range(r, c)) data[r][c] = num;
	else throw std::out_of_range("Matrix::set_data(): Index not in range");
}

int Matrix::get_data(const int r, const int c) {
	if (in_range(r, c)) return data[r][c];
	else throw std::out_of_range("Matrix::get_data(): Index not in range");
}

bool Matrix::in_range(const int r, const int c) { return r >= 0 && r < rows && c >= 0 && c < columns; }


std::vector<std::pair<int, int>> Matrix::get_adjacent_coords(const int x_r, const int x_c) {

	std::vector<std::pair<int, int>> adjacent_coords;
	std::vector<std::pair<int, int>> pairs{ {x_r, x_c - 1}, {x_r, x_c + 1}, {x_r - 1, x_c}, {x_r + 1, x_c} };
	for (std::pair<int, int>& x : pairs) {
		if (in_range(x.first, x.second)) adjacent_coords.push_back(x);
	}
	return adjacent_coords;
}

std::vector<int> Matrix::get_adjacent_data(const int x_r, const int x_c) {
	
	std::vector<int> adjacent_values;
	for (std::pair<int, int>& x : get_adjacent_coords(x_r, x_c)) {
		// this is range checked by get_adjacent coords
		adjacent_values.push_back(get_data(x.first, x.second));
	}
	return adjacent_values;
}
