#pragma once

struct Point {
	Point(int xx, int yy) : x{xx}, y{yy} {}

	int x;
	int y;

};

// to use in a map a std::less has to be defined
bool operator==(const Point& p1, const Point& p2);

bool operator<(const Point& p1, const Point& p2);