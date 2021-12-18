#include <fstream>
#include <vector>
#include "Probe.h"
#include <iostream>

Target get_target_from_input(const std::string& filename) {
	std::ifstream ifs{ filename };
	char c;
	std::vector<int> nums;
	while (ifs >> c) {
		if (isdigit(c) || c == '-') {
			ifs.putback(c);
			int n;
			ifs >> n;
			nums.push_back(n);
		}
	}
	return Target{ nums[0], nums[1], nums[2], nums[3] };
}

int main() {
	const std::string filename{ "Input.txt" };
	Target t = get_target_from_input(filename);
	int max_y{ 0 };
	for (int x = minimum_speed_to_reach(t.left()); x <= t.right(); x++) {
		for (int y = t.bottom(); y < -t.bottom(); y++) {
			Probe p(x, y);
			while (!in_beyond_target_area(p, t)) {
				p.step();
				if (in_target_area(p, t)) {
					max_y = std::max(max_y, p.top());
					break;
				}
			}
		}
	}
	std::cout << "Reached a max of: " << max_y;
}