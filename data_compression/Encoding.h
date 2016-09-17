//============================================================================
// Name        : Encoding.h
// Author      : Taylan D.
// Created on  : Sep 17, 2016
// Copyright   : The MIT License (MIT)
//============================================================================

#ifndef ENCODING_H_
#define ENCODING_H_

class Encoding {
public:
	virtual ~Encoding() {};

	virtual void encode(std::vector<int>& v) = 0;
	virtual void decode(std::vector<int>& v) = 0;
};


#endif /* ENCODING_H_ */
