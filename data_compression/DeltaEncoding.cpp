/*============================================================================
* Name        : DeltaEncoding.cpp
* Author      : Taylan Dogan
* Created on  : Sep 17, 2016
* Copyright   : The MIT License (MIT)
* Description : Delta encoding implementation (C++11).
*///============================================================================

#include <iostream>
#include <vector>

#include "DeltaEncoding.h"

using namespace std;

void DeltaEncoding::encode(vector<int>& input) {
	int last = 0;
	for(unsigned int i = 0; i < input.size(); i++) {
		int current = input[i];
		input[i] = current - last;
		last = current;
	}
}

void DeltaEncoding::decode(vector<int>& encoded) {
	int last = 0;
	for(unsigned int i = 0; i < encoded.size(); i++) {
		int current = encoded[i];
		encoded[i] = current + last;
		last = encoded[i];
	}
}
