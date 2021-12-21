#pragma once
#include "Matrix.h"
#include <vector>

struct Enhance_key;

struct Picture
{
	Picture(const std::vector<std::vector<char>>& chars, char outside='0');
	Picture() : pixels{ Matrix<char>{0,0} } {};

	char get_pixel(const int& row, const int& column) const;
	std::vector<char> get_square(const int& row, const int& column) const;
	int get_enhanced_key(const int& row, const int& column) const;

	void draw() const;
	int filled_pixels() const;

	int rows() const { return pixels.num_rows(); }
	int columns() const { return pixels.num_columns(); }

	char outside() const { return outside_area; }
	void update_outside(const Enhance_key& k);
private:
	Matrix<char> pixels;
	// this character is displayed on the 'outside' of the main picture frame in the infinite beyond
	char outside_area{'0'};
};

std::istream& operator>>(std::istream& is, Picture& p);

Picture enhance(const Picture& p, const Enhance_key& k);
