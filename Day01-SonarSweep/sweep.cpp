#include <iostream>
#include <fstream>

int main() {
	std::string filename = "Input.txt";
	std::ifstream f(filename);
	
	int counter{0};

	int previous_reading;
	f >> previous_reading;
	
	int new_reading;
	while (f >> new_reading) {
		if (new_reading > previous_reading) counter++;
		previous_reading = new_reading;
	}

	std::cout << "Increased readings : " << counter << "." << std::endl;
}
