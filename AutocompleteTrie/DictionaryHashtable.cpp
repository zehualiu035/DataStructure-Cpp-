#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>
//Zehua Liu A92406573
/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

bool DictionaryHashtable::insert(std::string word)
{ 
	std::pair<std::unordered_set<std::string>::iterator,bool> p;
	//if( DictionaryHashtable::find(word)){return false;}
	p= this->hash.insert(word);//insert 
	return p.second;

}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{

	std::unordered_set<std::string>::const_iterator it=hash.end();
	if(hash.find(word)==it){//check find
		return false;
	}
	return true;


}/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
