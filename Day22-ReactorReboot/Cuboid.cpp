#include "Cuboid.h"
#include "Plane.h"

#include <stdexcept>
#include <iostream>

// constructor from origin and dimensions
Cuboid::Cuboid(Point a, int dx, int dy, int dz, bool lit) : origin{ a }, d_x{ dx }, d_y{ dy }, d_z{ dz }, is_lit{ lit }{}

// constructor from two edge points
Cuboid::Cuboid(Point a, Point b, bool lit) : Cuboid(a, b.x - a.x, b.y - a.y, b.z - a.z, lit) {}

// is point p inside the Cuboid?
bool Cuboid::contains(const Point& p) const {
	return (
		p.x >= origin.x &&
		p.x <= origin.x + d_x &&
		p.y >= origin.y &&
		p.y <= origin.y + d_y &&
		p.z >= origin.z &&
		p.z <= origin.z + d_z
		);
}

// returns a vector of the 6 planes that the cubiod is defined by. the direction will mark whether the plane cuts 'below' or above the axis
std::vector<Plane> Cuboid::planes() const {
	std::vector<Plane> planes;
	planes.push_back(Plane{ AX, MINUS, origin.x });
	planes.push_back(Plane{ AY, MINUS, origin.y });
	planes.push_back(Plane{ AZ, MINUS, origin.z });
	planes.push_back(Plane{ AX, PLUS, origin.x + d_x });
	planes.push_back(Plane{ AY, PLUS, origin.y + d_y });
	planes.push_back(Plane{ AZ, PLUS, origin.z + d_z });
	return planes;
}

bool Cuboid::is_sliced_by(const Plane& p) const {
	// DESIGN: an axis slices a cuboid if there is some of the cuboid AT the level of the axis and one level above or below
	switch (p.axis) {
	case AX: {
		if (!contains(Point{p.value, origin.y, origin.z})) return false;
		if (p.dir == MINUS) return contains(Point{ p.value - 1, origin.y, origin.z });
		else return contains(Point{ p.value + 1, origin.y, origin.z });
	}
	case AY: {
		if (!contains(Point{ origin.x, p.value, origin.z })) return false;
		if (p.dir == MINUS) return contains(Point{ origin.x, p.value - 1, origin.z });
		else return contains(Point{ origin.x, p.value + 1, origin.z });
	}
	case AZ: {
		if (!contains(Point{ origin.x, origin.y, p.value })) return false;
		if (p.dir == MINUS) return contains(Point{ origin.x, origin.y, p.value - 1 });
		else return contains(Point{ origin.x, origin.y, p.value + 1 });
	}
	default: throw std::runtime_error("Unrecognized value for enum Axis"); // all Axis enum members acounted for
	}
}

// True if the first Cuboid contains the second cuboid whole.
bool envelops(const Cuboid& a, const Cuboid& b) {
	return a.contains(b.o()) && a.contains(Point{ b.x() + b.dx(), b.y() + b.dy(), b.z() + b.dz() });
}

// True if there is at least one common point in a and b
bool intersects(const Cuboid& a, const Cuboid& b) {
	return (a.x() <= b.x() + b.dx() && a.x() + a.dx() >= b.x()) &&
		(a.y() <= b.y() + b.dy() && a.y() + a.dy() >= b.y()) &&
		(a.z() <= b.z() + b.dz() && a.z() + a.dz() >= b.z());
}

std::vector<Cuboid> slice(const Cuboid& c, const Plane& p) {
	std::vector<Cuboid> slices;
	
	// does the Plane slice the cuboid?
	if (c.is_sliced_by(p)) {
		// we know that the plane slices the cuboid in two
		// depending on the cutoff direction the point of cutoff is different
		int offset_bottom = p.dir == MINUS ? p.value - 1 : p.value;
		int offset_top = offset_bottom + 1;

		switch (p.axis) {
		case AX: {
			// bottom part - starts at origin and ges 'up' to p.value - 1 (if cutting below) or p.value if cutting above p.value level
			slices.push_back(Cuboid{
				c.o(),
				offset_bottom - c.x(),
				c.dy(),
				c.dz(),
				c.lit() });
			// 'top' part, starts a point higher than offset
			slices.push_back(Cuboid{ 
				Point{offset_top, c.y(), c.z()},
				c.x() + c.dx() - offset_top,
				c.dy(), 
				c.dz(), 
				c.lit() });
			break;
		}
		case AY: {
			slices.push_back(Cuboid{
				c.o(),
				c.dx(),
				offset_bottom - c.y(),
				c.dz(),
				c.lit() });
			slices.push_back(Cuboid{
				Point{c.x(), offset_top, c.z()},
				c.dx(),
				c.y() + c.dy() - offset_top,
				c.dz(),
				c.lit() });
			break;
		}
		case AZ: {
			slices.push_back(Cuboid{
				c.o(),
				c.dx(),
				c.dy(),
				offset_bottom - c.z(),
				c.lit() });
			slices.push_back(Cuboid{
				Point{c.x(), c.y(), offset_top},
				c.dx(),
				c.dy(),
				c.z() + c.dz() - offset_top,
				c.lit() });
			break;
		}
		default: {} // all Axis enum mmbers accounted for
		}
	}
	else slices.push_back(c);
	return slices;
}

// subtracts cuboid b from cuboid a, leaving only the parts of a that are not in b
std::vector<Cuboid> subtract(const Cuboid& a, const Cuboid& b) {
	// 1. slice the cuboid a with the planes of cuboid b
	std::vector<Plane> planes = b.planes();
	std::vector<Cuboid> slices;
	std::vector<Cuboid> operands;

	operands.push_back(a);

	while (operands.size() > 0) {
		Cuboid c = operands.back();
		operands.pop_back();
		// is the operand enveloped by b? if so discard
		if (envelops(b, c)) continue;
		// is the operand not intersecting with b? if so, save as part of result
		if (!intersects(c, b)) { 
			slices.push_back(c); continue; 
		}
		// find slicing plane
		for (int i = 0; i < planes.size(); i++) {
			if (!c.is_sliced_by(planes[i])) continue;
			else {
				// this plane slices the operand c
				std::vector<Cuboid> new_operands = slice(c, planes[i]);
				for (const Cuboid& no : new_operands) operands.push_back(no);
				// each plane should cut at most once
				planes.erase(planes.begin() + i);
				break;
			}
		}
	}
	return slices;
}
