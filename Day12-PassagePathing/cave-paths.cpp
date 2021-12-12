#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "Path.h"



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

// PATHFINDING
struct Path {
	// constructors
	Path(const std::string start) {route.push_back(start);}
	Path(const Path& p, const std::string new_way) { route = p.route; route.push_back(new_way); };
	// was the node already visited on this path?
	bool already_visited(std::string node) {return std::find(route.begin(), route.end(), node) != route.end();}
	// DEBUG
	void print() {
		std::cout << "Path Route: ";
		for (auto& s : route) std::cout << s << " > ";
		std::cout << std::endl;
	}
	// data members
	std::vector<std::string> route;
};

std::vector<Path> find_paths(const std::string start, const std::string end, Graph<std::string>& data) {
	std::vector<Path> open_paths;
	std::vector<Path> finished_paths;
	open_paths.push_back(Path{ start });

	while (open_paths.size() > 0) {
		// work on last path
		Path p = open_paths.back();
		//p.print();
		open_paths.pop_back();
		// get adjacent caves
		for (auto node : data.get_adjecent(p.route.back())) {

			// if it's the endpoint, move to it and save
			if (node == end) { finished_paths.push_back(Path{ p, node }); continue; }

			// otherwise get type of cave
			// illegal path if small and already visited - discard
			if (ctype(node) == small && p.already_visited(node)) continue;
			// else, move in
			open_paths.push_back(Path{ p, node });
		}
	}
	return finished_paths;
}


// EXECUTION

int main() {
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
	std::vector<Path> paths = find_paths(start_cave, end_cave, cave_system);

	// output to console
	std::cout << "There are " << paths.size() << " paths through the cave system.";

}
