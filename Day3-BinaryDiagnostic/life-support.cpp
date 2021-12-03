#include <iostream>
#include <fstream>
#include <vector>
#include <string>


// this function will count the number of digits d at position n
int count_readings(const std::vector<std::string>& v, const char digit, const int position) {
	int count{ 0 };
	for (std::string x : v) if (x[position] == digit) count++;
	return count;
}

// this function will prune readings if a digit d is found at position n
void prune_readings(std::vector<std::string>& v, const char digit, const int position) {
	std::vector<std::string> temp;
	for (std::string x : v) if (x[position] != digit) temp.push_back(x);
	v = temp;
}


int main() {
	// Construct a vector of all readings
	std::string filename = "Input.txt";
	std::ifstream ifs{ filename };
	std::vector<std::string> readings;
	std::string r;
	while (ifs >> r) readings.push_back(r);

	const int length_of_reading = readings[0].length();

	// read oxygen
	std::vector<std::string> oxy = readings;
	for (int i = 0; i < length_of_reading; i++) {
		if (oxy.size() == 1) break;
		if ( count_readings(oxy, '1', i) >= oxy.size() / 2.0 ) prune_readings(oxy, '0', i);
		else prune_readings(oxy, '1', i);
	}
	// convert from binary-string to int
	int oxy_reading = std::stoi(oxy[0], 0, 2);
	
	// read co2
	std::vector<std::string> co2 = readings;
	for (int i = 0; i < length_of_reading; i++) {
		if (co2.size() == 1) break;
		if (count_readings(co2, '0', i) <= co2.size() / 2.0) prune_readings(co2, '1', i);
		else prune_readings(co2, '0', i);
	}
	int co2_reading = std::stoi(co2[0], 0, 2);

	// output to console	
	std::cout << "Final reading: Oxygen [" << oxy_reading << "] CO2 [" << co2_reading << "]. Product {" << oxy_reading * co2_reading << "}.\n";
}