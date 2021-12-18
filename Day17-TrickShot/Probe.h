#pragma once
#include <cmath>

struct Target {
public:
	Target(int x1, int x2, int y1, int y2);
	bool is_in(int x, int y) const;
	int left() const { return x_tl; }
	int right() const { return x_br; }
	int top() const { return y_tl; }
	int bottom() const { return y_br; }
private:
	int x_tl;
	int y_tl;
	int x_br;
	int y_br;
};

class Probe
{
public:
	Probe(int x, int y) : x_velocity{ x }, y_velocity{ y } {}
	int x() const { return x_pos; }
	int y() const { return y_pos; }
	int top() const { return y_top; }
	void step();
private:
	void x_drag();
	void y_gravity();
	void y_update_top();

	// data members
	// probe current position
	int x_pos{ 0 };
	int y_pos{ 0 };
	// probe current speed in two axes
	int x_velocity;
	int y_velocity; // + upward, - downward
	// tracking the top position reached
	int y_top{ 0 };
};

bool in_target_area(const Probe& p, const Target& t); 
bool in_beyond_target_area(const Probe& p, const Target& t); 
int minimum_speed_to_reach(int x_tl);