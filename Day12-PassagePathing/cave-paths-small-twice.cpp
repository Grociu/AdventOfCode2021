#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "Path.h"
#include <stack>

#include <chrono>


// INPUT PARSING

std::istream& operator>>(std::istream& is, Edge<std::string>& e) {
	std::string entry;
	const std::string delimiter{ "-" };
	is >> entry;
	e.source = entry.substr(0, entry.find(delimiter));
	e.destination = entry.substr(entry.find(delimiter) + delimiter.length(), entry.length());
	//std::cout << "Parsed (" << e.source << " >>>>>>> " << e.destination << ")" << std::endl;
	return is;
}

void read_edges_from_input(std::ifstream& ifs, std::vector<Edge<std::string>>& data) {

	std::string line;
	while (std::getline(ifs, line)) {

		std::istringstream iss{ line };
		Edge<std::string> e;
		iss >> e;
		data.push_back(e);
	}
}

int find_num_paths(const std::string& start, const std::string& end, Graph<std::string>& data) {
	// this only keeps track of the number if finished paths
	std::stack<Path> open_paths;
	int num_routes{ 0 };
	open_paths.push(Path{ start });

	while (open_paths.size() > 0) {
		// work on last path
		const Path p = open_paths.top();
		//p.print();
		open_paths.pop();
		// get adjacent caves
		for (const std::string& node : data.get_adjecent(p.current())) {

			// if it's the endpoint, move to it and save
			if (node == end) {
				num_routes++;
				continue; }

			// otherwise get type of cave
			// illegal path if small and already visited - discard
			if (!p.can_visit(node)) continue;
			// else, move in
			open_paths.push(Path{ p, node });
		}
	}
	return num_routes;
}


// EXECUTION

int main() {
	// measure execution time
	const auto start = std::chrono::high_resolution_clock::now();
	// read input
	const std::string input_filename = "Input.txt";
	//const std::string input_filename = "TestInput3.txt";
	std::ifstream ifs{ input_filename };
	std::vector<Edge<std::string>> connections;
	read_edges_from_input(ifs, connections);

	// construct an undirected graph from connections
	Graph<std::string> cave_system{ connections };

	// find all the paths throught the cave system
	const std::string start_cave = "start";
	const std::string end_cave = "end";
	const int num_paths = find_num_paths(start_cave, end_cave, cave_system);
	const auto end = std::chrono::high_resolution_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	// output to console
	std::cout << "There are " << num_paths << " paths through the cave system." << std::endl;
	std::cout << "Execution took " << duration.count() << "mus.";
}

// attempts to optimize
/*
Baseline:
54883252 mus - 54.88s
Switch open_paths to stack:
54128783 mus. - 54.13s , no improvement
Move Path declaration and definition outside the main file:
58389897mus - 58.39s, cleaner cone, but longer execution
Add qualifiers to member functions that limit memory use:
48758194mus - 48.76s, progress - this limited the creation of copied strings for some functions
Add further qualifiers and const to external class definitions and initializations
46445795mus - 46.45s minimal progress
Final qualifiers
45169402mus - 45.17s
Refactor get_afj_lst_index to use a map
44846316mus - 44.85s - wasteful
*/
