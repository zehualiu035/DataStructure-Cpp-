/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */
//Zehua Liu A92406573
#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <queue>
#include <vector>
#include <stack>

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class Node{
public:
bool end;
Node* left;
Node*right;
Node* mid;
char c;
std::string s;
 unsigned int fre;
 Node() :  end(false),left(0), right(0),mid(0),fre(0){} 
//bool operator < (const Node& other);
~Node();//just add thhis
};

class NodePtrComp{//rule to compare ptr,for priority queue
    public:
      bool operator()(Node*& fir, Node*& sec)const{
        return fir->fre < sec->fre;
      }
  };

class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;
bool find(std::string word,unsigned int freq) const;
Node* findLast(std::string word) const;

void BFS(std::queue<Node*> q,std::priority_queue<Node*,std::vector<Node*>, NodePtrComp> &save)
;
  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  
  /* Destructor */
  ~DictionaryTrie();

private:
Node* root;
  // Add your own data members and methods here
  void deleteNode(Node* node);
};


#endif // DICTIONARY_TRIE_H
