#include "Matrix.h"

struct Last_guess {
	void hit(int n, int r, int c) {num = n;	row = r; col = c;}
	int row;
	int col;
	int num;
};

class Bingo_board {
public:
	Bingo_board(int r, int c);
	Bingo_board(std::vector<std::vector<int>> nums);

	void set_data(int num, int r, int c);
	void guess(int num);
	bool won_last_turn(int num_guessed);

	int sum_unmarked();

	bool is_won() { return won; }
private:
	bool won{ false };
	bool row_victory();
	bool col_victory();
	int rows;
	int columns;
	Last_guess last;
	Matrix data{ rows, columns };
	Matrix guessed{ rows, columns }; // initialized with 0s will turn into 1 if guessed

};