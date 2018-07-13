#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2016
 * Author: Christine Alvarado and YOU
 */
int main() {

	/* Create an STL vector of some ints */
	/*test*/
	vector<int> v;
	v.push_back(3);
	v.push_back(4);
	v.push_back(1);
	v.push_back(100);
	v.push_back(-33);

	//we're adding here
	v.push_back(10);
	v.push_back(390);

	vector<int> v2;//v2 is empty tree



	vector<int> v3;//v3 left tree

	v3.push_back(100);
	v3.push_back(50);
	v3.push_back(25);
	v3.push_back(12);
	v3.push_back(6);



	/* Create an instance of BST holding int */
	BSTInt b;
	BSTInt b2;
	BSTInt b3;
	// Could use: for(auto item : v) { instead of the line below
	for(int item : v) {
		bool pr = b.insert(item);
		if(! pr ) {
			cout << "Incorrect bool return value when inserting " << item 
				<< endl;
			return -1;
		}
	}

	//build b3

	for(int item : v3) {
		bool pr3 = b3.insert(item);
		if(! pr3 ) {
			cout << "Incorrect bool return value when inserting " << item 
				<< endl;
			return -1;
		}
	}





	/* Test size. */
	cout << "Size of b1 is: " << b.size() << endl;
	if(b.size() != v.size()) {
		cout << "... which is incorrect." << endl;
		return -1;
	}



	cout << "Size of b2 is: " << b2.size() << endl;
	if(b2.size() != v2.size()) {
		cout << "... which is incorrect." << endl;
		return -1;
	}

	cout << "Size of b3 is: " << b3.size() << endl;
	if(b3.size() != v3.size()) {
		cout << "... which is incorrect." << endl;
		return -1;
	}






	/* Test find return value. */
	// Test the items that are already in the tree
	for(int item : v) {
		if(!b.find(item)) {
			cout << "Incorrect return value when finding " << item << endl;
			return -1;
		}
	}



	for(int item : v2) {
		if(b2.find(item)) {
			cout << "Incorrect return value when finding " << item << endl;
			return -1;
		}
	}
	for(int item : v3) {
		if(!b3.find(item)) {
			cout << "Incorrect return value when finding " << item << endl;
			return -1;
		}
	}











	/*Test height*/


           if(b.height()!=3){
	cout << "Height of b is: " << b.height() << endl;
		return -1;
	}

    if(b2.height()!=-1){
	cout << "Height of b2 is: " << b2.height() << endl;
		return -1;
	}
  if(b3.height()!=4){
	cout << "Height of b3 is: " << b3.height() << endl;
		return -1;
	}



	/* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

	
	// Test the template version of the BST  with ints 
	BST<int> btemp;
	for (int item : v) {
	// The auto type here is the pair of BSTIterator<int>, bool
	cout << "Inserting " << item << " into the int template-based BST...";
	auto p = btemp.insert(item);
	if (*(p.first) != item) {
	cout << "Wrong iterator returned.  "
	<< "Expected " << item << " but got " << *(p.first) << endl;
	return -1;
	}
	if (!p.second) {
	cout << "Wrong boolean returned.  Expected true but got " 
	<< p.second << endl;
	return -1;
	}
	cout << "success!" << endl;

	}

	// Now test finding the elements we just put in
	for (int item: v) {
	cout << "Finding " << item << "...." << endl;
	BSTIterator<int> foundIt = btemp.find(item);
	if (*(foundIt) != item) {
	cout << "incorrect value returned.  Expected iterator pointing to "
	<< item << " but found iterator pointing to " << *(foundIt) 
	<< endl;
	return -1;
	}
	cout << "success!" << endl;
	}



	// Test the iterator: The iterator should give an in-order traversal

	// Sort the vector, to compare with inorder iteration on the BST
	sort(v.begin(),v.end());

	cout << "traversal using iterator..." << endl;
	auto vit = v.begin();
	auto ven = v.end();

	// This is equivalent to BSTIterator<int> en = btemp.end();
	auto en = btemp.end();

	//This is equivalent to BST<int>::iterator it = btemp.begin();
	auto it = btemp.begin();
	for(; vit != ven; ++vit) {
	cout<< "before the for loop111"<<endl;
	if(! (it != en) ) {
	cout << *it << "," << *vit 
	<< ": Early termination of BST iteration." << endl;

	return -1;

	}
	cout << *it << endl;
 cout<<" here after d it"<<endl;
 
 
 cout<< "vit is "<< *vit<<endl;

 
  if(*it != *vit) {
	cout << *it << "," << *vit 
	<< ": Incorrect inorder iteration of BST." << endl;
	return -1;
	}
	++it;
	}
cout << "here"<<endl;
	cout << "success!" << endl;



	// ADD MORE TESTS HERE.  You might also want to change what is input
	// into the vector v.


	


	cout << "All tests passed!" << endl;
	return 0;
}
