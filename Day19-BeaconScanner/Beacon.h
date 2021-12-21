#include <iostream>

// forward declaration instead of include
struct Scanner;

struct Beacon
{
	Beacon(Scanner& s, int x, int y, int z);
	
	void solve();
	void update_temp();

	int x() const;
	int y() const;
	int z() const;

	void print() const;

	Scanner* parent_scanner;
	int relative_x{ 0 };
	int relative_y{ 0 };
	int relative_z{ 0 };

	int temp_x{ 0 };
	int temp_y{ 0 };
	int temp_z{ 0 };

	bool solved{ false };
	int real_x{ 0 };
	int real_y{ 0 };
	int real_z{ 0 };
};

std::istream& operator>>(std::istream& is, Beacon& b);
bool operator==(const Beacon& b1, const Beacon& b2);
bool operator<(const Beacon& b1, const Beacon& b2);
