#include "Line.h"

Line::Line(Point p1, Point p2) : begin{ p1 }, end{ p2 } {
	// NOTE: points can be 'out of order' - for example right to left, or left to right
	if (is_horizontal()) {
		for (int i = std::min(begin.x, end.x); i <= std::max(begin.x, end.x); i++) covered.push_back(Point{ i, begin.y });
	}
	else if (is_vertical()) {
		for (int i = std::min(begin.y, end.y); i <= std::max(begin.y, end.y); i++) covered.push_back(Point{ begin.x, i });
	}
	// diagonal line - per instruction, always at 45deg - sequential indexes
	// there are two variants, a line diagonally down to the right, and diagonally down to left
	
	// variant 1 right
	else if ((begin.x > end.x && begin.y > end.y) || (begin.x < end.x && begin.y < end.y)) {
		const int number_of_points = std::max(begin.x, end.x) - std::min(begin.x, end.x) + 1;
		for (int i = 0; i < number_of_points; i++) {
			covered.push_back(Point{ std::min(begin.x, end.x) + i, std::min(begin.y, end.y) + i}); // increment between x and y axis is the same
		}
	}
	// variant 2 left
	else {
		const int number_of_points = std::max(begin.x, end.x) - std::min(begin.x, end.x) + 1;
		for (int i = 0; i < number_of_points; i++) {
			covered.push_back(Point{ std::min(begin.x, end.x) + i, std::max(begin.y, end.y) - i }); // increment between x and y axis is the same, but in the other direction
		}
	}
}

bool Line::is_horizontal() const { return begin.y == end.y; }

bool Line::is_vertical() const { return begin.x == end.x;  }

bool Line::is_diagonal() const { return !(is_horizontal() || is_vertical()); }