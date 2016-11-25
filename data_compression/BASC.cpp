/*============================================================================
* Name        : BASC.cpp
* Author      : Taylan Dogan
* Created on  : Nov 25, 2016
* Copyright   : The MIT License (MIT)
* Description : 
*///==========================================================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <bitset>

using namespace std;

const int BITSET_SIZE = 32;

string int_to_binary_string(int number, int b) {
    const std::string result = std::bitset<BITSET_SIZE>(number).to_string();
    return result.substr(result.size() - b);
}

int binary_string_to_int(string binary_str) {
	return std::bitset<BITSET_SIZE>(binary_str).to_ulong();
}

string basc_encode(vector<int>& v, int b) {
	std::stringstream encoded_ss;
	// Initial bit length is set to b
	int current_b = b;

	for(unsigned int i = 0; i < v.size(); i++) {
		// Calculate how many bits are required for given integer
		int b_prime = ceil(log2(v[i] + 1));

		// If required bit number is lower than or equal to the previous bit length
		if(b_prime <= current_b) {
			// Emit a zero, followed by binary representation of integer using b bits
			encoded_ss << "0";
			encoded_ss << int_to_binary_string(v[i], current_b);
		}

		// If we need more bits than the previous bit length
		else {
			// Emit( b_prime - current_b) 1's
			for(int a = 0; a < (b_prime - current_b); a++) {
				encoded_ss << "1";
			}

			// Then, emit a zero, followed by (b_prime - 1) least significant bits of integer
			encoded_ss << "0";
			encoded_ss << int_to_binary_string(v[i], b_prime - 1);
		}

		// Update the bit length value
		current_b = b_prime;
	}

	return encoded_ss.str();
}

vector<int> basc_decode(string encoded, int b) {
	vector<int> v;
	string::iterator it;
	int current_b = b;
	int b_prime = -1;

	for(it = encoded.begin(); it < encoded.end(); ) {

		// If the codeword starts with a zero
		if(*it == '0') {
			// Move iterator once, to skip the flag
			it++;
			// Read b bits from the codeword
			long l = binary_string_to_int(std::string(it, it + current_b));
			v.push_back(l);
			// Calculate bit length for the next step
			b_prime = ceil(log2(l + 1));

			// Move iterator
			it = it + current_b;
		}

		else {
			int diff_of_bit_lengths = 0;
			// Read consecutive 1's until a zero
			while(*it == '1') {
				diff_of_bit_lengths++;
				it++;
			}
			// Skip that zero
			it++;

			// Calculate b'
			b_prime = current_b + diff_of_bit_lengths;

			// Read (b'-1) bits from the current codeword and prepend a 1
			std::string s(it, it + b_prime - 1);
			s.insert (0, 1, '1');

			// Convert it to decimal
			v.push_back(binary_string_to_int(s));

			// Move iterator
			it = it + b_prime - 1;
		}

		// Update bit length
		current_b = b_prime;
	}

	return v;
}

int main() {
	vector<int> test_v = {15, 6, 2, 3, 0, 0, 0, 0, 4, 5, 17, 31};
	string basc_encoded = basc_encode(test_v, 5);
	std::cout <<"Encoded: " << basc_encoded << endl;

	vector<int> decoded = basc_decode(basc_encoded, 5);
	std::cout << "Decoded: ";
	for(int i : decoded) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}
