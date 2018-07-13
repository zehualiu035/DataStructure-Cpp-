/*
 * extension.cpp
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/3/17
 *
 * This file is for the extension part of the program. The purpose of this file
 * is to take facebook user IDs and determine if two people are not linked by a
 * common friend. 
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "userGraph.h"
#include "userNode.h"
#include "unordered_set"
#include <queue>
#include <stack>
using namespace std;

int main (int argc, char* argv[]){

	// checks that the correct number of arguments were included
	if(argc !=4){
		cout<<"wrong input"<<endl;
		return -1;	
	}

	userGraph graph;
	bool isMake = graph.loadFromFile(argv[1],false);
	
	// checks if the graph was successfully constructed
	if(isMake==false){cout<<"fail to make graph"<<endl;return -1;}
	
	string start;
	ifstream inpair;
	ofstream out;
	inpair.open(argv[2]);

	// checks that the input and output files were successfully created
	if(!inpair.is_open()){cout<<"fail to open input"<<endl;}
	out.open(argv[3]);
	if(!out.is_open()){cout<<"fail to open out fail"<<endl;}

	bool have_header = false;

	// Continue to loop while reading the file	
	while (inpair) {
		string s;

		// get the next line
		if (!getline( inpair, s )) break;

		if (!have_header) {
			// skip the header
			have_header = true;
			continue;
		}
	
		istringstream ss( s );
		vector <string> record;
		
		// while the stream is open continue to read
		while (ss) {
			string next;

			// get the next string before hitting a tab character and put in 'next'
			if (!getline( ss, next, ' ' )) { 
				break;
			}

			record.push_back( next );
		}

		// we should have exactly 3 columns
		if (record.size() != 2) {
			continue;
		}

		string id1(record[0]);
		string id2(record[1]);
		unordered_map<string, userNode*>::iterator gotID1 = graph.userHash.find(id1);
		unordered_map<string, userNode*>::iterator gotID2 = graph.userHash.find(id2);

		// checks that boths of the actors exist in the graph
		if(gotID1==graph.userHash.end()||gotID2==graph.userHash.end()){
			if(gotID1==graph.userHash.end()){
				cout<<"id1 doesnt exist"<<endl;
			}
			else if(gotID2==graph.userHash.end()) {
				cout<<"id2 doesnt exist "<<id2<<endl;
			}
			return false;
		}

		vector <userNode*> friend1;
		vector<userNode*>::iterator friIt = gotID1->second->friends.begin();
		
		// Iterates through the friends
		for(;friIt!=gotID1->second->friends.end();friIt++){
			// Make sure we are continuing forward, and not visiting old node
			if(*friIt==gotID1->second){continue;}	
				friend1.push_back(*friIt);
		}

		vector <string> canConnect;
		vector<userNode*>::iterator friend1It = friend1.begin();
		
		// Iterate through the friend and check if the two can connect
		for(;friend1It!=friend1.end();friend1It++) {
			if(graph.isFriend(*friend1It,gotID2->second)){
					canConnect.push_back((*friend1It)->id);
			}
		}
		
		// If the two can connect, and are not identified as friends then make
		// make a connection between the two nodes
		if(canConnect.size()!=0&&(!graph.isFriend(gotID1->second,gotID2->second))){
			out<<"USER "<< id1<<" have common friend(s): ";
			vector<string>::iterator sIt = canConnect.begin();
			for(;sIt!=canConnect.end();sIt++){
				out<<*sIt<<" ";
			}
			out<<" with USER " << id2<<"\n";
		}
		// If the two are not friends, and do not have have a friend that both share
		else if(canConnect.size()==0&&(!graph.isFriend(gotID1->second,gotID2->second))) {	
			out<<"USER "<< id1<<" does not have a common friend with USER "<<id2<<"\n";																
		}
		// User and friend are already identified as friends
		else if((graph.isFriend(gotID1->second,gotID2->second))){
			out<<"USER "<< id1<<" is already friends with USER "<<id2<<"\n";													
		}
	}
}
