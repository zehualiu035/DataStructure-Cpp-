/*
 * userGraph.h
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/3/17
 * PA4
 * 
 * Description: This is the header file used for userGraph.cpp. This file
 * includes method headers for loading info from file, deleting graph, and
 * checking if two nodes are connected by a friend.
 */
#ifndef USERGRAPH_H
#define USERGRAPH_H

#include <iostream>
#include "userNode.h"
#include <unordered_map>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

class userGraph {
public:
  userGraph(void);
	~userGraph();
	unordered_map<string, userNode*> userHash;
	bool loadFromFile(const char* in_filename, bool use_weighted_edges);
	bool isFriend(userNode* id1,userNode* id2);
	void deleteUserNodes();
};
#endif

