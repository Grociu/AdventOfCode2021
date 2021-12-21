#include "Beacon.h"
#include "Scanner.h"
#include <string>
#include <sstream>

// calculates real positions of the scanned beacons based on the position of the scanner
void Scanner::mark_solved() {
	for (Beacon& b : beacons) b.solve();
	solved = true;
}

std::istream& operator>>(std::istream& is, Scanner& s) {
	std::string header;
	std::getline(is, header);
	std::istringstream iss { header };
	char c;
	while (iss >> c) {
		if (isdigit(c)) {
			iss.putback(c);
			// read id
			int i;
			iss >> i;
			s.set_id(i);
			break;
		}
	}

	// read sensed beacons
	while (is) {
		Beacon b{ s, 0, 0, 0 };
		is >> b;
		if (!is) return is;
		s.add_beacon(b);
	}
	return is;
}

// alingment calculations

// possible orientation of arguments
enum Orient { up = 1, down = -1 };
// all possible combitation for a triple
std::vector<std::vector<Orient>> all_orientations{
	{up, up, up}, {up, up, down}, {up, down, up}, {up, down, down},
	{down, up, up}, {down, down, up}, {down, up, down}, {down, down, down}
};



std::vector<std::vector<Rotation>> all_rotations{
	{is_x, is_y, is_z}, {is_x, is_z, is_y}, {is_y, is_x, is_z},
	{is_y, is_z, is_x}, {is_z, is_x, is_y}, {is_z, is_y, is_x}
};


// assumes the scanner s is properly alligned and tries to find a proper alignmnent of self in relation to s
void Scanner::attempt_allignment(Scanner& s) {
	// do not do these calculations if already solved or s is not solved
	if (solved || !s.solved) return;
	
	// for each point in the correctly coordinated points
	for (Beacon& correct_b : s.beacons) {

		// for each beacon in current scanner
		for (Beacon& candidate_b : beacons) {
			
			// HERE WE ARE ASSUMING THAT THEY ARE THE SAME POINT!
			// trying to find the 'correct' orientation of the scanner
			for (std::vector<Orient>& o : all_orientations) {
				// trying to find the correct rotation of the scanner
				for (std::vector<Rotation>& r : all_rotations) {
					// with the two beacon positions and orientation, set the scanner position and orientation to the candidates
					set_orientation(o[0], o[1], o[2]);
					set_rotation(r[0], r[1], r[2]);
					// apply rotation and orientation, to find the beaccon position
					int p_x{ correct_b.x() };
					int p_y{ correct_b.y() };
					int p_z{ correct_b.z() };
					switch (x_r) {
					case is_x: p_x -= o[0] * candidate_b.relative_x; break;
					case is_y: p_y -= o[0] * candidate_b.relative_x; break;
					case is_z: p_z -= o[0] * candidate_b.relative_x; break;
					default: {}
					}
					switch (y_r) {
					case is_x: p_x -= o[1] * candidate_b.relative_y; break;
					case is_y: p_y -= o[1] * candidate_b.relative_y; break;
					case is_z: p_z -= o[1] * candidate_b.relative_y; break;
					default: {}
					}
					switch (z_r) {
					case is_x: p_x -= o[2] * candidate_b.relative_z; break;
					case is_y: p_y -= o[2] * candidate_b.relative_z; break;
					case is_z: p_z -= o[2] * candidate_b.relative_z; break;
					default: {}
					}
					set_position(p_x, p_y, p_z);
					// orient the beacons with the new position and orientation of the scanner
					for (Beacon& beac : beacons) beac.update_temp();
					//std::cout << "Scanner position " << x() << " " << y() << " " << z() << std::endl;
					//if (x() == 68 && y() == -1246 && z() == -43) {
					//	print();
					//	s.print();
					//}
					// now, count all the beacons that have the same temp_pos as the original beacons
					// if count is >= 12, the position and orientation is correct!
					int count{ 0 };
					for (const Beacon& beac : beacons) {
						for (const Beacon& c_b : s.beacons) {
							//if (c_b.x() == -618 && c_b.y() == -824 && c_b.z() == -621) beac.print();
							if (beac == c_b) count++;
						}
					}
					//std::cout << "Count: " << count << std::endl;
					if (count >= 12) {
						std::cout << "Match found!" << std::endl;
						mark_solved();
						return;
					}
				}
			}
		}
	}
	std::cout << "No match!" << std::endl;
	return;
}

void Scanner::print() const {
	std::cout << "Beacons:" << std::endl;
	for (const Beacon& b : beacons) b.print();
}