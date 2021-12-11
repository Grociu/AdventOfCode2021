#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class Octopus {
public:
	Octopus(int e_lv) : energy_level{ e_lv } {}

	void raise_energy() {
		if (energy_level != 10) energy_level++;
	}

	void flash() {
		if (!flashed_this_step) {
			flashed_this_step = true;
			total_flashes++;
		}
	}

	void reset_energy_level() {
		energy_level = 0;
		flashed_this_step = false;
	}

	static int total_flashes;
	int energy_level;
	bool flashed_this_step{ false };
};

void flash(int r_x, int c_x, Matrix<Octopus>& oct) {
	oct.get_data(r_x, c_x).flash(); // octopus at coordinates flashes
	for (std::pair<int, int> coords : oct.get_adjacent_coords(r_x, c_x, true)) {
		Octopus& o = oct.get_data(coords.first, coords.second);
		o.raise_energy();
		if (o.energy_level == 10 && !o.flashed_this_step) flash(coords.first, coords.second, oct);
	}
}

void execute_step(Matrix<Octopus>& oct) {
	// raise energy of all octopi
	for (int r = 0; r < oct.num_rows(); r++) {
		for (int c = 0; c < oct.num_columns(); c++) {
			oct.get_data(r, c).raise_energy();
		}
	}
	// flash octopi with 9 energy
	for (int r = 0; r < oct.num_rows(); r++) {
		for (int c = 0; c < oct.num_columns(); c++) {
			Octopus& o = oct.get_data(r, c);
			if (o.energy_level == 10 && !o.flashed_this_step) flash(r, c, oct);
		}
	}
	// reset flashed octopus
	for (int r = 0; r < oct.num_rows(); r++) {
		for (int c = 0; c < oct.num_columns(); c++) {
			Octopus& o = oct.get_data(r, c);
			if (o.flashed_this_step) o.reset_energy_level();
		}
	}
}

void print(Matrix<Octopus>& oct) {
	for (int r = 0; r < oct.num_rows(); r++) {
		for (int c = 0; c < oct.num_columns(); c++) {
			std::cout << oct.get_data(r, c).energy_level;
		}
		std::cout << std::endl;
	}
}

// read input for single digit entries not separated by sepatrators
void parse_input(std::ifstream& ifs, Matrix<Octopus>& data) {
	std::string line;
	//for each line
	while (std::getline(ifs, line)) {
		std::vector<Octopus> octs;
		std::istringstream iss(line);
		char c;
		while (iss >> c) {
			int i = c - '0'; //converts digit to int
			octs.push_back(Octopus(i));
		}
		data.add_row(octs);
	}
}

bool is_synchronized(Matrix<Octopus> &data) {
	for (int r = 0; r < data.num_rows(); r++) {
		for (int c = 0; c < data.num_columns(); c++) {
			Octopus& o = data.get_data(r, c);
			if (o.energy_level != 0) return false;
		}
	}
	return true;
}

// static member of Octopi class initialization;
int Octopus::total_flashes{ 0 };

int main() {

	const std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };

	Matrix<Octopus> octopi{ 0, 0 };
	parse_input(ifs, octopi);

	int steps_taken = 0;
	
	while (!is_synchronized(octopi)) {
		execute_step(octopi);
		steps_taken++;
	}

	std::cout << "Steps to synchronize: " << steps_taken << std::endl;
}