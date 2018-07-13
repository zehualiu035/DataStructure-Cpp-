/*
 * userGraph.cpp
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/3/17
 * PA4
 * Description: This is a file used for the extension.cpp file. It determines
 * if two people are not connected by a friend.
 */

#include "userGraph.h" 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "userNode.h"
#include "unordered_set"
using namespace std;

userGraph::userGraph(void) {}
bool userGraph::isFriend(userNode* id1,userNode* id2){
	bool isfriend=false;

	vector<userNode*>::iterator friendIt = 	id1->friends.begin();
	// iterate through the vector of userNodes and check if they are already friends
	for(;friendIt!=id1->friends.end();friendIt++){
		if(*friendIt==(id2)){
			isfriend=true;
		}
	}
		return isfriend;
}


/*
 * Description: this method reads in the two columns. The first column being
 * the ID of the user, and the second ID being the ID of the friends of that
 * specific user.
 *
 * Parameters: 
 * in_filename - the name of the input file
 * use_weighted_edges - used to determine if weighted edges are to be used or not
 */
bool userGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
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

		// continue reading while stream is open
    while (ss) {
      string next;
      
        // get the next string before hitting a tab character
        // and put it in 'next'
      if (!getline( ss, next, ' ' )) { 
				break;
			}

    	record.push_back( next );
    }
    
    if (record.size() != 2) {
     	// we should have exactly 3 columns
      continue;
    }

    string id(record[0]);
    string fri(record[1]);
		unordered_map<string, userNode*>::iterator gotID = 
			userGraph::userHash.find(id);
		unordered_map<string, userNode*>::iterator gotFriend = 
			userGraph::userHash.find(fri);

		//both user and fir are not exist
		if(gotID==userGraph::userHash.end()&&gotFriend ==userGraph::userHash.end()){
			userNode* user=new userNode(id);
			userNode* ufri=new userNode(fri);
			ufri->friends.push_back(user);
			user->friends.push_back(ufri);
			userGraph::userHash.insert({id,user});
			userGraph::userHash.insert({fri,ufri});
		}

		//user exist ,friend doesnt
		else if(gotID!=userGraph::userHash.end()&&gotFriend ==userGraph::userHash.end()){
			userNode* ufri=new userNode(fri);
			ufri->friends.push_back(gotID->second);
			gotID->second->friends.push_back(ufri);
			userGraph::userHash.insert({fri,ufri});
		}

		//user doesnt exist ..friend does
		else if(gotID == userGraph::userHash.end()&&gotFriend != userGraph::userHash.end()){
			userNode* user = new userNode(id);
			user->friends.push_back(gotFriend->second);
			gotFriend->second->friends.push_back(user);
			userGraph::userHash.insert({id, user});	
		}

		//both exist
		else if(gotID != userGraph::userHash.end()&&gotFriend != userGraph::userHash.end()){
			if(!userGraph::isFriend(  gotID->second   , gotFriend->second)){
				gotFriend->second->friends.push_back(gotID->second);
				gotID->second->friends.push_back(gotFriend->second);
			}					
		}	
	}

	// check if reached EOF
	if (!infile.eof()) {
  	cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}


/*
 * Description: This is the deconstructor method. It uses the helper method
 * deleteUserNodes in order to deconstruct the graph.
 */
userGraph::~userGraph() {
	deleteUserNodes();
}

/*
 * Description: This is the helper method for the deconstructor and it iterates
 * through the graph and deletes the actorNodes. 
 */
void userGraph::deleteUserNodes() {
	unordered_map<string, userNode*>::iterator userclr = 
		userGraph::userHash.begin();

	for(;userclr!= userGraph::userHash.end();userclr++ ){
		delete userclr->second;
	}
}
