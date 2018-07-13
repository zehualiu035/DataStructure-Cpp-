#include<iostream>
#include<string>
#include <fstream>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include "util.h"
//Zehua Liu A92406573
using namespace std;


int main(int argc, char** argv)
{

	//Initialize words
 //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;//push word with frequency
	words.push_back("basketball");//1(99)
	words.push_back("basketballadsa");//2(98)
	words.push_back("basketballbeasf");//3
	words.push_back("basketballcgjds");//4

	words.push_back("basketballdgadfgs");//5
	words.push_back("basketballexvghhjdc");//6
	words.push_back("basketballfsewssg");//7
	words.push_back("asterisk");//8

	words.push_back("basket");//9

	words.push_back("harry jlajd");

words.push_back("harry jlajd**");

	words.push_back("harry");
	words.push_back("sriram");
	words.push_back("cse");
	words.push_back("crucio");
	words.push_back("autocomplete");
	words.push_back("cser");  
	words.push_back("hasdlahldaldhad");
	// words.push_back("");

	cout << "Inserting into Dictionaries..." << endl;



	wit = words.begin();
	wen = words.end();
	tt = dt.insert(*wit, 99);
	cout<<"auto test"<<endl;

	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}

	wit++;
	tt = dt.insert(*wit, 98);

	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}


	wit++;
	tt = dt.insert(*wit, 3);
	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}

	wit++;
	tt = dt.insert(*wit, 4);
	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}

	wit++;
	tt = dt.insert(*wit, 5);
	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}

	wit++;
	tt = dt.insert(*wit, 6);
	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}

	wit++;
	tt = dt.insert(*wit, 7);
	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}

	wit++;
	tt = dt.insert(*wit, 8);
	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}

	wit++;
	tt = dt.insert(*wit, 9);
	if(!tt)
	{
		cout << "failed for DictionaryTrie... ";
	}
	vector<string>::iterator check;
	vector<std::string> comp= dt.predictCompletions("basket",100);//get the vector with auto cmplete word
	check=comp.begin();
	dt.find("");
 cout<<""<<endl;
 cout<<"print from most frequen"<< endl;//print frequency
	for(;check!=comp.end();check++){
		cout<<*check <<endl;


	}

	cout<<"end test for auto complete"<<endl;


cout<<" "<<endl;


cout<<"DirectionaryTire should failed until harry insert"<<endl;
cout<<"all the string have special mark should failed"<<endl;


	wit = words.begin();
	wen = words.end();
	for(; wit != wen; ++wit)
	{//cout<<"here is 10"<<endl;


		cout << "Inserting: "<<*wit<<endl;

		t_bst = d_bst.insert(*wit);


		t_ht = d_ht.insert(*wit);


		tt = dt.insert(*wit, 1);
		if(!t_bst)
		{
			cout << "failed for DictionaryBST... ";
		}
		if(!t_ht)
		{
			cout << "failed for DictionaryHashset... ";
		}
		if(!tt)
		{
			cout << "failed for DictionaryTrie... ";
		}
		if(t_bst && t_ht && tt)
		{
			cout << "PASSED! :D ";
		}//cout<<"here is 9"<<endl;
		cout << endl;
	}
cout<<""<<endl;
	cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;
  cout<<"also try different frequence"<<endl;
	wit = words.begin();
	wen = words.end();



	for(; wit != wen; ++wit)
	{
		cout << "Inserting: \"" << *wit << "\"... ";
		t_bst = d_bst.insert(*wit);
		t_ht = d_ht.insert(*wit);
		tt = dt.insert(*wit, 0);//try with diffetent freq,test update
		tt = dt.insert(*wit, 2);
		tt = dt.insert(*wit, 5);
		tt = dt.insert(*wit, 8);
		if(t_bst)
		{
			cout << "failed for DictionaryBST... ";
		}
		if(t_ht)
		{
			cout << "failed for DictionaryHashset... ";
		}
		if(tt)
		{
			cout << "failed for DictionaryTrie... ";
		}
		if(!t_bst && !t_ht && !tt)
		{
			cout << "PASSED! :D ";
		}
		cout << endl;
	}

	cout << endl;



	//You are supposed to add more test cases in this file 
      //find test
	wit = words.begin();
	wen = words.end();
	for(; wit != wen; ++wit)
	{//cout<<"here is 10"<<endl;


		cout << "Find: " << *wit<<endl;

		t_bst = d_bst.find(*wit);


		t_ht = d_ht.find(*wit);

		tt = dt.find(*wit);
		if(!t_bst)
		{
			cout << "failed for DictionaryBST... ";
		}
		if(!t_ht)
		{
			cout << "failed for DictionaryHashset... ";
		}
		if(!tt)
		{
			cout << "failed for DictionaryTrie... ";
		}
		if(t_bst && t_ht && tt)
		{
			cout << "PASSED find! :D ";
		}//cout<<"here is 9"<<endl;
		cout << endl;
	}
//load dictionary case
 
 
 
 
 
 cout<< "test auto "<<endl;
 	ifstream in;//open file
	in.open("shuffled_unique_freq_dict.txt");
	
		if(!in.is_open()) //check vaild
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }

		in.seekg(0, ios_base::beg);
 
   DictionaryTrie dt2;
 Utils::load_dict(dt2, in);
 	vector<string>::iterator check2;
 	vector<std::string> comp1= dt2.predictCompletions("b",100);//test b 100
 	check2=comp1.begin();//check2 is the beginning of comp
	
 cout<<""<<endl;
 cout<<"print from most frequency"<< endl;//print frequency
	for(;check2!=comp1.end();check2++){
		cout<<*check2 <<endl;


	}
 
	return 0;
}
