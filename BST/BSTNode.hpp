#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** Starter code for PA1, CSE 100 2016
 * Authors: Christine Alvarado, based on code by Paul Kube 
 * ADD YOUR NAME AS AN AUTHOR HERE
 */

template<typename Data>
class BSTNode {

	public:

		BSTNode<Data>* left;
		BSTNode<Data>* right;
		BSTNode<Data>* parent;
		Data const data;   // the const Data in this node.

		/** Constructor.  Initialize a BSTNode with the given Data item,
		 *  no parent, and no children.
		 */
		BSTNode(const Data & d);


		/** Return the successor of this BSTNode in a BST, or 0 if none.
		 ** PRECONDITION: this BSTNode is a node in a BST.
		 ** POSTCONDITION:  the BST is unchanged.
		 ** RETURNS: the BSTNode that is the successor of this BSTNode,
		 ** or 0 if there is none.
		 */ // TODO            //WHY DOES THIS SAY RTO DODO JRW ETE TERHGDRGRDRRRRRR
		BSTNode<Data>* successor(); 

}; 


// Function definitions
// For a templated class it's easiest to just put them in the same file as the class declaration

template <typename Data>
BSTNode<Data>::BSTNode(const Data & d) : data(d), left(0), right(0), parent(0) {}

/* Return a pointer to the BSTNode that contains the item that is sequentially next 
 * in the tree */
	template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor() //Should have 4 cases
{
	//TODO
	//current pointer
	BSTNode<Data>* curr = 0;

//Case 1

	//If at the root
	if(!parent){

		//root is the largest, return 0
		if(!right)
			return 0;

		if(right){

			curr = this->right; //changed t0 ->

			while(curr->left){

				curr = curr->left;

			}

			return curr;

		}

	} //end root case




//Case 2

	//If the parent is smaller, and there's no children
	//Check all parents, if root is still smaller, return 0

	//if parent is smaller
	//null check
	if(this->parent){
		if((parent->data) < (this->data)){

			//if no right (left doesn't matter)                       
			if(!this->right){

				//	curr = this->parent;

				//traverse up the parents
				while(curr->parent){

					curr = curr->parent;
					//if a parent is larger, return it
					if(data < curr->data)
						return curr;

				}
				//this->data is largest
				return 0;
			}
		}
	}
	//end "no children"

//Case 3

	//if the parent.data is bigger
	if ((this->data) < (this->parent->data))
	{
		//If there is no right
		if(!right)
			return parent;

		//If there is a right
		if(right){

			curr = this->right; //changed from . to ->

			while(curr->left){

				curr = curr->left;
			}

			return curr;

		} //end (data < parent) && right case
	}

//Case 4

	//if there is a right, it will be right->left->left...
	//if a right exists
	if(this->right){

		curr = this->right;

		//check as far left as possible
		while(curr->left){

			curr = curr->left;

		}

		//return either the right, or the right->left...
		return curr;

	}


	//should not happen
	return NULL;
}

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
	stm << '[';
	stm << std::setw(10) << &n;                 // address of the BSTNode
	stm << "; p:" << std::setw(10) << n.parent; // address of its parent
	stm << "; l:" << std::setw(10) << n.left;   // address of its left child
	stm << "; r:" << std::setw(10) << n.right;  // address of its right child
	stm << "; d:" << n.data;                    // its data field
	stm << ']';
	return stm;
}

#endif // BSTNODE_HPP
