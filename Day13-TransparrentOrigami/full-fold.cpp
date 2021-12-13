#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


struct Point {
	Point(int xx, int yy) : x{ xx }, y{ yy } {}
	int x;
	int y;
};

// needed for use with map
bool operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
bool operator<(const Point& a, const Point& b) {
	if (a.x < b.x) return true;
	if (a.x > b.x) return false;
	return a.y < b.y;
}

class Paper {
public:
	Paper(const std::vector<Point>& pts) {
		for (const Point& p : pts) {
			size_x = std::max(size_x, p.x + 1);
			size_y = std::max(size_y, p.y + 1);
			points[p] = true;
		}
	}
	void print_stats() const { std::cout << size_x << " " << size_y << " " << points.size() << std::endl; }

	void fold(std::pair<char, int> instr) {
		// some points will be erased as the size of paper decreases, some points will be added
		std::vector<Point> to_erase;
		std::vector<Point> to_add;
		// iterate over points
		switch (instr.first) {
		case 'x': {
			for (auto& p : points) {
				// folding at x == instr.second, points to the right of the line, get folded
				if (p.first.x > instr.second) {
					to_add.push_back(Point{ p.first.x - 2 * (p.first.x - instr.second), p.first.y });
					to_erase.push_back(p.first);
				}
			}
			size_x = instr.second;
			break;
		}
		case 'y': {
			for (auto& p : points) {
				if (p.first.y > instr.second) {
					to_add.push_back(Point{ p.first.x, p.first.y - 2 * (p.first.y - instr.second) });
					to_erase.push_back(p.first);
				}
			}
			size_y = instr.second;
			break;
		}
		default: {}
		}
		for (Point& p : to_erase) points.erase(p);
		for (Point& p : to_add) points[p] = true;
	}

	// prints the papersheet coordinates
	void output() {
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				try {
					if (points.at(Point{ x, y })) std::cout << '*';
				}
				catch (std::out_of_range) {
					std::cout << ' ';
				}
			}
			std::cout << std::endl;
		}
	}

private:
	int size_x;
	int size_y;
	std::map<Point, bool> points;
};


void read_points(std::istream& is, std::vector<Point>& points) {
	char c;
	while (is >> c) {
		// if a letter is found, exit
		if (isalpha(c)) { is.putback(c); return; }
		if (isdigit(c)) {
			is.putback(c);
			int x, y;
			is >> x;
			is >> c; // reads the comma
			is >> y;
			points.push_back(Point{ x,y });
		}
	}
}

void read_instructions(std::istream& is, std::vector<std::pair<char, int>>& instructions) {
	char c;
	while (is >> c) {
		switch (c) {
		case 'x': case 'y': {
			char axis = c;
			is >> c;
			int val;
			is >> val;
			instructions.push_back({ axis, val });
			break;
		}
		default: {} // skip by default
		}
	}
}


int main() {
	// read input
	const std::string input_filename = "Input.txt";
	//const std::string input_filename = "TestInput.txt";
	std::ifstream ifs{ input_filename };
	std::vector<Point> points;
	std::vector<std::pair<char, int>> instructions;
	read_points(ifs, points);
	read_instructions(ifs, instructions);

	// construct a sheet of paper
	Paper paper{ points };
	// fold
	for (const auto& ins : instructions) paper.fold(ins);
	// output
	paper.print_stats();
	paper.output();
}