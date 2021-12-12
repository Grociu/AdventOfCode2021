#include "Path.h"
#include <iostream>


Cave_type ctype(const std::string& cv) {
	if (isupper(cv[0])) return large;
	else return small;
}

// Path members
Path::Path(const std::string& start) { route.push_back(start); }

Path::Path(const Path& p, const std::string& new_way)
	: small_visited_twice{ p.small_visited_twice } {
	route = p.route;
	route.push_back(new_way);
	count_small(new_way);
};

// was the node already visited on this path?
bool Path::already_visited(const std::string& node) const {
	return std::find(route.begin(), route.end(), node) != route.end(); 
}

// is this a valid net move?
bool Path::can_visit(const std::string& node) const {
	// cant visit the start of route
	if (ctype(node) == large || !already_visited(node)) return true;
	if (node == route[0]) return false; // can't go back to beginning
	return !small_visited_twice;
}

void Path::print() const {
	std::cout << "Path Route: ";
	for (auto& s : route) std::cout << s << " > ";
	std::cout << std::endl;
}

void Path::count_small(const std::string& node) {
	if (small_visited_twice || ctype(node) == large) return; // already fullfilled no need to adjust
	small_visited_twice = std::count(route.begin(), route.end(), node) >= 2;
}

std::string Path::current() const {
	return route.back();
}