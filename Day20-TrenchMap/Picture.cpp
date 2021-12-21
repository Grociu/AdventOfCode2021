#include "Picture.h"
#include "Matrix.h"
#include "Enhance_key.h"
#include <string>
#include <sstream>

Picture::Picture(const std::vector<std::vector<char>>& chars, char outside) : pixels{ Matrix<char>{chars} }, outside_area{ outside } {}

char Picture::get_pixel(const int& row, const int& column) const {
	try { // try reading from the pixels that are accounted for
		return pixels.get_data(row, column);
	}
	catch (std::out_of_range) { // IF FAILED, return empty because the canvas is infinite!
		return outside_area;
	}
}

// returns values for a 3x3 square surrounding the pixel at r,c, needed to determine the enhanced pixel value
std::vector<char> Picture::get_square(const int& row, const int& column) const {
	std::vector<char> result;
	for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++) result.push_back(get_pixel(row + i, column + j));
	return result;
}

int Picture::get_enhanced_key(const int& row, const int& column) const {
	std::string binary_string{ "" };
	for (const char& c : get_square(row, column)) binary_string += c;
	return stoi(binary_string, 0, 2);
}

void Picture::draw() const {
	for (int i = 0; i < rows(); i++) {
		std::cout << std::endl;
		for (int j = 0; j < columns(); j++) {
			std::cout << (get_pixel(i, j) == '1' ? '#' : '.');
		}
	}
	std::cout << std::endl;
}

int Picture::filled_pixels() const {
	int count{ 0 };
	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < columns(); j++) {
			if (get_pixel(i, j) == '1') count++;
		}
	}
	return count;
}

std::istream& operator>>(std::istream& is, Picture& p) {

	std::vector<std::vector<char>> chars;
	std::string line;
	char c;

	while (std::getline(is, line)) {
		if (line == "") continue;
		chars.push_back(std::vector<char>{});
		std::istringstream iss{ line };
		while (iss >> c) {
			switch (c) {
			case '#': chars.back().push_back('1'); break;
			case '.': chars.back().push_back('0'); break;
			default: {}
			}
		}
	}
	p = Picture{ chars };
	return is;
}

void Picture::update_outside(const Enhance_key& k) {
	outside_area = (k.get(get_enhanced_key(-4, -4)) ? '1' : '0');
}

Picture enhance(const Picture& p, const Enhance_key& k) {
	std::vector<std::vector<char>> new_chars;
	for (int i = -1; i < p.rows() + 1; i++) {
		new_chars.push_back(std::vector<char>(0));
		for (int j = -1; j < p.columns() + 1; j++) {
			if (k.get(p.get_enhanced_key(i, j))) new_chars.back().push_back('1');
			else new_chars.back().push_back('0');
		}
	}
	Picture new_pic{ new_chars, p.outside()};
	new_pic.update_outside(k);
	return new_pic;
}