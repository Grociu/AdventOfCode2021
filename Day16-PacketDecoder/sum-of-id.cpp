#include <fstream>
#include <sstream>
#include <iostream>
#include <bitset>
#include "Packet.h"


// reads contents of file filename to string input_string
void read_input_file(const std::string& filename, std::string& input_string) {
	std::ifstream ifs{ filename };
	ifs >> input_string;
}

int main() {
	
	// read input
	const std::string filename{ "TestInput11.txt" };
	std::string input;
	read_input_file(filename, input);
	//std::cout << input;

	// decode into packets
	std::vector<Packet> packets;
	decode_packets(input, packets);
}