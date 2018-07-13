#include <iostream>
#include "BitInputStream.h"

void BitInputStream::fill() {
	buf = in.get();
	nbits = 0;
}

int BitInputStream::readBit() {
	//If all bits in the buffer are read, fill the buffer first
	if(nbits == 8) {
			// check that this is what you do
			fill();
	}
	// Get the bit at the appropriate location in the bit buffer, and return
	// the appropriate int
	int bitShift = buf >> (7-nbits); // 7 or 8?
	int mask = 1;
	int result = bitShift & mask;
	// increment index
	nbits++;

	return result;
}
