#ifndef BIT_OUTPUT_STREAM_H
#define BIT_OUTPUT_STREAM_H
#include <iostream>

class BitOutputStream {
private:
	char buf;
	int nbits;
	std::ostream & out;

public:
	/* initialize a BitoutputStream that will use ostream for output */
	BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
			//clear buffer and bit counter
	}
	
	void writeBit(int i);

	/* send the buffer to the output, and clear it */
	void flush();

};

#endif //BIT_OUTPUT_STREAM_H

