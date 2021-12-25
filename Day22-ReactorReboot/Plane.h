#pragma once

struct Point;
enum Axis{AX, AY, AZ};
enum Direction{MINUS, PLUS};

struct Plane
{
	Plane(Axis a, Direction d, int level) : axis{ a }, dir{ d }, value{ level }{}
	Axis axis;
	Direction dir;
	int value;
};

