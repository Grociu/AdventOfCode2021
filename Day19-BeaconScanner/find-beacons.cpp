#include "Beacon.h"
#include "Scanner.h"
#include <fstream>
#include <set>

int main() {
	//std::string filename{ "TestInput1.txt" };
	std::string filename{ "TestInput2.txt" };
	//std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };

	std::vector<Scanner> scanners;

	// read the scanners data from input
	while (ifs) {
		Scanner s;
		ifs >> s;
		if (ifs.eof()) break;
		scanners.push_back(s);
		if (!ifs.eof()) ifs.clear();
	}

	// DEBUG print scanned beacons
	//for (const Scanner& s : scanners) {
	//	std::cout << s.get_id() << " sees " << s.num_beacons() << " beacons" << std::endl;
	//}

	// update pointers to the members of scanners vector
	for (Scanner& s : scanners) for (Beacon& b : s.beacons) b.parent_scanner = &s;

	// Assume Scanner with id=0 is oriented correctly and at coords 0.0;
	scanners[0].set_position(0, 0, 0);
	scanners[0].set_orientation(1, 1, 1);
	scanners[0].set_rotation(is_x, is_y, is_z);
	scanners[0].mark_solved();

	// DEBUG print beacons
	//for (const Scanner& s : scanners) s.print();

	// DEBUG check pointers
	//Scanner* p = &scanners[0];
	//Scanner* p2 = scanners[0].beacons[0].parent_scanner;
	//std::cout << p << " " << p2  << std::endl;

	// Try alignment of s1 with s0
	//scanners[1].attempt_allignment(scanners[0]);
	
	// Track which scanners are solved
	std::set<int> solved_id{ 0 };
	std::set<int> analyzed;
	
	while (solved_id.size() < scanners.size()) {
		for (int id : solved_id) if (analyzed.find(id) == analyzed.end()) {
			for (Scanner& s : scanners) {
				s.attempt_allignment(scanners[id]);
				if (s.solved) solved_id.insert(s.get_id());
			}
			analyzed.insert(id);
			std::cout << "ID: " << id << " fully analyzed." << std::endl;
		}
		for (int id : solved_id) std::cout << id << " " << scanners[id].x() << " " << scanners[id].y() << " " << scanners[id].z() << std::endl;
		std::cout << std::endl;
	}
	
	// count beacons
	std::set<Beacon> all_beacons;
	for (const Scanner& s : scanners) for (const Beacon& b : s.beacons) all_beacons.insert(b);
	
	std::cout << "There are " << all_beacons.size() << " total beacons." << std::endl;
}