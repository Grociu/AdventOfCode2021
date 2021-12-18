#include <iostream>
#include <sstream>
//#include "Snailfish_number.h"
#include "BT_node.h"

int main() {
	const std::string read = "[1,2]";

	struct Bt_node* root = new Bt_node();
	root->attach(new Bt_node(1));
}