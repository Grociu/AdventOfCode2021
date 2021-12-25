#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Cuboid.h"
#include "Plane.h"


struct Instructions {
	std::vector<Cuboid> initialization;
	std::vector<Cuboid> main_procedure;
};

std::istream& operator>>(std::istream& is, Instructions& data) {
	std::string line;
	while (std::getline(is, line)) {
		std::istringstream iss{ line };
		std::vector<int> nums;
		bool lit;
		bool init{ true };

		// read on/off
		char c1, c2;
		iss >> c1 >> c2;
		switch (c2) {
		case 'n': lit = true; break;
		case 'f': lit = false; break;
		default: return is; // error
		}

		// read digits
		while (iss >> c1) {
			if (isdigit(c1) || c1 == '-') {
				iss.putback(c1);
				int n;
				iss >> n;
				nums.push_back(n);
			}
		}

		// assemble a Cuboid from data
		Cuboid c{
			Point{std::min(nums[0], nums[1]), std::min(nums[2], nums[3]), std::min(nums[4], nums[5])},
			Point{std::max(nums[0], nums[1]), std::max(nums[2], nums[3]), std::max(nums[4], nums[5])},
			lit
		};

		// switch from initialization to main_sequence if needed
		if (init && abs(nums[0]) > 50) init = false;

		// record  Cuboid
		if (init) data.initialization.push_back(c);
		else data.main_procedure.push_back(c);

	}
	return is;
}

int main() {

	// read input

	//const std::string filename{ "TestInput1.txt" }; // Example with just 4 initializing instructions // should be 39 lits
	//const std::string filename{ "TestInput2.txt" }; // Example in the text marked with 'largest example' // should be 590784 lits
	//const std::string filename{ "TestInput3.txt" }; // Example for full input // should be 2758514936282235 lits
	const std::string filename{ "PuzzleInput.txt" }; // Puzzle input!

	std::ifstream ifs{ filename };
	Instructions instr;
	ifs >> instr;

	// set up the initial lit cuboids 
	std::vector<Cuboid> lit_cuboids;
	lit_cuboids.push_back(instr.initialization[0]);

	// run initialization
	for (unsigned int i = 1; i < instr.initialization.size(); i++) {
		std::vector<Cuboid> operands = lit_cuboids;
		lit_cuboids.clear();
		for (const Cuboid& c : operands) {
			std::vector<Cuboid> remnants = subtract(c, instr.initialization[i]);
			lit_cuboids.insert(lit_cuboids.end(), remnants.begin(), remnants.end());
		}
		if (instr.initialization[i].lit()) lit_cuboids.push_back(instr.initialization[i]);
	}

	// find number of lit pixels
	long long lit_pixels{ 0 };
	for (const Cuboid& c : lit_cuboids) lit_pixels += c.lit_pixels();

	std::cout << "Initialization - Lit pixels: " << lit_pixels << std::endl;

	// run main_sequence
	for (unsigned int i = 0; i < instr.main_procedure.size(); i++) {
		std::vector<Cuboid> operands = lit_cuboids;
		lit_cuboids.clear();
		for (const Cuboid& c : operands) {
			std::vector<Cuboid> remnants = subtract(c, instr.main_procedure[i]);
			lit_cuboids.insert(lit_cuboids.end(), remnants.begin(), remnants.end());
		}
		if (instr.main_procedure[i].lit()) lit_cuboids.push_back(instr.main_procedure[i]);
	}

	// find number of lit pixels
	lit_pixels = 0;
	for (const Cuboid& c : lit_cuboids) lit_pixels += c.lit_pixels();

	std::cout << "Full sequence - Lit pixels: " << lit_pixels << std::endl;

}