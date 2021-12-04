#include "Matrix.h"


Matrix::Matrix(const int r, const int c) : rows{ r }, columns{ c } {
		for (int i = 0; i < r; i++) data.push_back(std::vector<int>( c, 0 ));
	}

Matrix::Matrix(const std::vector<std::vector<int>> nums) {
	rows = nums[0].size();
	columns = nums.size();
	data = nums;
}

void Matrix::set_data(const int num, const int r, const int c) {if(in_range(r,c)) data[r][c] = num; }

int Matrix::get_data(const int r, const int c) {if (in_range(r, c)) return data[r][c]; }

bool Matrix::in_range(int r, int c) { return r >= 0 && r < rows&& c >= 0 && c < columns; }
