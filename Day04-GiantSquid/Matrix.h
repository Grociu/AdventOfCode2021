#include <vector>

class Matrix {
public:
	Matrix(const int r, const int c);
	Matrix(const std::vector<std::vector<int>> nums);

	void set_data(const int num, const int r, const int c);
	int get_data(const int r, const int c);

private:
	bool in_range(int r, int c);
		
	std::vector<std::vector<int>> data;
	int rows;
	int columns;
};
