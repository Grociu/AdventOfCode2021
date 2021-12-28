#include <iostream>
#include <vector>

#include "Alu.h"
#include "Monad.h"


int main() {
	
	Alu alu;
	Monad monad;

	const std::string filename = "Input.txt";
	Program program;

	read_program_from_file(filename, program);

	while (true) {
		//while (monad.has_zero()) { monad.decrement(); }
		alu.execute_program(program, monad.digits());
		if (alu.z == 0) break;
		monad.decrement(); // will result in a number without zero
	}

	std::cout << "Alu: w(" << alu.w << ") x(" << alu.x << ") y(" << alu.y << ") z(" << alu.z << ")" << std::endl;
	std::cout << monad.num();
}