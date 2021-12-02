#include <iostream>
#include <fstream>

struct Position {
	Position(int ds, int dp) : distance{ ds }, depth{ dp } {}
	
	void up(int n) { depth -= n; }
	void down(int n) { depth += n; }
	void forward(int n) { distance += n; }
	
	int distance;
	int depth;
};


int main() {
	std::string filename = "Input.txt";
	Position p{ 0, 0 };
	std::ifstream ifs{ filename };

	std::string instruction;
	int value;

	// read input
	while (ifs >> instruction >> value) {
		switch (instruction[0]) { // first letter of instruction
		case 'u': p.up(value); break;
		case 'd': p.down(value); break;
		case 'f': p.forward(value); break;
		default: throw std::runtime_error("Unrecognized input: " + instruction);
		}
	}

	// output to console	
	std::cout << "Final position: distance[" << p.distance << "] depth [" << p.depth << "]. Product {" << p.distance * p.depth << "}.\n";
}