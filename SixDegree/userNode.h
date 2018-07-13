/*
 * userNode.h
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/3/17
 * PA4
 * Description: This is the header file for userNode. The userNode is a
 * person who has an ID, and has friends who are also identifiable via ID.
 */

#ifndef USERNODE_H
#define USERNODE_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;
class userNode{
public:
	string id;
	vector<userNode*> friends;
	userNode(string id) : id(id){}

};
#endif
