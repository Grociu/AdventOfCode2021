#pragma once
#include <map>
#include <vector>

// energy cost per move for each type of Amphipod
const std::map<char, int> COST_PER_MOVE {
	{ 'A', 1 }, {'B', 10 }, {'C', 100}, {'D', 1000}
};

struct Move {
	Move(int a, int b, int steps, char c) : 
		from{ a },
		to{ b }, 
		energy{ steps * COST_PER_MOVE.at(c)} {}

	int from;
	int to;
	int energy;
};

struct Path {
	Path(int origin) : current{ origin }, visited{ {origin} } {}
	Path(Path p, int move) : current{ move } {
		visited = p.visited;
		visited.push_back(move);
	}
	int current;
	std::vector<int> visited;
};

struct Gamestate
{
	Gamestate(std::map<int, char> init) : positions{ init }, energy_used{ 0 } {}
	Gamestate() {}
	std::map<int, char> positions;
	int energy_used;

	bool is_empty(int pos) const;
	bool is_winning() const;
	void make_move(const Move& m);
	std::vector<Move> legal_moves() const;
};

bool operator==(const Gamestate& a, const Gamestate& b); 
bool operator<(const Gamestate& a, const Gamestate& b);

std::vector<int> get_adjacent(const int& pos);

