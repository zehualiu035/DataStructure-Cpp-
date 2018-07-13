#ifndef BIT_INPUT_STREAM_H
#define BIT_INPUT_STREAM_H

#include <iostream>

class BitInputStream {
private:
	char buf;
	int nbits;
	std::istream & in;
public:

	/* Initialize BitInputStream that uses given istream for input */
	BitInputStream(std::istream & is) : in(is) {
		buf = 0;
		nbits = 0; //initialize bit index QUESTION: SHOULD THIS BE 7?
	}

	int readBit();

	void fill();
};

#endif //BIT_INPUT_STREAM_H
