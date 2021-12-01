#include <iostream>
#include <fstream>

int main() {
	std::string filename = "Input.txt";
	std::ifstream if_front(filename);
	std::ifstream if_back(filename);

	int counter{0};

	// construct first triplet of readings
	int previous_sum{0};
	int new_reading;

	for (int i = 0; i < 3; i++) {	
		if_front >> new_reading;
		previous_sum += new_reading;
	}

	//construct second triplet of readings
	int running_sum{ previous_sum };

	while (if_front >> new_reading) {
		//DEBUG: std::cout << new_reading << "/n";
		// new number was read - add it to running sum
		running_sum += new_reading;
		// read the number from the back and subtract it from running sum
		if_back >> new_reading;
		
		running_sum -= new_reading;
		// compare the readings and update before next iteration
		if (running_sum > previous_sum) counter++;
		previous_sum = running_sum;
	}

	std::cout << "Increased readings : " << counter << "." << std::endl;
}
