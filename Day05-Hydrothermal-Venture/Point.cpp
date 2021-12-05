#include "Point.h"


// to use in a map a std::less has to be defined
bool operator==(Point& p1, Point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

bool operator<(const Point& p1, const Point& p2) {
	if (p1.x < p2.x) return true;
	if (p1.x > p2.x) return false;
	return p1.y < p2.y;
}