#include <iostream>
#include <fstream>
#include "Bingo_board.h"


// functions for handling input
// POSSIBLE CLEANUP: move to a separate file with a std::ifstream subclass
void read_guesses(std::ifstream& ifs, std::vector<int>& guesses) {
	char c;
	while (ifs.get(c)) {
		if (c == '\n') { ifs.get(c); break; } // read the next newline then exit
		if (isdigit(c)) {
			ifs.putback(c);
			int n;
			ifs >> n;
			guesses.push_back(n);
		}
	}
}

Bingo_board read_board(std::ifstream& ifs) {
	int row{ 0 };
	int column{ 0 };
	std::vector<std::vector<int>> nums;
	char c;
	while (ifs.get(c)) {
		// got to end of line
		if (c == '\n') {
			// is it the end of board?
			ifs.get(c);
			if (c == '\n') { 
				break; 
			}
			// otherwise c is now the first digit of the first number in the next row
			row++;
			column = 0;
		}
		if (isdigit(c)) {
			ifs.putback(c);
			int n;
			ifs >> n;
			if (column == 0) { // start new row
				nums.push_back(std::vector<int>{});
			} 
			nums[row].push_back(n);
			column++;
		}
	}
	return Bingo_board{ nums };
}

void read_boards(std::ifstream& ifs, std::vector<Bingo_board>& boards) {
	while (ifs) {
		boards.push_back(read_board(ifs));
	}
}


int main() {
	// Read input
	std::string filename = "Input.txt";
	std::ifstream ifs{ filename };

	// read the guesses first as they appear in the file first, looking for linebreak as a terminator
	std::vector<int> guesses;
	read_guesses(ifs, guesses);

	// read the bingo boards
	std::vector<Bingo_board> boards;
	read_boards(ifs, boards);

	// track whne the game is running
	bool game{ true };

	// each guess is a turn
	for (int turn : guesses) {
		// check each board each turn
		for (Bingo_board& b : boards) {
			b.guess(turn);
			// if a victory condition is reached on a board, save  and exit
			if (b.won_last_turn(turn)) {
				std::cout << "Score: " << b.sum_unmarked() * turn << std::endl;
				game = false;
				break;
			}
		}
		if (!game) break;
	}
}
