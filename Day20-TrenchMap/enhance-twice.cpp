#include <fstream>
#include "Enhance_key.h"
#include "Picture.h"

int main() {
	// parse input
	//std::string filename{ "TestInput1.txt" };
	std::string filename{ "Input.txt" };
	std::ifstream ifs { filename };
	
	// read the enhancement key
	Enhance_key key;
	ifs >> key;

	// read the input picture
	Picture pic0{};
	ifs >> pic0;
	//pic0.draw();
	//std::cout << pic0.rows() << " " << pic0.columns() << std::endl;
	
	// enhance!
	Picture pic1 = enhance(pic0, key);
	//pic1.draw();
	//std::cout << pic1.rows() << " " << pic1.columns() << std::endl;

	Picture pic2 = enhance(pic1, key);
	//pic2.draw();
	//std::cout << pic2.rows() << " " << pic2.columns() << std::endl;
	

	// output to console
	std::cout << "Picture enhanced twice has " << pic2.filled_pixels() << " lit pixels.";
}