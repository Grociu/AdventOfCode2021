#include "Matrix.h"
#include <stdexcept>
#include <iostream>

// Commented out template functions, need to be defined in the header for the linker not to complain
// TO DO: Find a way to have these in this file, or fix header to contain definitions and declarations separately.

/*
template<typename T>
Matrix<T>::Matrix(const int r, const int c) : rows{ r }, columns{ c } {
	for (int i = 0; i < r; i++) data.push_back(std::vector<T>(c, 0));
}
*/

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> objects) {
	rows = objects[0].size();
	columns = objects.size();
	data = objects;
}

/*
template<typename T>
void Matrix<T>::add_row(const std::vector<T> objects) {
	rows++;
	columns = std::max(columns, int(objects.size()));
	data.push_back(objects);
}
*/

/*
template<typename T>
void Matrix<T>::set_data(const T object, const int r, const int c) {
	if (in_range(r, c)) data[r][c] = object;
	else throw std::out_of_range("Matrix::set_data(): Index not in range");
}
*/

/*
template<typename T>
T& Matrix<T>::get_data(const int r, const int c) {
	if (in_range(r, c)) return data[r][c];
	else throw std::out_of_range("Matrix::get_data(): Index not in range");
}
*/

/*
template<typename T>
bool Matrix<T>::in_range(const int r, const int c) { return r >= 0 && r < rows&& c >= 0 && c < columns; }
*/

/*
template<typename T>
std::vector<std::pair<int, int>> Matrix<T>::get_adjacent_coords(const int x_r, const int x_c, bool diagonal) {

	std::vector<std::pair<int, int>> adjacent_coords;
	// get non-diagonal adjacent
	std::vector<std::pair<int, int>> pairs{ {x_r, x_c - 1}, {x_r, x_c + 1}, {x_r - 1, x_c}, {x_r + 1, x_c} };
	// get diagonal adjacent
	for (std::pair<int, int>& x : pairs) {
		if (in_range(x.first, x.second)) adjacent_coords.push_back(x);
	}
	// get diagonal adjacent
	if (diagonal) {
		std::vector<std::pair<int, int>> pairs{ {x_r - 1, x_c - 1}, {x_r + 1, x_c + 1}, {x_r - 1, x_c + 1}, {x_r + 1, x_c - 1} };
		for (std::pair<int, int>& x : pairs) {
			if (in_range(x.first, x.second)) adjacent_coords.push_back(x);
		}
	}
	return adjacent_coords;
}
*/

template<typename T>
std::vector<T> Matrix<T>::get_adjacent_data(const int x_r, const int x_c) {

	std::vector<int> adjacent_values;
	for (std::pair<int, int>& x : get_adjacent_coords(x_r, x_c)) {
		// this is range checked by get_adjacent coords
		adjacent_values.push_back(get_data(x.first, x.second));
	}
	return adjacent_values;
}
