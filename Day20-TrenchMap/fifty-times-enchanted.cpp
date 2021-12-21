#include <fstream>
#include "Enhance_key.h"
#include "Picture.h"

int main() {
	// parse input
	//std::string filename{ "TestInput1.txt" };
	std::string filename{ "Input.txt" };
	std::ifstream ifs{ filename };

	// read the enhancement key
	Enhance_key key;
	ifs >> key;

	// read the input picture
	Picture pic{};
	ifs >> pic;
	
	// enhance 50 times!
	for (int i = 0; i < 50; i++) {
		pic = enhance(pic, key);
		// output to console
		//std::cout << "Picture enhanced " << i+1 << " times has " << pic.filled_pixels() << " lit pixels." << std::endl;
	}
	

	// output to console
	std::cout << "Picture enhanced fifty times has " << pic.filled_pixels() << " lit pixels.";

	// input 20876 too high
}