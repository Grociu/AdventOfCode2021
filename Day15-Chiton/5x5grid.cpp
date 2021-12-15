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
	Node() : Node{ -1 } {};

	int move_risk;
	int total_move_risk{ INT_MAX };
	bool visited{ false };
	bool is_target{ false };
	//std::vector<std::pair<int, int>> adjacent_node_coords;
	std::pair<int, int> coords{ -1, -1 };
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

// wrap digit n, if it's 9 or less stays the same, if it's 10+ it's divided by 10 and added 1
// the progresion should be 7 8 9 1 2 3
int wrap_digit(int n) {
	return n < 10 ? n : n % 10 + 1;
}

Matrix<Node> extend_matrix(Matrix<Node>& orig, int extend_right, int extend_down) {
	
	Matrix<Node> result{orig.num_rows() * extend_right, orig.num_columns() * extend_down};
	// set values for each Node in the result matrix
	for (int r = 0; r < orig.num_rows(); r++) {
		for (int c = 0; c < orig.num_columns(); c++) {
			for (int r_ex = 0; r_ex < extend_right; r_ex++) {
				for (int c_ex = 0; c_ex < extend_down; c_ex++) {
					Node n{ wrap_digit(orig.get_data(r, c).move_risk + r_ex + c_ex) };
					n.coords = { r + r_ex * orig.num_rows(), c + c_ex * orig.num_columns() };
					result.set_data(n, n.coords.first, n.coords.second);
				}
			}
		}
	}
	return result;
}


void calculate_total_path_risk(const std::pair<int, int>& start, const std::pair<int, int>& end, Matrix<Node>& nodes) {
	// setup the algorithm
	Node* current = &nodes.get_data(start.first, start.second);
	current->total_move_risk = 0;
	current->visited = true;
	nodes.get_data(end.first, end.second).is_target = true;

	// unvisited nodes 'one away' with their risk_level calculated
	std::map<std::pair<int, int>, int> visit_candidates;

	// repeat until we arrive at target nodes
	while (!current->is_target) {
		// for each neighbor of current
		for (auto& pair : nodes.get_adjacent_coords(current->coords.first, current->coords.second)) {
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
		std::pair<int, int> min_risk_node = std::min_element(visit_candidates.begin(), visit_candidates.end(),
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

	Matrix<Node> extended_nodes = extend_matrix(nodes, 5, 5);

	const std::pair<int, int> START_POINT{ 0, 0 };
	const std::pair<int, int> END_POINT{ extended_nodes.num_rows() - 1, extended_nodes.num_columns() - 1 };


	calculate_total_path_risk(START_POINT, END_POINT, extended_nodes);
	int total_risk = extended_nodes.get_data(END_POINT.first, END_POINT.second).total_move_risk;
	std::cout << "Total risk to get to bottom right is: " << total_risk << std::endl;
}