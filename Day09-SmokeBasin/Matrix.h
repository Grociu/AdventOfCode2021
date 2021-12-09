#include <vector>

class Matrix {
public:
	Matrix(const int r, const int c);
	Matrix(const std::vector<std::vector<int>> nums);

	void add_row(const std::vector<int> nums);
	void set_data(const int num, const int r, const int c);
	int get_data(const int r, const int c);
	std::vector<std::pair<int, int>> get_adjacent_coords(const int x_r, const int x_c);
	std::vector<int> get_adjacent_data(const int x_r, const int x_c);

	int num_rows() { return rows; }
	int num_columns() { return columns; }
private:
	bool in_range(const int r, const int c);

	std::vector<std::vector<int>> data;
	int rows;
	int columns;
};
