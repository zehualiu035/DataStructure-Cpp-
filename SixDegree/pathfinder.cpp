/*
 * pathfinder.cpp
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/3/17
 * PA4
 *
 * Description: This file was used for the checkpoint. It has method that
 * checks for the best weigthed and unweighted path. 
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
#include <queue>
#include <stack>
using namespace std;

/*
 * Description: Determines the best weighted path from one actor to another
 */
int pathFinderW (int argc, char* argv[]){
	if(argc !=5){
		cout<<"wrong input"<<endl;
		return -1;	
	}
	
	string uorw=argv[2];
	ActorGraph graph;
	bool isMake=graph.loadFromFile(argv[1],false);
	
	if(isMake==false){cout<<"fail to make graph"<<endl;return -1;}

	string start;
	ifstream inpair;
	ofstream out;
	inpair.open(argv[3]);
	if(!inpair.is_open()){cout<<"fail to open input"<<endl;}
	out.open(argv[4]);
	if(!out.is_open()){cout<<"fail to open out fail"<<endl;}
	bool have_header = false;

	out<<"(actor)--[movie#@year]-->(actor)--...\n";

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
		
		while (ss) {
			string next;

			// get the next string before hitting a tab character and put in 'next'
			if (!getline( ss, next, '\t' )) break;
	
			record.push_back( next );
		}
		
		if (record.size() != 2) {
			// we should have exactly 3 columns
			continue;
		}

		string actor1(record[0]);
		start=actor1;
		string actor2(record[1]);
		unordered_map<string,ActorNode*>::iterator gotActor2 = 
			graph.actorsHash.find(actor2);
	
		// run dijkstra's algorithm using the helper function
		graph.dijkstra(actor1, actor2);
		ActorNode* back = (gotActor2->second);
		string end=back->name;
		stack<string> path;
		
		// while not back at the beggining
		while(back->name.compare(start)!=0) {
			path.push(back->name);
			path.push(back->preM->title);	
			back=back->preM->preA;
		}	
		
		// print out the values to the out file
		out<<"("<<start<<")";
		while(path.size()>0){
			out<<"--[";
			out<<path.top();
			out<<"]-->(";
			path.pop();
			out<<path.top();
			out<<")";
			path.pop();
		}

		out<<"\n";	
	}

	return 1;
}

/*
 * The main method for pathfinder
 */
int main (int argc, char* argv[]){

	// check that the number of arguments passed in is the correct number
	if(argc !=5){
		cout<<"wrong input"<<endl;
		return -1;	
	}

	string uorw=argv[2];
	if(uorw!="w"&&uorw!="u"){cout<<"wrong input"<<endl;return -1;}
	if(uorw=="w"){pathFinderW(argc, argv); return 1;}
	ActorGraph graph;
	bool isMake=graph.loadFromFile(argv[1],false);
	
	if(isMake==false){cout<<"fail to make graph"<<endl;return -1;}

	
	string start;
	ifstream inpair;
	ofstream out;
	inpair.open(argv[3]);
	if(!inpair.is_open()){cout<<"fail to open input"<<endl;}
	out.open(argv[4]);
	if(!out.is_open()){cout<<"fail to open out fail"<<endl;}
	bool have_header = false;

	out<<"(actor)--[movie#@year]-->(actor)--...\n";

	// continue to loop while the stream is open
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
		
		// while stream is open continue through
		while (ss) {
			string next;

			// get the next string before hitting a tab character and put in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		// we should have exactly 3 columns
		if (record.size() != 2) {
			continue;
		}

		string actor1(record[0]);
		start=actor1;
		string actor2(record[1]);
	
		
		graph.setPBFS(actor1,actor2);
		unordered_map<string,ActorNode*>::iterator target2 = 
			graph.actorsHash.find(actor2);
		unordered_map<string,ActorNode*>::iterator target1 = 
			graph.actorsHash.find(actor1);
		ActorNode* back = (target2->second);
		start = target1->second->name;
		string end = back->name;
		stack<string> path;
		
		// set the best route, check if we are back at the beggining
		while(back->name.compare(start)!=0){
			path.push(back->name);
			path.push(back->preM->title);
			back = back->preM->preA;
		}	

		// output the path to the out file
		out<<"("<<start<<")";
		while(path.size()>0){
			out<<"--[";
			out<<path.top();
			out<<"]-->(";
			path.pop();
			out<<path.top();
			out<<")";
			path.pop();
		}
		out<<"\n";	
	}

	return 1;
}



