#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::string filename = "Input.txt";
	std::ifstream ifs{ filename };

	std::string reading;
	// vector to store the sum of ones in all the readings
	std::vector<int> ones;
	// int to track the number of total readings
	int num_read{ 0 };

	// read the readings and compile the vector of ones in each position
	while (ifs >> reading) {
		// this will 'read' the length of the reading and adjust the vector accordingly
		while (ones.size() < reading.length()) ones.push_back(0);
		for (int i = 0; i < ones.size(); i++) {
			switch (reading[i]) {
			case '1': ones[i]++; break;
			case '0': break;
			default: break;
			}
		}
		num_read++;
	}

	// construct gamma - 1 if ones[i] > num_read/2
	int gamma{ 0 };
	for (int i = 0; i < ones.size(); i++) {
		if (ones[i] > num_read / 2) gamma += int(pow(2, ones.size() - i - 1));
	}
	// epsilon will be max binary minus gamma
	int epsilon{ (int(pow(2, ones.size()))) - 1 - gamma };

	// output to console	
	std::cout << "Final reading: gamma [" << gamma << "] epsilon [" << epsilon << "]. Product {" << gamma*epsilon << "}.\n";
}