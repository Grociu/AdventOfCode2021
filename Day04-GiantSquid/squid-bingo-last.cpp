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
			//DEBUG std::cout << "read board, newline 1\n";
			// is it the end of board?
			ifs.get(c);
			if (c == '\n') {
				// DEBUG std::cout << "read board, newline 2\n";
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
			//DEBUG std::cout << "reading n: " << n <<" \n";
			if (column == 0) { // start new row
				//DEBUG std::cout << "adding new row: " << row << " \n";
				nums.push_back(std::vector<int>{});
			}
			nums[row].push_back(n);
			//DEBUG std::cout << "added n: " << n << " at: (" << row << ", " << column << ")\n";
			column++;
		}
	}
	return Bingo_board{ nums };
}

void read_boards(std::ifstream& ifs, std::vector<Bingo_board>& boards) {
	while (ifs) boards.push_back(read_board(ifs));
}


int main() {
	// read input
	std::string filename = "Input.txt";
	//std::string filename = "TestInput.txt";
	std::ifstream ifs{ filename };

	// read the guesses first as they appear in the file first, looking for linebreak as a terminator
	std::vector<int> guesses;
	read_guesses(ifs, guesses);

	// read the bingo boards
	std::vector<Bingo_board> boards;
	read_boards(ifs, boards);

	// store the scorre of the last winning board
	int last_winning_board_score{0};
	
	// execute a guess sequence
	for (int turn : guesses) {
		// pick a board
		for (Bingo_board& b : boards) {
			// if board is already won, skip
			if (b.is_won()) continue;
			b.guess(turn);
			// if this board won after this turn, update the winning sum
			// POSIBLE OPTIMIZATION: can store board index and winning turn instead. Calculate just one sum_unmrked after all turns are executed (as this board will now be skipped!)
			if (b.won_last_turn(turn)) last_winning_board_score = b.sum_unmarked() * turn;
		}
	}

	// outupt result to console
	std::cout << "Score: " << last_winning_board_score << std::endl;
}
