#pragma once
#include <vector>
#include <string>
#include <iostream>

struct Packet {
	int version;
	int id;
	std::vector<int> values;
	std::vector<Packet> subpackets;
	};

// helper functions
std::string hex_to_binary(char c);
std::string read_n(std::istream& stream, int n);
std::string read_n_from_bin(std::istream& stream, int n, int& bs_idx);
void add_character_from_hex_stream(std::istream& hex_stream, std::stringstream& binary_stream, int& binary_stream_size);

// operators
std::istream& read_packet(std::istream& hex_stream, Packet& p, std::string b_str = "");
void decode_packets(const std::string& input, std::vector<Packet>& packets);
