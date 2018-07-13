/*
 * ActorGraph.cpp
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/3/17
 *
 * This file is meant to exist as a container for starter code that you can 
 * use to read the input file format defined in movie_casts.tsv. 
 * Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
#include "ActorNode.h"
#include "Movie.h"
#include "unordered_set"
using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {

    // Initialize the file stream
  	ifstream infile(in_filename);
    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
    	string s;
    
    	// get the next line
      if (!getline( infile, s )) break;

      if (!have_header) {
      	// skip the header
        have_header = true;
        continue;
      }

      istringstream ss( s );
      vector <string> record;

      while (ss) {
      	string next;
      
        // get the next string before hitting a tab character
        // and put it in 'next'
        if (!getline( ss, next, '\t' )) break;

        record.push_back( next );
      }
    
      if (record.size() != 3) {
      	// we should have exactly 3 columns
        continue;
      }

      string actor_name(record[0]);
      string movie_title(record[1]);
      int movie_year = stoi(record[2]);
    
      // we have an actor/movie relationship, now what?
        
			// locate node with actor name
			// add movie title to the actor's movies vector
			// add the movie year to the actor's mYear vector
	

			string movie_name = movie_title +"#@"+ to_string(movie_year);

			unordered_map<string, ActorNode*>::iterator gotActor = 
				ActorGraph::actorsHash.find(actor_name);
			unordered_map<string, Movie*>::iterator gotMovie = 
				ActorGraph::moviesHash.find(movie_name);
	
			// Case: root node, or independent node case
			if(gotActor == ActorGraph::actorsHash.end() 
					&& gotMovie == ActorGraph::moviesHash.end()) {
				//Create two nodes
				ActorNode* tmp = new ActorNode(actor_name);
				Movie* mov = new Movie(movie_name, movie_year);
				ActorGraph::numOfActor++;
				ActorGraph::numOfMovie++;
				ActorGraph::moviePQ.push(mov);

				// push nodes into eachother's Movie*/Actor* vectors
				tmp->movies.push_back(mov);
				mov->actor.push_back(tmp);

				// insert into the unordered_map
				ActorGraph::actorsHash.insert({actor_name, tmp}); 
				ActorGraph::moviesHash.insert({movie_name, mov});
			}

			// Case: actor does not exist yet, but the movie does exist
			else if (gotActor == ActorGraph::actorsHash.end() 
								&& gotMovie != ActorGraph::moviesHash.end()) {
				// create a new actor node and push into Movie's Actor vect
        ActorNode *tmp = new ActorNode(actor_name);
				tmp->movies.push_back(gotMovie->second);
				gotMovie->second->actor.push_back(tmp);
				ActorGraph::actorsHash.insert({actor_name, tmp});

				// Tracks edges and actors
				ActorGraph::numOfEdge++;
				ActorGraph::numOfActor++;
			}
			// Case: actor does exist, is possible movie does not exist.
			else if (gotActor != ActorGraph::actorsHash.end() 
								&& gotMovie == ActorGraph::moviesHash.end()) {

				//create new Movie node
        Movie* mov = new Movie(movie_name, movie_year);
				ActorGraph::moviePQ.push(mov);
		
				// push movie into Actor's movie vector
        gotActor->second->movies.push_back(mov);
        mov->actor.push_back(gotActor->second);
       	ActorGraph::moviesHash.insert({movie_name, mov});
				ActorGraph::numOfMovie++;
        ActorGraph::numOfActor++;
			}

			// Case: Movie and Actor exist
			else {
				gotActor->second->movies.push_back(gotMovie->second);
				gotMovie->second->actor.push_back(gotActor->second);
			//	ActorGraph::numOfEdge++;
			}			
    }
		
		// EOF check
    if (!infile.eof()) {
    	cerr << "Failed to read " << in_filename << "!\n";
      return false;
    }

    infile.close();

    return true;
}

/*
 * Description: The purpose of this function is for unweighted graph for
 * the checkpoint.
 *
 * actor1 - the starting actor's name
 * actor2 - the end of path actor's name
 *
 * return false if failed to set pointers from movies to actors
 */
int ActorGraph::setPBFS(string actor1,string actor2){
	vector<Movie*>::iterator movieIt;
	vector<ActorNode*>::iterator actIt;

	unordered_map<string,ActorNode*>::iterator gotActor1 = 
		ActorGraph::actorsHash.find(actor1);
	unordered_map<string,ActorNode*>::iterator gotActor2 = 
		ActorGraph::actorsHash.find(actor2);
		
	// Checks if the actors do not exist in the graph
	if(gotActor1==ActorGraph::actorsHash.end()||gotActor2==ActorGraph::actorsHash.end()){
		return false;
	}
	
	unordered_map<string,ActorNode*> check; 
	unordered_map<string,Movie*> checkM;
	queue<ActorNode*> q;
	bool isFind=false;
	
	// push the first node into the queue, and start BFS
	q.push(gotActor1->second);
	while(!q.empty()){
		ActorNode* cur=q.front();
		q.pop();
		movieIt=cur->movies.begin();
		// Iterate through the actors movies
		for(;movieIt!=(cur->movies.end());movieIt++){
			actIt=(*movieIt)-> actor.begin();
			// checks if movie already exists. Sets preA of the movie
			if(checkM.find((*movieIt)->title)==checkM.end()){
				(*movieIt)->preA=cur;
				checkM.insert({(*movieIt)->title,(*movieIt)});
			}
      else continue;
			
			// Iterate through the actors in the movie
			for(;actIt!=(*movieIt)->actor.end();actIt++){
				// dont go back to the same node thats already being visited
				if((*actIt==cur)||((*actIt)==gotActor1->second)){
					check.insert({(*actIt)->name,(*actIt)});
					continue;
				}
				// If curr does not exist, then first time we see the node and insert
				if(check.find((*actIt)->name) == check.end()){					
					(*actIt)->preM = (*movieIt);
					check.insert({(*actIt)->name,(*actIt)});
        				q.push(*actIt);
					if((*actIt)->name.compare(actor2)==0){
						isFind=true;
					}
				}
				// not the first time that we find the node
				else {
					// checks if actors preM year is less than new movie's year.                                                                 
					if((check.find((*actIt)->name)->second)->preM->year < 
							((*movieIt)->year) &&(*actIt)->preM->preA == cur) {
          	(*actIt)->preM=(*movieIt);	
					}
				}		
			}
		}
		if(isFind){
			break;
		}
	}
}


/*
 * Description: This method implements the dijkstra algorithm where the edges
 * are weighted. The path between two actors that has the least weight, is
 * the best path.
 *
 * Parameters: 
 * actor1 - The starting actor
 * actor2 - The actor at the end of the path
 * 
 * Return: Returns an int indicating the success of insertion
 */
int  ActorGraph::dijkstra(string actor1,string actor2){
	unordered_map<string,ActorNode*>::iterator gotActor1 = 
		ActorGraph::actorsHash.find(actor1);
	unordered_map<string,ActorNode*>::iterator gotActor2 = 
		ActorGraph::actorsHash.find(actor2);

	// Checks if the actor exist, or if they are not found in the graph
	if(gotActor1==ActorGraph::actorsHash.end()||gotActor2==ActorGraph::actorsHash.end()){
		return false;
	}
	
	vector<Movie*>::iterator movieIt;
	vector<ActorNode*>::iterator actIt;
	vector<ActorNode*> resetA;
	priority_queue<ActorNode*, vector<ActorNode*>,NodeComp> actorPQ; 
	
	// Sets the actor dist to 0
	((gotActor1->second)->dist) = 0;
	actorPQ.push((gotActor1->second));

	// Do a dijkstra search through the nodes
	while(actorPQ.size() != 0) {
		ActorNode* tmpAct = actorPQ.top();
		actorPQ.pop();
		resetA.push_back(tmpAct);	

		// checks if the actor has been visited before
		if(tmpAct->done == false) {
			tmpAct->done = true;
			vector<Movie*>::iterator movieIt = tmpAct->movies.begin();

			// iterates through the movies
			for(;movieIt!=(tmpAct->movies.end());movieIt++){
				actIt=(*movieIt)-> actor.begin();
			
				// iterates through the actors of the movie above
				for(;actIt!=(*movieIt)->actor.end();actIt++){
					int c;
					c = tmpAct->dist + (*movieIt)->weight;
					// check if the new distance is less than the previous one	
					if(c < (*actIt)->dist) {
						(*actIt)->dist = c;
						(*actIt)->preM= *movieIt;
						(*movieIt)->preA= tmpAct;
						actorPQ.push(*actIt);
					}
				}
			}
		}
	}
	
	//  Reset the values in the nodes	for future use
	actIt=resetA.begin();
	for(;actIt!=resetA.end();actIt++){
		(*actIt)->dist=9999;
		(*actIt)->done=false;
	}
}

	
/*
 * Description: This method does a BFS through the tree and checks if an edge
 * already exists between two nodes. If an edge already does exist, then dont
 * add a new one. This BFS is for the isConnect function.
 *
 * Parameters:
 * actor1 - the name of the start actor
 * actor2 - the name of the end of path actor
 *
 * return: returns an int indicating failure of insertion or the year of the
 * newest movie is in the path between the two actors. 
 */ 
int  ActorGraph::BFS(string actor1,string actor2,int thisyear){		
	int connectyear=9999;
	vector<Movie*>::iterator movieIt;
	vector<ActorNode*>::iterator actIt;

	unordered_map<string,ActorNode*>::iterator gotActor1 = 
		ActorGraph::actorsHash.find(actor1);
	unordered_map<string,ActorNode*>::iterator gotActor2 = 
		ActorGraph::actorsHash.find(actor2);
	
	// Checks if the actors exist in the graph or not
	if(gotActor1==ActorGraph::actorsHash.end()||gotActor2==ActorGraph::actorsHash.end()){
		return false;
	}
	
	unordered_map<string,ActorNode*> check; 
	unordered_map<string,Movie*> checkM;
	queue<ActorNode*> q;
	bool isFind=false;
	q.push(gotActor1->second);

	// Do a BFS through the graph
	while(!q.empty()){
		ActorNode* cur=q.front();
		q.pop();
		movieIt=cur->movies.begin();
	// Iterate through each movie in the Actor's Movie* vector
		for(;movieIt!=(cur->movies.end());movieIt++){
			// check if the movie is connected in graph yet
			if((*movieIt)->isConnect==false){
continue;}
						actIt=(*movieIt)-> actor.begin();
			// check if the Movie exists in the graph
			if(checkM.find((*movieIt)->title)==checkM.end()){
				checkM.insert({(*movieIt)->title,(*movieIt)});
			}
      else {
		continue;}		
			// for each Movie in the cur Actor, go through its vector of Actor*
			for(;actIt!=(*movieIt)->actor.end();actIt++){
				// check if the act exists, if so then skip
				if((*actIt==cur)){
					check.insert({(*actIt)->name,(*actIt)});
					continue;
				}
				// check if the actor does not exist, then push to check list
				if(check.find((*actIt)->name) == check.end()){
					check.insert({(*actIt)->name,(*actIt)});
        	q.push(*actIt);
					// the names are the same, so found the target Node
					if((*actIt)->name.compare(actor2)==0){
						isFind=true;
						connectyear=thisyear;
						break;
					}
				}				
			}
			if(isFind){
				break;
			}
		}
		if(isFind){
			break;
		}
	}

	return connectyear;			
}

/*
 * Description: This is a helper method used by uFind. It iterates through all
 * of the nodes until it reaches one node without a parent. This is the root
 * node, and it is returned. 
 */
ActorNode* ActorGraph::findRoot(ActorNode* node){
	// iterate until root
	while((node->parent)!=0){
		node=node->parent;
	}
	return node;
}


/*
 * The purpose of this method is to create a connection between the actors.
 * This method is used by disjoint set. It has the smaller set pointing to 
 * the larger set
 */
int  ActorGraph::unite(Movie* curM){
vector<ActorNode*>::iterator actIt;
	actIt=curM->actor.begin();
	ActorNode* curR= findRoot(*actIt);
	
	// iterate through the actor's movie vector of Actor*s	
	for(;actIt!=curM->actor.end();actIt++){
		ActorNode* temp=findRoot(*actIt);	
		if(curR!=temp){
			// if greater than temps size
			if((curR->size)>(temp->size)){
			temp->parent=curR;
				(curR->size)+=(temp->size);
				}
			// for when less than or equal to the tmps size
			else if((curR->size)<=(temp->size)){
				curR->parent=temp;
				temp->size+=curR->size;
				curR=temp;
				}

		}
	}	

}
 			

/*
 * Description: This uses the disjoint set to set the pointers to the root node.
 * We iterate to the root using the parent pointers, until the root no longer
 * has a parent pointer. 
 *
 * Parameters:
 * actor1 - the name of the start actor
 * actor2 - the name of the end of path actor
 *
 * return - one if success, 0 if failed
 */
int  ActorGraph::ufind(string actor1,string actor2){
	//make connection first
 	unordered_map<string, ActorNode*>::iterator gotActor1 = 
		ActorGraph::actorsHash.find(actor1);
	unordered_map<string,ActorNode*>::iterator gotActor2 = 
		ActorGraph::actorsHash.find(actor2);

	// checks if the root is the same, for disjoint set. Already connected
	if(findRoot(gotActor1->second) == findRoot(gotActor2->second)){
		return 1;
	}
	else {
		return false;
	}
}

/*
 * This is the destructor for the ActorGraph. It uses the helper method
 * deleteActNodes in order to delete.
 */
ActorGraph::~ActorGraph() {
	deleteActNodes();
}

/*
 * This is the helper method for the destructor, and it iterates through the
 * actors and movies, and deletes them.
 */
void ActorGraph::deleteActNodes() {
	// create two iterators, one for movie and one for actors
	unordered_map<string, ActorNode*>::iterator actclr = 
		ActorGraph::actorsHash.begin();
	unordered_map<string, Movie*>::iterator movclr = 
		ActorGraph::moviesHash.begin();

	// iterate through each of the actors and movies and delete
	for(;actclr!= ActorGraph::actorsHash.end();actclr++ ){
		delete actclr->second;
	}
		
	for(;movclr!= ActorGraph::moviesHash.end();movclr++ ){
		delete movclr->second;
	}
}

