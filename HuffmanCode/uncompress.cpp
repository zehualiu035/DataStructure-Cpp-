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

int main (int argc, char* argv[]) {
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

	if(!in.is_open()) {
		cout << "The input file was unable to be opened." << endl;
		return -1;
	}
	if(!out.is_open()) {
		cout << "The output file was unable to be opened." << endl;
		return -1;	
	}
	in.seekg(0, ios_base::beg);
	int nextINT;
	for(int i=0;i<256;i++) {
		in >> nextINT;
		if(in.eof()) break;

		if(nextINT!=0) {
			freqs[i]=nextINT;
		}
	}
	HCTree tree;
	unsigned char c;
	tree.build(freqs);
	while(1){
		c=tree.decode(in);
		if(in.eof())break;
		out << c;
	}
}
