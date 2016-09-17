/*============================================================================
* Name        : DeltaEncoding.h
* Author      : Taylan Dogan
* Created on  : Sep 17, 2016
* Copyright   : The MIT License (MIT)
* Description : Delta encoding implementation (C++11).
*///============================================================================

#ifndef DELTAENCODING_H_
#define DELTAENCODING_H_

#include <vector>
#include "Encoding.h"

class DeltaEncoding : public Encoding {
public:
	DeltaEncoding() {};
	~DeltaEncoding() {};

	void encode(std::vector<int>& v);
	void decode(std::vector<int>& v);
};

#endif /* DELTAENCODING_H_ */
