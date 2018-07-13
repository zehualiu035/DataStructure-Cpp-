/*
 * Names: Mark Barnes, Zehua liu
 * Date: 14/2/17
 * PA3
 * Description: Builds huffman tree, and has encode and decode methods.
 */
#include <queue>
#include <functional>
#include <vector>
#include <fstream>
#include <stack>
#include "HCTree.h"
//#include "BitInputStream.h"
//#include "BitOutputStream.h"

using namespace std;

/*
 * Description: The purpose of this method is to set up Huffman tree.
 * 
 */
void HCTree::build(const vector<int>& freqs) {
	std::priority_queue<HCNode*,vector<HCNode*>, HCNodePtrComp> nodeQ;

	// Questions: What is the purpose of symbol? 
	for(int i = 0; i < 256;i++) { 
		
		// Checks if the frequency was 0, skip if was.
		if(freqs[i] != 0) {
			HCNode* n=new HCNode(freqs[i], i, 0, 0, 0);
			nodeQ.push(n);
			root=n;
		  leaves[i]=n;
		}
	}
	
	// Iterate through the nodeQ
	while(!nodeQ.empty() && nodeQ.size() > 1){

		//top takes next value, pop removes it
		HCNode* left = nodeQ.top();
		nodeQ.pop();

		HCNode* right = nodeQ.top();
		nodeQ.pop();
		
		// create a parent node w/ sum of left and right children
		HCNode* parent = new HCNode((left->count)+(right->count),
 										left->symbol,left,right,0);
		left->p = parent;
		right->p = parent;

		// check before pushing back into the priorityQ if q is empty.
		if(!nodeQ.empty()) {
			nodeQ.push(parent);
		}
			root=parent;
	}
}

/*HCTree::encode(byte symbol, BitOutputStream& out) const {
	HCNode* cur = leaves[symbol];
	std::stack<unsigned char> code;
	// if the cur's parent exists, then check which side cur node is on 
	while(cur->p){
		// the cur node is the left child
		if(cur == cur->p->c0) {
			// add 0 to the code
			code.push('0');
		}
		// the cur node is the right child
		else {
			// add 1 to the code
			code.push('1');
		}

		// adjust the location of cur
		cur = cur->p;
	}

	// now we need to write the coded values to the output stream	
	iore pushing back into the priorityQ if q is empty. If so
		// then dont push.
		if(!nodeQ.empty()) {
			nodeQ.push(parent);
		}
			root=pf (out!=NULL) {
		// for each value in the stack we will write it out to the file
    for (int i=0 ; i<code.size() ; i++) {
			// QUESTION: Ask tutor if this should be a char or another value
      fputc (code.pop(), out);
		}
  }

}*/

// write out the 'char' value of 0 and 1, to represent the sequence of bits
void HCTree::encode(byte symbol, ofstream& out) const {
	HCNode* cur = leaves[symbol];
	std::stack<unsigned char> code;
	
	// if the curr's parent exists, then check which side curr node is on
	if(cur==root){out << '0';return;}
	
	// ascend from leaf to root
	while(cur->p) {
		if(cur == cur->p->c0) {
			code.push('0');
		}
		else {
			code.push('1');
		}
		//adjust the location of curr
		cur = cur->p;
	}

	//write the coded values to the output stream
	if (out) {
		// write each value in the stack to out file
		while(!code.empty()){
			out << code.top();
			code.pop();
		}
	}
}

/*
 * We decode the whole file, reading in each bit, when reaching a leaf node
 * we return that value.  
 */
/*int HCTree::decode(BitInputStream& in) const {
	int charVal;
	HCNode* curr = root;
	
	if(in) {
		charVal = fgetc(in);
		while(charVal != EOF) {
			// is this an ascii value? or int value?
			if(charVal == '0') {
				if(curr->c0) {
					curr = curr->c0;
				}
				// curr is already a leaf
				else {
					return curr->symbol;
				}			
			}	
			else if(charVal == '1') {
				if(curr->c1) {
					curr = curr->c1;
				}
				// curr is already a leaf
				else {
					return curr->symbol;
				}
			}
			else {
				cout << "The value is neither 1 nor 0." << endl;
				return;
			}
			charVal = fgetc(in);
		}
	}
}*/

int HCTree::decode(ifstream& in) const {
	unsigned char charVal;
	HCNode* curr = root;
	
	// check if stream is open
	if(in) {
		while(1) {
			charVal = (unsigned char) in.get();
			
			// end of file check
			if(in.eof()) {
				break;
			}
			
			// Reading in, if 0 take left path, if 1 take right.
			if(charVal == '0') {
				if(curr->c0) {
					curr = curr->c0;
					// if a leaf then return the value
					if(!curr->c0 && !curr->c1) {
						return curr->symbol;
					}
				}
			}
		
			else if(charVal == '1') {
				if(curr->c1) {
					curr = curr->c1;
					if(!curr->c0 && !curr->c1) {
						return curr->symbol;
					}
				}
			}
		}
	}
}

/* implements deleteNode helper method, it destructs tree */
HCTree::~HCTree() {
	deleteNode(root);
}

/* Helper method for destructor */
void HCTree::deleteNode(HCNode* node) {
	if(node == 0) {
		return;
	}

	if(node->c0) {
		deleteNode(node->c0);
	}

	if(node->c1) {
		deleteNode(node->c1);
	}
	
	delete node;
}


