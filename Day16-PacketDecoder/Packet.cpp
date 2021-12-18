#include "Packet.h"
#include <sstream>
#include <bitset>



	// Converts a hexadecimal character c to a string that's the binary representation of that character
	std::string hex_to_binary(char c) {
		std::stringstream char_stream;
		char_stream << std::hex << c;
		unsigned n;
		char_stream >> n;
		std::bitset<4> b(n);
		return b.to_string();
	}

	// reads n characters from stream stream and returns result
	std::string read_n(std::istream& stream, int n) {
		std::string result(n, ' ');
		stream.read(&result[0], n);
		return result;
	}

	// reads n characters from binary stream stream and returns result and increments the passed index
	std::string read_n_from_bin(std::istream& stream, int n, int& bs_idx) {
		bs_idx += n;
		return read_n(stream, n);
	}

	// from hex_stream reads one hex_character ant moves it to the binary stream, and increments the binary stream size by 4 (length of hex in binary)
	void add_character_from_hex_stream(std::istream& hex_stream, std::stringstream& binary_stream, int& binary_stream_size) {
		char c;
		hex_stream >> c;
		if (!hex_stream) return;
		else {
			binary_stream << hex_to_binary(c);
			binary_stream_size += 4;
		}
		//else throw std::runtime_error("Cannot read from hex_stream.");
	}

	void read_n_hex_into_binary(const int n, std::istream& hex_stream, std::stringstream& binary_stream, int& binary_index, int& binary_size) {
		while (!(binary_index + n*4 <= binary_size)) {
			int control = binary_size;
			char c;
			hex_stream >> c;
			if (!hex_stream) return;
			else {
				binary_stream << hex_to_binary(c);
				binary_size += 4;
			}
			if (control == binary_size) hex_stream.setstate(std::ios::badbit);
		}
	}

	// from a input stream that's a hexadecimal-string, try to read a packet
	// b_str is the optional argument that represents a remnant of a binary_string from 'up' a stage
	std::istream& read_packet(std::istream& hex_stream, Packet& p, std::string b_str) {

		// 1. establish a binary stream to be parsed, and track it's length and last read index
		std::stringstream binary_stream;
		int bs_idx{ 0 }; // tracks current index of binnary stream
		int bs_max{ 0 }; // tracks maximum index of binary stream

		// 1.1 initialize the binary stream, with the optional argument
		binary_stream << b_str;
		bs_max += b_str.length();
		std::cout << "initialized packet " << "bs_idx : " << bs_idx << " bs_max : " << bs_max << std::endl;
		/* REDUNDANT CODE?
		// 2. read a character can be read from hexstream stream
		char ch;
		hex_stream >> ch;
		if (!hex_stream) { return hex_stream; }

		// 3. if we're here a character was read - packet is starting

		// 4. read first character into the binary_stream
		binary_stream << hex_to_binary(ch);
		bs_max += 4;
		*/

		// 5. We need to read the header which is at least 6 characters long (2*4 > 6)
		read_n_hex_into_binary(2, hex_stream, binary_stream, bs_idx, bs_max);
		if (!hex_stream) { return hex_stream; }

		// 5. RULE 1. opening three characters of a packet are the version
		// 6. Save the 'version' in packet [stoi(str, index, base) - converts string to in with base from index
		std::string version;
		version = read_n_from_bin(binary_stream, 3, bs_idx);
		std::cout << "version : " << version << std::endl;
		p.version = stoi(version, 0, 2);
		std::cout << "p.version : " << p.version << std::endl;

		// 7. RULE 2. next three charactes are the ID
		std::string id;
		id = read_n_from_bin(binary_stream, 3, bs_idx);
		std::cout << "id : " << id << std::endl;
		p.id = stoi(id, 0, 2);
		std::cout << "p.id : " << p.id << std::endl;
		std::cout << "read header " << "bs_idx : " << bs_idx << " bs_max : " << bs_max << std::endl;

		// 8. RULE 3 - depending on packet ID do different things
		switch (p.id) {
		case 4: { // LITERAL VALUE
			// read groups of 5 from binary stream
			std::string literal_value;
			while (true) {
				std::string segment;
				// we need 5 chars, that's 2 hexes
				read_n_hex_into_binary(2, hex_stream, binary_stream, bs_idx, bs_max);
				std::cout << "read segment from hex" << " bs_idx : " << bs_idx << " bs_max : " << bs_max << std::endl;
				if (!hex_stream) { return hex_stream; }
				segment = read_n_from_bin(binary_stream, 5, bs_idx);
				std::cout << "segmnent : " << segment << std::endl;
				std::cout << "read 5 from binary" << " bs_idx : " << bs_idx << " bs_max : " << bs_max << std::endl;
				literal_value += segment.substr(1); // add last four bits to the number literal
				std::cout << "literal value : " << literal_value << std::endl;
				if (segment[0] == '0') break; // as long as first character is 1, we continue to read the literal
			}
			/* WASTE  READOUT
			while (bs_idx < bs_max) { // the rest of the characters in the binary stream are waste, move binary stream to bs_max
				std::cout << "bs_idx : " << bs_idx << " bs_max : " << bs_max << std::endl;
				std::string waste = read_n_from_bin(binary_stream, bs_max - bs_idx, bs_idx);
				std::cout << "waste : " << waste << std::endl;
			}
			*/
			// save literal in packet
			p.values.push_back(stoi(literal_value, 0, 2));
			//std::cout << "p.values[-1] : " << p.values.back() << std::endl;
			break;
		}
		default: { // OPERATOR PACKET
			// I. first chatacter is the length type_id
			std::string length_type; // still should have two characters in buffor
			length_type = read_n_from_bin(binary_stream, 1, bs_idx);
			// II. determine the number of bits deterining the remaining packet length
			int label_length;
			switch (length_type[0]) {
			case '0': {label_length = 15; break; }
			case '1': {label_length = 11; break; }
			default: throw std::runtime_error("Error reading an operator - lenght_type fail");
			}
			// III read label
			read_n_hex_into_binary(label_length / 4 + 1, hex_stream, binary_stream, bs_idx, bs_max);
			if (!hex_stream) { return hex_stream; }
			std::string label = read_n_from_bin(binary_stream, label_length, bs_idx);
			switch (length_type[0]) {
			case '0': {
				// label represents the number of bits the subpackets take
				int bits_in_subpackets = stoi(label, 0, 2);
				// IV read sub-packets until length into a new hex_substring 
				// PROBLEM - binary string can have some chars left and we want  those chars in front of the hex_string (but not 4)
				std::string binary_remnant;
				char b_ch;
				while (binary_stream >> b_ch) binary_remnant += b_ch;
				// define the new hex_sub-stream to read just some bits 
				std::string hex_substream_string;
				hex_substream_string = read_n(hex_stream, bits_in_subpackets / 4 + 1);
				std::istringstream hex_substream{ hex_substream_string };
				// V read actual subpackets from the ne sub_stream
				while (hex_substream) {
					Packet s;
					read_packet(hex_substream, s, binary_remnant);
					p.subpackets.push_back(s);
				}
				break;
			}
			case '1': { break; } // not implemented
			default: throw std::runtime_error("Error reading an operator - lenght_type fail");
			}
			
		} // END OF OPERATOR PACKET
		} // END OF PACKET TYPE SWITCH
		// Packet successfully read
		return hex_stream;
	}


	void decode_packets(const std::string& input, std::vector<Packet>& packets) {
		std::istringstream hex_stream{ input };
		while (hex_stream) {
			Packet p;
			read_packet(hex_stream, p);
			packets.push_back(p);
		}
	}
