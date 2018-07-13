/*
 * Names: Mark Barnes, Zehua Liu
 * Date: 3/2/17
 * PA 4
 * Description: This is the header file for ActorNode. It includes variables
 * and an overrided comparator method 
 */
#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <vector>
#include <iostream>
#include <string>
//#include "Movie.h" this causes issues

using namespace std;

class Movie;

/*
 * Keeps track of actor and movies that the actor was in.
 */
class ActorNode {

public:
	int size=1;							//for unite
	bool done = false;			//for dijkstra
	int dist = 9999; 				// distance is the sum of movie_weights to this actor
	string name; 						// the name of the actor
	ActorNode* parent=0;		// parent pointer used for disjoint set
	Movie* preM = 0;				//pointer to the previous Movie
	vector<Movie*> movies;	// the list of movies the actor has been in
	ActorNode(string name) : name(name){}
};

class NodeComp {
public:
	// overrides compare operator, determines which of the two has a greater dist
	bool operator () (ActorNode*& lhs, ActorNode*& rhs) {
		return lhs->dist > rhs->dist;
	}
};

#endif // ACTORNODE_H


