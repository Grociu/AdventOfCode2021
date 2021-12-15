#include <vector>
#include <stdexcept>

template<typename T>
class Matrix {
public:
	Matrix<T>(const int r, const int c) : rows{ r }, columns{ c } {
		for (int i = 0; i < r; i++) data.push_back(std::vector<T>(c, 0));
	}
	
	Matrix<T>(const int r, const int c, const T init) : rows{ r }, columns{ c } {
		for (int i = 0; i < r; i++) data.push_back(std::vector<T>(c, T));
	}

	Matrix<T>(const std::vector<std::vector<T>> objects);

	void add_row(const std::vector<T> objects) {
		rows++;
		columns = std::max(columns, int(objects.size()));
		data.push_back(objects);
	}

	void set_data(const T object, const int r, const int c);

	T& get_data(const int r, const int c) {
		if (in_range(r, c)) return data[r][c];
		else throw std::out_of_range("Matrix::get_data(): Index not in range");
	}

	std::vector<std::pair<int, int>> get_adjacent_coords(const int x_r, const int x_c, bool diagonal = false) {

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


	std::vector<T> get_adjacent_data(const int x_r, const int x_c);

	int num_rows() const { return rows; }
	int num_columns() const { return columns; }
private:
	bool in_range(const int r, const int c) const { return r >= 0 && r < rows&& c >= 0 && c < columns; }

	std::vector<std::vector<T>> data;
	int rows;
	int columns;
};

template<typename T>
void Matrix<T>::set_data(const T object, const int r, const int c) {
	if (in_range(r, c)) data[r][c] = object;
	else throw std::out_of_range("Matrix::set_data(): Index not in range");
}