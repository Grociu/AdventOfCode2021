#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Line.h"


void read_lines(std::ifstream& ifs, std::vector<Line>& lines) {
	std::string file_line;
	while (std::getline(ifs, file_line)) {

		std::stringstream iss{ file_line };
		std::vector<int> nums;
		char c;

		// read the line, ignore nondigit characters, use digit charaatres to construct integers
		while (iss >> c) {
			if (isdigit(c)) {
				iss.putback(c);
				int n;
				iss >> n;
				nums.push_back(n);
			}
		}
		// construct a Line object from nums
		lines.push_back({ Point{ nums[0], nums[1] }, Point{ nums[2], nums[3] } });
	}
}

int main() {
	std::string filename = "Input.txt";
	std::ifstream ifs{ filename };

	// read lines from input
	std::vector<Line> lines;
	read_lines(ifs, lines);

	// map points that are covered and a number of lines covering them (horizontal and vertical only)
	std::map<Point, int> cover;

	for (Line& l : lines) {
		if (l.is_horizontal() || l.is_vertical()) {
			for (Point& p : l.covered_points()) {
				if (cover.count(p)) cover[p]++;
				else cover[p] = 1;
			}
		}
	}

	// count overlaps (>=2 in cover map)
	int num_overlapped_points{ 0 };
	for (auto const& x : cover) {
		if (x.second > 1) num_overlapped_points++;
	}
	
	// output to console
	std::cout << "Overlapped points: " << num_overlapped_points << std::endl;
}