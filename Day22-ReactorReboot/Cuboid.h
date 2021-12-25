#pragma once
#include <vector>

struct Point {
	int x;
	int y;
	int z;
};

struct Plane;

// represents an INCLUSIVE cuboid of pixels, with origin at point (ox, oy, oz) and dimensions dx x dy x dz
class Cuboid
{
public:
	Cuboid(Point a, Point b, bool lit=true);
	Cuboid(Point a, int dx, int dy, int dz, bool lit = true);
	
	bool contains(const Point& p) const;
	bool is_sliced_by(const Plane& p) const;
	std::vector<Plane> planes() const;
	
	// returns the number of lit pixels inside the cuboid
	long long lit_pixels() const { return is_lit ? long long(d_x + 1) * long long(d_y + 1) * long long(d_z + 1) : 0 ; }
	bool lit() const { return is_lit; }
	// basic access functions
	
	// origin point of the Cuboid
	Point o() const { return origin; }
	int x() const { return origin.x; }
	int y() const { return origin.y; }
	int z() const { return origin.z; }
	int dx() const { return d_x; }
	int dy() const { return d_y; }
	int dz() const { return d_z; }

private:
	// coordinates of the origin point
	Point origin;
	// size of sides
	int d_x;
	int d_y;
	int d_z;
	// cuboid can be lit or not, if lit, ALL pixels inside are lit
	bool is_lit;
};

bool envelops(const Cuboid& a, const Cuboid& b);
bool intersects(const Cuboid& a, const Cuboid& b);

std::vector<Cuboid> slice(const Cuboid& c, const Plane& p);
std::vector<Cuboid> subtract(const Cuboid& a, const Cuboid& b);
