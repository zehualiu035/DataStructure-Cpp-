#include "util.h"
#include "DictionaryBST.h"
#include <set>
//Zehua Liu A92406573
/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){

}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	std::pair<std::set<std::string>::iterator,bool> p;
	if(DictionaryBST::find(word)){return false;}//check if is there
	p=tree.insert(word);//insert
	return p.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	std::set<std::string>::iterator it=tree.end();
	if(tree.find(word)==it){//check find
		return false;
	}
	return true;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}

