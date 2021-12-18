#pragma once

enum Direction{left, right};

struct Bt_node {

	Bt_node();
	Bt_node(int n);
	void attach(Bt_node& b, Bt_node& parent, Direction d);
	Bt_node* get_left();
	Bt_node* rightmost();
	Bt_node* get_right();
	Bt_node* leftmost();

	int value;
	int rank;
	struct Bt_node* left;
	struct Bt_node* right;
	struct Bt_node* parent;

};

Bt_node::Bt_node() {
	value = -1;
	rank = 1;
	left = nullptr;
	right = nullptr; //NULL;
	parent = nullptr;
}

Bt_node::Bt_node(int n) {
	value = n;
	rank = 1;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

void Bt_node::attach(Bt_node& b, Bt_node& n_parent, Direction d) {
	// attach to parent
	switch (d) {
	case Direction::left: {
		if (n_parent.left == nullptr) n_parent.left = &b; 
	}
	case Direction::right: {
		if (n_parent.right == nullptr) n_parent.right = &b; 
	}
	default: {}
	}
	// refer the parent
	parent = &n_parent;
}

// returns a node to the left of current node that has a value, or nullptr;
// used for exploding - will be left of a pair
Bt_node* Bt_node::get_left() {
	if (parent == nullptr || parent->parent == nullptr) return nullptr;
	if (parent->right == this && parent->left != nullptr) return parent->left;
	
	Bt_node* runner = parent->parent;
	if (runner->left == parent || runner->left == nullptr) return parent->get_left();
	if (runner->right == parent) { 
		runner = parent->left; 
		Bt_node* rightmost = runner->rightmost();
		if (rightmost != nullptr) return rightmost;
		return parent->parent->get_left();
	}
}

Bt_node* Bt_node::rightmost() {
	if (right != nullptr) return right->value != -1 ? right : right->rightmost();
	if (left != nullptr) return left->value != -1 ? left : left->rightmost();
	return nullptr;
}

// returns a node to the right of current node that has a value, or nullptr;
// used for exploding - will be left of a pair
Bt_node* Bt_node::get_right() {
	if (parent == nullptr || parent->parent == nullptr) return nullptr;
	if (parent->left == this && parent->right != nullptr) return parent->right;

	Bt_node* runner = parent->parent;
	if (runner->right == parent || runner->right == nullptr) return parent->get_right();
	if (runner->left == parent) {
		runner = parent->right;
		Bt_node* leftmost = runner->leftmost();
		if (leftmost != nullptr) return leftmost;
		return parent->parent->get_right();
	}
}

Bt_node* Bt_node::leftmost() {
	if (left != nullptr) return left->value != -1 ? left : left->leftmost();
	if (right != nullptr) return right->value != -1 ? right : right->leftmost();
	return nullptr;
}