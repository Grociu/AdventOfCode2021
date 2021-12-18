#include "Probe.h"



// coordinates in input are x small, x, large, y, small, y large
// but target area is xsmall y large -> x large y- small (underwater)
Target::Target(int x1, int x2, int y1, int y2) : x_tl{ x1 }, y_tl{ y2 }, x_br{ x2 }, y_br{ y1 } {}
	
bool Target::is_in(int x, int y) const { return x >= x_tl && x <= x_br && y <= y_tl && y >= y_br; }
	
void Probe::step() {
		x_pos += x_velocity;
		y_pos += y_velocity;
		y_update_top();
		x_drag();
		y_gravity();
	}

void Probe::x_drag() {
		if (x_velocity > 0) x_velocity--;
		else if (x_velocity < 0) x_velocity++;
	}

void Probe::y_gravity() { y_velocity--; }

// vertical speed is decreasing with each step, so as long as it's > 0 each step will be the highest  
void Probe::y_update_top() { if (y_velocity > 0) y_top = y_pos; }

bool in_target_area(const Probe& p, const Target& t) {
	return t.is_in(p.x(), p.y());
}

// probe will have reached beyond the target area if it's x position is beyond the right side of it or it's below the target
bool in_beyond_target_area(const Probe& p, const Target& t) {
	return p.x() > t.right() || p.y() < t.bottom();
}

// the slowest to reach x_tl of a target from 0,0 will be the arithmetic series n + (n-1) + ... + 1 = x_tl
// any slower (n-1) and the sum will be lower than x_tl
// from sum of ariithmethic series and quadratic
int minimum_speed_to_reach(int x_tl) {
	return int(std::ceil((std::sqrt(1.0 + 8.0 * x_tl)- 1.0) / 2.0));
}