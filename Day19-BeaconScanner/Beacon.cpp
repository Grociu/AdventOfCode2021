#include "Beacon.h"
#include "Scanner.h"

// Constructor
Beacon::Beacon(Scanner& s, int x, int y, int z)
	: parent_scanner{ &s }, relative_x {x}, relative_y{ y }, relative_z{ z },
	temp_x{ x }, temp_y{ y }, temp_z{ z } {}

int Beacon::x() const { return solved ? real_x : temp_x; }
int Beacon::y() const { return solved ? real_y : temp_y; }
int Beacon::z() const { return solved ? real_z : temp_z; }


void Beacon::update_temp() {
	// without rotation
	//temp_x = parent_scanner->x() +parent_scanner->xo() * relative_x;
	//temp_y = parent_scanner->y() +parent_scanner->yo() * relative_y;
	//temp_z = parent_scanner->z() +parent_scanner->zo() * relative_z;
	// with rotation
	temp_x = parent_scanner->x();
	temp_y = parent_scanner->y();
	temp_z = parent_scanner->z();
	switch (parent_scanner->x_r) {
	case is_x: temp_x += parent_scanner->xo() * relative_x; break;
	case is_y: temp_y += parent_scanner->xo() * relative_x; break;
	case is_z: temp_z += parent_scanner->xo() * relative_x; break;
	default: {}
	}
	switch (parent_scanner->y_r) {
	case is_x: temp_x += parent_scanner->yo() * relative_y; break;
	case is_y: temp_y += parent_scanner->yo() * relative_y; break;
	case is_z: temp_z += parent_scanner->yo() * relative_y; break;
	default: {}
	}
	switch (parent_scanner->z_r) {
	case is_x: temp_x += parent_scanner->zo() * relative_z; break;
	case is_y: temp_y += parent_scanner->zo() * relative_z; break;
	case is_z: temp_z += parent_scanner->zo() * relative_z; break;
	default: {}
	}
}

void Beacon::solve() {
	if (solved) return;
	//update_temp();
	real_x = temp_x;
	real_y = temp_y;
	real_z = temp_z;
	solved = true;
}

std::istream& operator>>(std::istream& is, Beacon& b) {
	int x, y, z;
	char c1, c2;
	is >> x;
	if (!is) { 
		is.unget(); 
		return is; 
	}
	is >> c1 >> y >> c2 >> z;
	if (c1 != ',' || c2 != ',') { is.setstate(std::ios::failbit); return is; }
	b.relative_x = x;
	b.temp_x = x;
	b.relative_y = y;
	b.temp_y = y;
	b.relative_z = z;
	b.temp_z = z;
	return is;
}

bool operator==(const Beacon& b1, const Beacon& b2) {
	return (b1.x() == b2.x() && b1.y() == b2.y() && b1.z() == b2.z());
}

bool operator<(const Beacon& b1, const Beacon& b2) {
	if (b1.x() < b2.x()) return true;
	if (b1.x() > b2.x()) return false;
	if (b1.y() < b2.y()) return true;
	if (b1.y() > b2.y()) return false;
	return b1.z() < b2.z();
}

void Beacon::print() const {
	std::cout << x() << " " << y() << " " << z() << std::endl;
}