#include "Bingo_board.h"
#include <iostream>

Bingo_board::Bingo_board(int r, int c) : rows{ r }, columns{ c } {}

Bingo_board::Bingo_board(const std::vector<std::vector<int>> nums) {
	rows = nums.size();
	columns = nums[0].size();
	data = Matrix{ nums };
	guessed = Matrix{ rows, columns };
}

void Bingo_board::set_data(int num, int r, int c) { data.set_data(num, r, c); }

void Bingo_board::guess(int num) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			//DEBUG std::cout << "row: " << i << " column: " << j << " value: " << data.get_data(i, j) << " guessing: " << num << std::endl;
			if (num == data.get_data(i, j)) {
				//DEBUG std::cout << "found num: " << num << std::endl;
				last.hit(num, i, j); 
				guessed.set_data(1, i, j);
				return;
			}
		}
	}
}

bool Bingo_board::row_victory() {
	// this only checks last guessed number
	for (int j = 0; j < columns; j++) {
		if (!guessed.get_data(last.row, j)) return false;
	}
	return true;
}

bool Bingo_board::col_victory() {
	// this only checks last guessed number
	for (int i = 0; i < rows; i++) {
		if (!guessed.get_data(i, last.col)) return false;
	}
	return true;
}

int Bingo_board::sum_unmarked() {
	int sum{ 0 };
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			//DEBUG std::cout << guessed.get_data(i, j) << " " << i << " " << j << std::endl;
			if (!guessed.get_data(i, j)) { 
				sum += data.get_data(i, j); 
				//DEBUG std::cout << "adding: " << data.get_data(i, j) << " sum " << sum << std::endl; 
			}
		}
	}
	return sum;
}

bool Bingo_board::won_last_turn(int num_guessed) {
	if (won || num_guessed != last.num) return false;
	if (row_victory() || col_victory()) {
		won = true;
		return true; // will only be true if the number was guessed last turn
	}
	return false;
}