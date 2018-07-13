#include <iostream>
#include <fstream>
#include <string>
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include "DictionaryTrie.h"
#include "util.h"
//Zehua Liu A92406573
using namespace std;

int main(int argc, char* argv[]){

	int min_size;
	int step_size;
	int num_iterations;

	if (argc!=5){//check vaild
		cout<<"invaild input,wrong number"<<endl;
		return -1;
	}
	//set value

	min_size = stoi(argv[1], 0, 10);
	step_size = stoi(argv[2], 0, 10);
	num_iterations = stoi(argv[3], 0, 10);
	ifstream in;//open file
	in.open(argv[4]);

	if(!in.is_open()) //check vaild
	{
		cout<< "Invalid input file. No file was opened. Please try again.\n";
		return -1;
	}

	in.seekg(0, ios_base::beg);



	Utils utils;
	Timer timer;

	long  time=0;
	long  average_time=0;



	cout << "DictionaryTrie\n";
	for(int i = 0; i < num_iterations; i++){
		in.seekg(0, ios_base::beg);
		DictionaryTrie trie;
		utils.load_dict(trie, in, min_size + i * step_size);//load file
		vector<string> words1;
		utils.load_vector(words1, in, 100);	


		time = 0;timer.begin_timer();
		for(int j=0;j<5;j++){

			for(int i = 0; i < 100; i++){//is this success find?
				trie.find(words1[i]);//found sth is not in this file
				//trie.find("no this word will be found");
			}

		}
		time =  timer.end_timer();//set time
		average_time = time / 5;//get avg
		cout << min_size + i * step_size << '\t' 
			<< average_time << endl;
	}

	cout << "\n";


	//for bst

	cout << "DictionaryBST\n";

	for(int i = 0; i < num_iterations; i++){
		in.seekg(0, ios_base::beg);//clear the in
		DictionaryBST bst;
		utils.load_dict(bst, in, min_size + i * step_size);
		vector<string> words;
		utils.load_vector(words, in, 100);

		time = 0;timer.begin_timer();//count time
		for(int j=0;j<5;j++){


			for(int i = 0; i < 100; i++){
				//	bst.find("no this word will be found");
				bst.find(words[i]);
			}	



		}time = timer.end_timer();
		average_time = time / 5;//get avg
		cout << min_size + i * step_size << '\t' 
			<< average_time << endl;
	}

	cout << "\n";//for hash

	cout <<  "DictionaryHashtable\n";

	for(int i = 0; i < num_iterations; i++){
		in.seekg(0, ios_base::beg);//clear the in
		DictionaryHashtable hash;
		utils.load_dict(hash, in, min_size + i * step_size);//load file
		vector<string> words2;
		utils.load_vector(words2, in, 100);

		time = 0;//count time
		timer.begin_timer();
		for(int j=0;j<20;j++){

			for(int i = 0; i < 100; i++){//unsuccessful find
				hash.find(words2[i]);
				//hash.find("no this word will be found");
			}

		}
		time =timer.end_timer();
		average_time = time / 20;//get more ave so I set it to 20
		cout << min_size + i * step_size << '\t' 
			<< average_time << endl;
	}

	return 0;
}
