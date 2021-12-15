#include "Matrix.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>


// node of the cave system/graph
struct Node {
	Node(int n) : move_risk(n) {};
	int move_risk;
	int total_move_risk{ INT_MAX };
	bool visited{ false };
	bool is_target{ false };
	std::vector<std::pair<int, int>> adjacent_node_coords;
};

// reusing input parser from Day11
// read input for single digit entries not separated by sepatrators
void parse_input(std::ifstream& ifs, Matrix<Node>& data) {
	std::string line;
	//for each line
	while (std::getline(ifs, line)) {
		std::vector<Node> nodes;
		std::istringstream iss(line);
		char c;
		while (iss >> c) {
			int i = c - '0'; //converts digit to int
			nodes.push_back(Node(i));
		}
		data.add_row(nodes);
	}
}


void calculate_total_path_risk(const std::pair<int, int>& start, const std::pair<int, int>& end, Matrix<Node>& nodes) {
	// setup the algorithm
	Node* current = &nodes.get_data(start.first, start.second);
	current->total_move_risk = 0;
	current->visited = true;
	nodes.get_data(end.first, end.second).is_target = true;
	// get adjecancy lists to the nodes
	for (int r = 0; r < nodes.num_rows(); r++) {
		for (int c = 0; c < nodes.num_columns(); c++) {
			nodes.get_data(r, c).adjacent_node_coords = nodes.get_adjacent_coords(r, c, false);
		}
	}
	std::map<std::pair<int, int>, int> visit_candidates;
	// repeat until we arrive at target nodes
	while (!current->is_target) {
		// for each neighbor of current
		for (auto& pair : current->adjacent_node_coords) {
			Node* next = &nodes.get_data(pair.first, pair.second);
			// if not yet visited, update total risk to minimum of saved risk and risk of move from current to next
			if (!next->visited) {
				next->total_move_risk = std::min(next->total_move_risk, current->total_move_risk + next->move_risk);
				// track this node in the visit candidates map
				try { visit_candidates.at(pair) = next->total_move_risk; }
				catch (std::out_of_range) { visit_candidates[pair] = next->total_move_risk; }
			}
		}
		// all the total-risks are updated for adjacent nodes of current, find the node with lowest total_risk and move to it
		std::pair<int,int> min_risk_node = std::min_element(visit_candidates.begin(), visit_candidates.end(),
			[](const auto& l, const auto& r) { return l.second < r.second; })->first;
		current = &nodes.get_data(min_risk_node.first, min_risk_node.second);
		current->visited = true;
		visit_candidates.erase(min_risk_node);
	}
}


int main() {
	// READ INPUT
	const std::string input_filename = "Input.txt";
	//const std::string input_filename = "TestInput.txt";
	std::ifstream ifs{ input_filename };
	Matrix<Node> nodes{ 0,0 };
	parse_input(ifs, nodes);

	const std::pair<int, int> START_POINT{ 0, 0 };
	const std::pair<int, int> END_POINT{ nodes.num_rows() -1, nodes.num_columns() -1 };


	calculate_total_path_risk(START_POINT, END_POINT, nodes);
	int total_risk = nodes.get_data(END_POINT.first, END_POINT.second).total_move_risk;
	std::cout << "Total risk to get to bottom right is: " << total_risk << std::endl;
}