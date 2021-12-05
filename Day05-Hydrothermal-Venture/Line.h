#pragma once

#include "Point.h"
#include <vector>

struct Line {
public:
	Line(Point p1, Point p2);
	bool is_horizontal() const;
	bool is_vertical() const;
	bool is_diagonal() const;


	// simple getter
	std::vector<Point> covered_points() const { return covered; }

	// public members
	Point begin;
	Point end;

private:
	std::vector<Point> covered;
};