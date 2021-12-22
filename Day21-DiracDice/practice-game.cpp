#include <vector>
#include <iostream>

class Deterministic_die {

public:
	Deterministic_die(int n, int initial) : sides{ n }, last_result{ initial } {};
	int roll() {
		last_result++;
		if (last_result > sides) last_result = 1;
		times_rolled++;
		return last_result;
	}

	int times_rolled{ 0 };

private:
	int sides;
	int last_result{ 0 };

};

class Board {
public:
	Board(int n) : num_squares{ n } {}
	const int num_squares;
	const static int WIN_CON{ 1000 };
};

class Player {
public:
	Player(int start_square, Board& b) : square{ start_square }, board{ b }{}

	void take_turn(Deterministic_die& die) {
		int turn_result{0};
		for (int i = 0; i < 3; i++) turn_result += die.roll();
		square += turn_result;
		while (square > board.num_squares) square -= board.num_squares;
		score += square;
		if (score >= board.WIN_CON) has_won = true;
	}

	int square;
	Board& board;
	int score{ 0 };
	bool has_won{ false };
};


int main() {

	Deterministic_die d100(100, 0);
	Board board(10);

	// input readout skipped - should be easy looking for digits
	std::vector<Player> players{Player(5,board), Player(10,board)};

	// play game
	int active_player{ 0 };
	while (!players[0].has_won && !players[1].has_won) {
		players[active_player].take_turn(d100);
		active_player++;
		if (active_player >= players.size()) active_player -= players.size();
	}

	// find losing player
	Player& loser = players[0].has_won ? players[1] : players[0];

	// output result
	std::cout << "Loser score: " << loser.score << " Die rolled: " << d100.times_rolled << " times. Product: " << loser.score * d100.times_rolled << std::endl;

}