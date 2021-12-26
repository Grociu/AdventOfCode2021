#include <set>
#include <iostream>
#include "Gamestate.h"


// BOARD Schematics
/////////////////////////////
// 0-1-2-3-4-5-6-7-8-9-10  // 11 possible positions on the corridor
//     -   -   -   -
//     21  41  61  81
//     -   -   -   -
//     22  42  62  82
////////////////////////////

// position of a token on this board is represented by a map<int, char> 
// where int represents a position, and char a character in that position

// INPUT READ - can be done by reading from file, but this is skipped

/*
// test input
const std::map<int, char> input = {
	{21, 'B'}, {22, 'A'}, {41, 'C'}, {42, 'D'},
	{61, 'B'}, {62, 'C'}, {81, 'D'}, {82, 'A'}
};
*/


// puzzle input
std::map<int, char> input = {
	{21, 'C'}, {22, 'C'}, {41, 'B'}, {42, 'D'},
	{61, 'A'}, {62, 'A'}, {81, 'D'}, {82, 'B'}
};


// winning state
const std::map<int, char> win_state = {
	{21, 'A'}, {22, 'A'}, {41, 'B'}, {42, 'B'},
	{61, 'C'}, {62, 'C'}, {81, 'D'}, {82, 'D'}
};


int main() {
	// initialize game
	Gamestate initial{ input };
	std::set<Gamestate> gamestates;
	gamestates.insert(initial);

	// looking for these values
	bool first_set{ false };
	Gamestate first_win_g;
	Gamestate last_win_g;
	int winning_g{ 0 };

	// ALGORITHM
	// Gamestates are sorted in the set by expended energy
	// Take, the gamestate requiring least energy, save and remove it from the set,
	// Check if it's a winning Gamestate, if yes, return, if no move on down
	// Calculate all possible legal moves from that saved state.
	// For each of those moves excecute the move and save the new gamestate into the set
	// repeat until a winnig state is found, since they will be sorted by smallest energy, the first winning one will be the one requiring the least energy

	while (gamestates.size() > 0) {

		// get gamestate with lowest energy needed;
		Gamestate g = *gamestates.begin();
		gamestates.erase(gamestates.begin());

		// win condition
		if (g.is_winning()) { 
			if (!first_set) {
				first_win_g = g;
				first_set = true;
			}
			last_win_g = g;
			winning_g++;
			continue;
		}
		
		// calculate legal moves
		std::vector<Move> legal_moves = g.legal_moves();
		
		// make all the legal moves and update gamestates
		for (const Move& m : legal_moves) {
			Gamestate new_g = g;
			new_g.make_move(m);
			gamestates.insert(new_g);
		}

	}
	
	std::cout << "Lowest energy needed: " << first_win_g.energy_used << std::endl;
	std::cout << "Greatest energy needed: " << last_win_g.energy_used << std::endl;
	std::cout << "Winning combinations: " << last_win_g.energy_used << std::endl;

}