/*
 * actorconnections.cpp
 * Author: Mark Barnes, Zehua Liu
 * Date:   3/3/17
 *
 * This actorconnections files is used to do either a BFS or union find. 
 */
//#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
#include "unordered_set"
#include <queue>
#include <stack>
using namespace std;

int main (int argc, char* argv[]){

	// The number of arguments should be 5
	if(argc !=5){
		cout<<"wrong input"<<endl;
		return -1;	
	}

	string uorb=argv[4];
	
	// makes sure desired search is either bfs or ufind
	if(uorb!="bfs"&&uorb!="ufind"){
		cout<<"last argument should be either 'bfs' or 'ufind'"<<endl;return -1;
	}

	ActorGraph graph;
	bool isMake=graph.loadFromFile(argv[1],false);
		
	// checks if the graph failed to make
	if(isMake==false) {
		cout<<"fail to make graph"<<endl;
		return -1;
	}
	
	string start;
	ifstream inpair;
	ofstream out;
	inpair.open(argv[2]);

	// makes sure the files are open and ready for reading/writing
	if(!inpair.is_open()){cout<<"fail to open input"<<endl;}
	out.open(argv[3]);
	if(!out.is_open()){cout<<"fail to open out fail"<<endl;}
	bool have_header = false;
	
	// output the header to the file
	out<<"Actor1\tActor2\tYear\n";

	// continue to loop until EOF
	while (inpair) {
		string s;

		// get the next line
   	 if (!getline( inpair, s )) { 
			break;
		}

		// checks if file has header
    if (!have_header) {
    	// skip the header
      have_header = true;
      continue;
    }

		istringstream ss( s );
		vector <string> record;

		// continue to read while stream is open
		while (ss) {
			string next;

			// get the next string before hitting a tab character and put in 'next'
			if (!getline( ss, next, '\t' )) {
				break;
			}

			record.push_back( next );
		}

		if (record.size() != 2) {
			// we should have exactly 2 columns
			continue;
		}

		bool done =false;
		string actor1(record[0]);
		start=actor1;
		string actor2(record[1]);
	
		// When we are doing a BFS
		if(uorb=="bfs") {
 		//	priority_queue<Movie*, vector<Movie*>,MovieComp> copypq=graph.moviePQ;
			vector<Movie*>resetM; 
			while(graph.moviePQ.size()!=0){
				Movie* curM=graph.moviePQ.top();
				while(graph.moviePQ.top()->year==curM->year&&graph.moviePQ.size()>0){
					Movie* curM=graph.moviePQ.top();
					graph.moviePQ.pop();
					curM->isConnect=true;
   				resetM.push_back(curM);
				}

				// when the path has been used
				if(graph.BFS(actor1,actor2,curM->year)!=9999){
					out<<actor1;
					out<<"\t";
					out<<actor2;
					out<<"\t";
					out<<curM->year;
					out<<"\n";
					done =true;	
					break;
				}
 			}

			// checks if we have explored an edge
			if(done){
				vector<Movie*>::iterator movieIt=resetM.begin();
				// reset the nodes and their connection
				for(;movieIt!=resetM.end();movieIt++){
					(*movieIt)->isConnect=false;
          graph.moviePQ.push((*movieIt));
				}
			}

			if(done=false) {
				out<<actor1;
				out<<"\t";
				out<<actor2;
				out<<"\t";
				out<<9999;
				out<<"\n";	
				vector<Movie*>::iterator movieIt=resetM.begin();
				// reset the nodes and their connection
				for(;movieIt!=resetM.end();movieIt++){
					(*movieIt)->isConnect=false;
        	graph.moviePQ.push((*movieIt));
				}
			}
		}
 		
		// When we are doing a union find
		else if(uorb=="ufind"){
			priority_queue<Movie*, vector<Movie*>,MovieComp> copyPQ=graph.moviePQ; 
			
			// Continue while all the nodes have not been seen
			vector<Movie*>resetM; 
			while(copyPQ.size()!=0){
				Movie* curM=copyPQ.top();
				while(copyPQ.top()->year==curM->year&&copyPQ.size()>0){
					Movie* curM=copyPQ.top();
					graph.unite(curM);
					copyPQ.pop();
				}
				// if successful union find
				if(graph.ufind(actor1,actor2)==1){
					out<<actor1;
					out<<"\t";
					out<<actor2;
					out<<"\t";
					out<<curM->year;
					out<<"\n";
					done =true;	
					break;
				}
 			}

			if(done){
					unordered_map<string, ActorNode*>::iterator actclr = 
						graph.actorsHash.begin();
					// Reset the pointers		
					for(;actclr!= graph.actorsHash.end();actclr++ ){
						actclr->second->parent=0;
					}
				//	break;		
			}
			
			// case when node was not visited 
			if(done = false){
				out<<actor1;
				out<<"\t";
				out<<actor2;
				out<<"\t";
				out<<9999;
				out<<"\n";

				unordered_map<string, ActorNode*>::iterator actclr = 
						graph.actorsHash.begin();
					
					// Reset the parent pointers
					for(;actclr!= graph.actorsHash.end();actclr++ ){
						actclr->second->parent=0;
					}
			}						
		}
	}

	return 1;
}
