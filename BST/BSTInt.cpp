
#include "BSTInt.h"

/* Function definitions for a int-based BST class */


/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
  if (!root) {
    root = new BSTNodeInt(item);
    ++isize;
    return true;
  }

//Check for duplicate
	
	if(find(item))
	return false;

  BSTNodeInt* curr = root;
  
  while (curr->left || curr->right) {
    if (item < curr->data) {
	if(!curr->left){
		break;
			}
      curr = curr->left;
    }
    else if (curr->data < item) {
	if(!curr->right){
		break;}
      curr = curr->right;
    }
    else {
      return false;
    }
  }

  // Ready to insert
  BSTNodeInt* newNode = new BSTNodeInt(item);
  if (item < curr->data) {
    curr->left = newNode;
    newNode->parent = curr;
  }
  else {
    curr->right = newNode;
    newNode->parent = curr;
  }

  ++isize;
  return true;

}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
  BSTNodeInt* curr = root;
  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
    }
    else if (item < curr->data) {
      curr = curr->left;
    }
    else {
      return true;
    }
  }
  return false;
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
  return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
 */
int BSTInt::height() const
{
  return recHeight(root);
}

/**Recursively calculate the height*/
int BSTInt::recHeight(BSTNodeInt* current) const 
{

if(!current)
return -1;

int lheight = recHeight(current->left);
int rheight = recHeight(current->right);

if(lheight > rheight)
return (lheight + 1);

else return(rheight + 1); 





}


/** Return true if the BST is empty, else false. 
 */
bool BSTInt::empty() const 
{
  if(!root)
	return true;
  else
  return false;
}




/* do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt* n)
{
if(!n){
return;
}
	
deleteAll(n->left);
deleteAll(n->right);

delete n;

}
