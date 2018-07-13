/*
 * ActorGraph.h
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/2/17
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include "Movie.h"
#include "ActorNode.h"
#include <unordered_map>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
// Maybe include some data structures here

using namespace std;
class MovieComp {
public:
	bool operator () (Movie*& lhs, Movie*& rhs) {
		return lhs->year   > rhs->year ;
	}
};
class ActorGraph {
protected:

public:
  ActorGraph(void);
	~ActorGraph();

	unsigned int numOfEdge=0;
	unsigned int numOfMovie=0;	
	unsigned int numOfActor=0;
	unordered_map<string, ActorNode*> actorsHash;
	unordered_map<string, Movie*> moviesHash;
  priority_queue<Movie*, vector<Movie*>,MovieComp> moviePQ;

   // Maybe add some more methods here
  
   /** You can modify this method definition as you wish
    *
    * Load the graph from a tab-delimited file of actor->movie relationships.
    *
    * in_filename - input filename
    * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
    *
    * return true if file was loaded sucessfully, false otherwise
    */

	ActorNode* findRoot(ActorNode* node);
	int BFS(string actor1,string actor2,int year);
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
	void deleteActNodes();											// helper method for the destructor
	int ufind(string actor1,string actor2);     // method for union find
	int setPBFS(string actor1,string actor2);		// resets the parent pointers
	int dijkstra(string actor1,string actor2);  // dijkstra helper method
	int unite(Movie* m);												// unites the actors for disjoint set
};


#endif // ACTORGRAPH_H
