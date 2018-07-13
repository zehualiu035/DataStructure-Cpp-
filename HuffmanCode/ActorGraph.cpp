/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
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
				cout << "movie_name is: " << movie_name << endl;

				unordered_map<string, ActorNode*>::iterator gotActor = 
					ActorGraph::actorsHash.find(actor_name);
				unordered_map<string, Movie*>::iterator gotMovie = 
					ActorGraph::moviesHash.find(movie_name);
	
				// Case: root node, or independent node case
				if(gotActor == ActorGraph::actorsHash.end() 
					&& gotMovie == ActorGraph::moviesHash.end()) {
cout<<"case1"<<endl;
					ActorNode* tmp = new ActorNode(actor_name);
					Movie* mov = new Movie(movie_name,movie_title, movie_year);
					ActorGraph::numOfActor++;
					ActorGraph::numOfMovie++;

					tmp->movies.push_back(mov);
					mov->actor.push_back(tmp);//
					ActorGraph::actorsHash.insert({actor_name, tmp}); // first key, second is real object/val
					ActorGraph::moviesHash.insert({movie_name, mov});
				}
				// Case: actor does not exist yet, but the movie does exist
				else if (gotActor == ActorGraph::actorsHash.end() && gotMovie != ActorGraph::moviesHash.end()) {
					cout<<"case2"<<endl;
          ActorNode *tmp = new ActorNode(actor_name);
					tmp->movies.push_back(gotMovie->second);//
					gotMovie->second->actor.push_back(tmp);
					ActorGraph::actorsHash.insert({actor_name, tmp});
					ActorGraph::numOfEdge++;
					ActorGraph::numOfActor++;
				}
				// Case: actor does exist, is possible movie does not exist.
				else if (gotActor != ActorGraph::actorsHash.end() && gotMovie == ActorGraph::moviesHash.end()) {
					cout << "Actor does exist and Movie does not" << endl;
          	Movie* mov = new Movie(movie_name,movie_title, movie_year);
           gotActor->second->movies.push_back(mov);
           mov->actor.push_back(gotActor->second);//
       	ActorGraph::moviesHash.insert({movie_name, mov});
					ActorGraph::numOfMovie++;
          ActorGraph::numOfActor++;
					//ActorGraph::numOfEdge++; // should the number of edges increase too?
				}
				// Case: Movie and Actor exist
				else {// may casue loop
					cout << "Movie and Actor already exist" << endl;
					
						
						cout<<"act is "<<((gotActor->second))->name<<endl;
						cout<<"mov is "<<((gotMovie->second))->title<<endl;
					gotActor->second->movies.push_back(gotMovie->second);//
					gotMovie->second->actor.push_back(gotActor->second);
					ActorGraph::numOfEdge++;
				}			
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
