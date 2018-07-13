#include <iostream>
#include "BitOutputStream.h"

using namespace std;

/* send the buffer to the output, and clear it */
void BitOutputStream::flush() {
	out.put(buf);
	out.flush();
	buf = nbits = 0;
}	

void BitOutputStream::writeBit(int i) {

	// if bit buffer is full, then flush. 
	if(nbits == 8) { 		
		flush();
	}	
	char mask = i;
	// Write LSB of i into the buffer at curr index
	mask = mask << 7 - nbits;
	buf = mask | buf;

	cout << "writeBit produced as a mask: " << mask << endl;
	cout << "nbits is: " << nbits << endl;
	cout << "buf is: " << buf << endl;

	// Increment the index
	nbits++;
}




