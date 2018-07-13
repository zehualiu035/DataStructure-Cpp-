/*
 * Names: Mark Barnes, Zehua Liu
 * Date: 2/10/17
 * PA 3
 * Description: This file 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include "HCTree.h"
#include "HCNode.h"

using namespace std;

int main (int argc, char* argv[]) {
	
	// checks that 3 arguments were passed in
	if(argc != 3) {
		cout << "Invalid number of argumnets, needs 3." << endl;
		return -1;
	}

	string inFile = argv[1];
	string outFile = argv[2];
	vector<int> freqs (256, 0);
  ifstream in;
	ofstream out;	
	in.open(inFile);
	out.open(outFile);
	
	// check that in and out files are open
	if(!in.is_open()) {
		cout << "The input file was unable to be opened." << endl;
		return -1;
	}
  if(!out.is_open()) {
		cout << "The output file was unable to be opened." << endl;
		return -1;	
	}
	
	// go to the beggining of the file
	in.seekg(0, ios_base::beg);
  unsigned char c;

	// read through the whole file, and then check then increment freqs of
	// the char value inside of freqs vector
	while(1) {
		c = (unsigned char)in.get();
		if(in.eof()) break;
		freqs[(int)c]++;
	}
	
	// close the stream and build the tree
	in.close();
  HCTree tree;
	tree.build(freqs);

	// step 5: output the values to the out file.
	for(int tmp: freqs) {
		out << tmp;
		out << '\n';
	}
	
	//step 6: open the input file again for reading
	in.open(inFile);
	if(!in.is_open()) {
		cout << "The input file was unable to be opened." << endl;
	 	return -1;
	}
	
	/*
	 * step 7: Translate each byte from the input file into its code, and append
	 * these codes as a sequence of bits to the output file. 
	 */
	while(1) {
		c = (unsigned char)in.get();
		if(in.eof()) break;

		// case when eof, breaks from while loop.	
		tree.encode(c, out);
	
	}
	
	// close the input and output streams
	in.close();
	out.close();

}
