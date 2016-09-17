//============================================================================
// Name        : CompressionAlgorithms.cpp
// Author      : Taylan D.
// Created on  : Sep 17, 2016
// Copyright   : The MIT License (MIT)
// Description : Some algorithms related to data compression (C++11).
//============================================================================

#include <iostream>
#include <memory>
#include <vector>

#include "Encoding.h"
#include "DeltaEncoding.h"

using namespace std;

template<typename T>
void print_vector(const vector<T>& v) {
	for(auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<int> v = {5, 9, 11, 23, 20, 20, 71, 80, 92, 100};

	std::unique_ptr<DeltaEncoding> delta_enc(new DeltaEncoding());
	delta_enc->encode(v);
	print_vector(v);
	delta_enc->decode(v);
	print_vector(v);
	//delete delta_enc;

	return 0;
}
