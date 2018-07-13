/*
 * Names: Mark Barnes, Zehua Liu
 * Date: 2/26/17
 * PA4
 * Description: Header file for Movie. Holds string for movie name, int for
 * year of release.
 */
#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;
class ActorNode;

/*
 * Movies have a string for title of movie, and an int for year released
 */
class Movie {

public:
	string title;			 		// The title of the movie
	int weight = 9999;		// weight of the edge
	int year;							// Year of movie release					 
 	bool isConnect=false; // Determines if node is connected
	ActorNode* preA = 0;	// A pointer to the previous actor
	std::vector<ActorNode*> actor; // The actors that act in the movie
	
	// constructor uses string for title, and int for year
	Movie(string title1,int year) : title(title1),year(year) {
		weight = 1 + (2015 - year);	
}	
};

#endif //MOVIE_H
