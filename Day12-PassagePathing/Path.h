#include <string>
#include <vector>

// Cave_type CLASSIFICATION
enum Cave_type {
	large, small
};

Cave_type ctype(const std::string& cv);

struct Path {
	// constructors
	Path(const std::string& start);
	Path(const Path& p, const std::string& new_way);
	// was the node already visited on this path?
	bool already_visited(const std::string& node) const;
	bool can_visit(const std::string& node) const;
	std::string current() const;
	// DEBUG
	void print() const;
	// data members
	
private:
	void count_small(const std::string& node);
	bool small_visited_twice{ false };
	std::vector<std::string> route;
};