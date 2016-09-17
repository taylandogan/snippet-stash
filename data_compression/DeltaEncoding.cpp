/*============================================================================
* Name        : DeltaEncoding.cpp
* Author      : Taylan Dogan
* Created on  : Sep 17, 2016
* Copyright   : The MIT License (MIT)
* Description : Delta encoding implementation (C++11).
*///============================================================================

#include <iostream>
#include <vector>

using namespace std;

void encode(vector<int>& input) {
	int last = 0;
	for(unsigned int i = 0; i < input.size(); i++) {
		int current = input[i];
		input[i] = current - last;
		last = current;
	}
}

void decode(vector<int>& encoded) {
	int last = 0;
	for(unsigned int i = 0; i < encoded.size(); i++) {
		int current = encoded[i];
		encoded[i] = current + last;
		last = encoded[i];
	}
}

template<typename T>
void print_vector(const vector<T>& v) {
	for(auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<int> v = {5, 9, 11, 23, 20, 20, 71, 80, 92, 100};

	encode(v);
	print_vector(v);
	decode(v);
	print_vector(v);
	return 0;
}
