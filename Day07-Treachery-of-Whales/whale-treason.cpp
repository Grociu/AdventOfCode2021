#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

// using variant day06 input parser
void parse_input(std::ifstream& ifs, std::vector<int>& data) {
	char c;
	while (ifs >> c) {
		if (isdigit(c)) {
			ifs.putback(c);
			int num;
			ifs >> num;
			data.push_back(num);
		}
	}
}

int total_fuel_needed(int position, const std::vector<int>& data) {
	int sum{ 0 };
	for (const int& i : data) sum += abs(i - position);
	return sum;
}

int main() {

	// prepare a stream to read input
	std::string filename = "Input.txt";
	std::ifstream ifs{ filename };

	// this will keep track of the initial_distances of crab submarines
	std::vector <int> initial_distances;

	// read input into the school map;
	parse_input(ifs, initial_distances);

	// sort the list of initial_distaances
	sort(initial_distances.begin(), initial_distances.end());

	// assertion - for sorted list - if at any point total_fuel(position n+1) total_fuel(position n), n is the minimum
	// a better way would be to do this at half index first and look 'down' into quarters eights looking for a crossover point
	int current_minimum{ total_fuel_needed(0, initial_distances) };
	for (int i = 1; i < initial_distances.size(); i++) {
		int fuel_this_iteration{ total_fuel_needed(i, initial_distances) };
		if (fuel_this_iteration > current_minimum) break;
		else current_minimum = fuel_this_iteration;
	}

	// output to console
	std::cout << "Minimum fuel required: " << current_minimum << std::endl;
}