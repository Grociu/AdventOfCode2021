#pragma once
#include <iostream>
#include <vector>

class Snailfish_number
{

public:
	// possible types for elements
	// Undefined, Literal or Snailfish_number
	enum Sn_type { Und, Lit, Snn };
	Snailfish_number() {}
	void rank_up();
	bool needs_reducing();
	void reduce();
	// data members
	int highest_snn_subrank();
	int highest_lit_value();
	Sn_type left{ Und };
	Sn_type right{ Und };
	int rank{ 0 }; // this is the nesting level of this Sn number
	std::vector<int> nums;
	std::vector<Snailfish_number> sn_nums;
	Snailfish_number& operator+=(const Snailfish_number& other);

	}
};



std::istream& operator>>(std::istream& is, Snailfish_number& sn) {
	// read the '['
	char c;
	is >> c;
	if (c != '[') {
		is.setstate(std::ios::failbit); return is;
	}
	// increase rank
	sn.rank++;
	// read left side - id type
	is >> c;
	if (isdigit(c)) {
		// read a digit and save;
		sn.left = Snailfish_number::Lit;
		sn.nums.push_back(c - '0'); // converts digit to int
	}
	else if (c == '[') {
		// read a snailfish number and save
		sn.left = Snailfish_number::Snn;
		Snailfish_number sub_sn;
		sub_sn.rank = sn.rank;
		is.putback(c);
		is >> sub_sn;
		sn.sn_nums.push_back(sub_sn);
	}
	// read comma
	is >> c;
	if (c != ',') {
		is.setstate(std::ios::failbit); return is;
	}
	// read right side - id type
	is >> c;
	if (isdigit(c)) {
		// read a digit and save;
		sn.right = Snailfish_number::Lit;
		sn.nums.push_back(c - '0'); // converts digit to int
	}
	else if (c == '[') {
		// read a snailfish number and save
		sn.right = Snailfish_number::Snn;
		Snailfish_number sub_sn;
		sub_sn.rank = sn.rank;
		is.putback(c);
		is >> sub_sn;
		sn.sn_nums.push_back(sub_sn);
	}
	// read closer
	is >> c;
	if (c != ']') {
		is.setstate(std::ios::failbit); return is;
	}
	return is;
}

// increases rank of the number - also increases ank of all subnumbers
// performed when adding - moving to a new snailfish number
void Snailfish_number::rank_up() {
	rank++;
	for (auto& sn : sn_nums) sn.rank_up();
}

int Snailfish_number::highest_snn_subrank() {
	int max_rank{ rank };
	for (auto& snn : sn_nums) { max_rank = std::max(max_rank, snn.highest_snn_subrank()); }
	return max_rank;
}

int Snailfish_number::highest_lit_value() {
	int max_lit{ 0 };
	for (auto& lit : nums) { max_lit = std::max(max_lit, lit); }
	for (auto& snn : sn_nums) { max_lit = std::max(max_lit, snn.highest_lit_value()); }
	return max_lit;
}

bool Snailfish_number::needs_reducing() {
	if (highest_snn_subrank() >= 5) return true;
	if (highest_lit_value() >= 10) return true;
	return false;
}

void Snailfish_number::reduce() {
	int* last_literal = new int{ -1 };
	int* delete_this = last_literal;
	Snailfish_number* exploding = this;
	if (exploding->rank > 4) // find first to explode
}

Snailfish_number& Snailfish_number::operator+=(const Snailfish_number& other) {
	// [1,2] += [[3,4], 5] =>> [[1,2], [[3,4],5]]
	Snailfish_number a = *this;
	Snailfish_number b = other;
	a.rank_up();
	b.rank_up();
	Snailfish_number c;
	c.rank = 1;
	c.left = Snn;
	c.sn_nums.push_back(a);
	c.right = Snn;
	c.sn_nums.push_back(b);
	while (c.needs_reducing()) {
		c.reduce();
	}
}