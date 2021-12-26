#include "Gamestate.h"
#include <stdexcept>
#include <algorithm>

// winning game state positions
const std::map<int, char> win_state = {
	{21, 'A'}, {22, 'A'}, {41, 'B'}, {42, 'B'},
	{61, 'C'}, {62, 'C'}, {81, 'D'}, {82, 'D'}
};


// is this a winning position? Comparing only POSITIONS, not energy expended!
bool Gamestate::is_winning() const { return positions == win_state; }


// BOARD Schematics
/////////////////////////////
// 0-1-2-3-4-5-6-7-8-9-10  // 11 possible positions on the corridor
//     -   -   -   -
//     21  41  61  81
//     -   -   -   -
//     22  42  62  82
////////////////////////////

// returns a vector of fields adjacent to the field with position pos
std::vector<int> get_adjacent(const int& pos) {
	switch (pos) {
	case 0: return { 1 };
	case 1: case 3: case 5: case 7: case 9: return { pos - 1, pos + 1 };
	case 2: case 4: case 6: case 8: return { pos - 1, pos + 1, pos * 10 + 1 };
	case 10: return { 9 };
	case 21: case 41: case 61: case 81: return { pos + 1, pos / 10 };
	case 22: case 42: case 62: case 82: return { pos - 1 };
	default: throw std::invalid_argument("Board space not recognized");
	}
}

bool Gamestate::is_empty(int pos) const {
	try {
		char temp = positions.at(pos);
		return false;
	}
	catch (std::out_of_range) {
		return true;
	}
}


std::vector<Move> Gamestate::legal_moves() const {
	std::vector<Move> legal_moves;
	// iterate over positions
	for (auto& pos : positions) {
		
		// check if it is in the correct end position
		// pos will represent a correct win position if it appears in win_state map in the same spot
		try {
			int is_end_mod{ 0 };
			switch (pos.first) {
			case 21: case 41: case 61: case 81: { is_end_mod = 1; break; }
			case 22: case 42: case 62: case 82: { is_end_mod = -1; break; }
			default: {}
			}
			if (
				win_state.at(pos.first) == pos.second && 
				(is_empty(pos.first + is_end_mod) || positions.at(pos.first + is_end_mod) == pos.second)
				) continue;
		}
		// if error - do nothing
		catch (std::out_of_range) {}

		// marked position is NOT an end position
		// calculate possible paths for the item 
		std::vector<Path> paths;
		paths.push_back(Path(pos.first));
		
		while (paths.size() > 0) {
			// get an active
			Path p = paths.back();
			paths.pop_back();
			// get the adjacent fields to the current field
			for (int candidate : get_adjacent(p.current)) {
				// GAME RULE 0 - Cannot backtrack - if backtracking move to next candidate
				if (std::find(p.visited.begin(), p.visited.end(), candidate) != p.visited.end()) continue;
				// GAME RULE 1 - Move legal if moving to unocupied space - if candidate occupied in gamestate positions - illegal move
				if (!is_empty(candidate)) continue; // occupied - move to next candidate

				// empty spot- move possible
				// At this poit it's a valid PATH. Add it to paths
				paths.push_back(Path(p, candidate));

				// check if this is a valid LEGAL MOVE according to the game rules.
				switch (candidate) {
					// GAME RULE 2 - Cannot stop just outside any room (if that's the case the move is not legal, but a path still can be valid)
				case 2: case 4: case 6: case 8: continue;
					// GAME RULE 4 - To move to a corridor you have to start in a room, as all moves from corridor must end in a room
				case 0: case 1: case 3: case 5: case 7: case 9: case 10: {
					switch (p.visited[0]) {
					case 21: case 22: case 41: case 42: case 61: case 62: case 81: case 82: break; // move to default of main switch
					default: continue;
					}
					break;
				}
				// GAME RULE 3 - The room is of CORRECT TYPE and is EITHER empty (can only move to the 2 position) OR contains only amphipods of the CORRECT type (can only move to 1 position) 
				case 21: case 41: case 61: case 81: {
					// is niche of the correct (winning) type?
					if (pos.second != win_state.at(candidate)) continue;
					// is the following spot empty? (can't stop here if empty spot exists further in)
					if (is_empty(candidate + 1)) continue;
					// something is in the +1 spot, is it o the winning type?
					if (positions.at(candidate + 1) != win_state.at(candidate)) continue;
					// prevent the move from +1 to 0 position
					if (p.current == candidate + 1) continue;
					break;
				}
				case 22: case 42: case 62: case 82: {
					// THIS CASE SHOULD BE ALREADY FILTERED (BLOCKED) by candidate-1
					// is niche of the correct (winning) type?
					if (pos.second != win_state.at(candidate)) continue;
					break;
				}
				default:{}
				}
				// SWITCH CASE - CANDIDATE ends
				// path is a LEGAL MOVE
				legal_moves.push_back(Move{ p.visited[0], candidate, int(p.visited.size()), pos.second });
			}
			// FOR LOOP - all possible adjacent spots pathed through
		}
		// ALL PATHS CALCULTED, 
			
	}
	// ALL 8 positions handled LEGAL MOVES for candidate is full
	
	// legal moves filter, if a move that results in a 'final position can be taken' only those moves should be taken
	std::vector<Move> filtered_legal_moves;
	for (const Move& m : legal_moves) {
		switch (m.to) {
		case 21: case 22: case 41: case 42: case 61: case 62: case 81: case 82: filtered_legal_moves.push_back(m); continue;
		default: {}
		}
	}
	if (filtered_legal_moves.size() > 0) return filtered_legal_moves;
	return legal_moves;
}

void Gamestate::make_move(const Move& m) {
	char moved = positions.at(m.from);
	positions.erase(m.from);
	positions[m.to] = moved;
	energy_used += m.energy;
}

bool operator==(const Gamestate& a, const Gamestate& b) { return a.energy_used == b.energy_used && a.positions == b.positions; }

bool operator<(const Gamestate& a, const Gamestate& b) {
	if (a.energy_used < b.energy_used) return true;
	if (a.energy_used > b.energy_used) return false;
	return a.positions < b.positions; // removed in C++20
}