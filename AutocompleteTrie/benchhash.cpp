#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <unordered_set>
#include <fstream>
#include <stdint.h>
#include <sstream>
using namespace std;	
//Zehua Liu A92406573
int hash1 (string word,int size)   //first hash always return 1

{      
	return  1;
}
//second hash ,can calculate the index
int hash2 (string word,int size)
{
	int seed = 131; 
	unsigned long hash2 = 0;
	for(unsigned int i = 0; i < word.length(); i++)
	{
		hash2 = (hash2 * seed) + word[i];
	}
	return hash2 % size;//in correct range
}

float addup(long sum){
	return (sum+1)*sum/2;
//add up sum
}


//get rid of frequence
unsigned int stripFrequency(string& line)
{
	// Count the number of characters past the first space
	int count = 0;
	string::iterator last = line.end();
	for (string::iterator it = line.begin(); it != last; ++it) {
		count++;
		if (*it == ' ') {
			break;
		}
	}
	unsigned int freq = std::stoi(line.substr(0, count));

	line.erase(0, count);


	return freq;
}

int main(int argc, char* argv[]){
	unsigned int num_words;

	if (argc!=3){
		cout<<"invaild input,wrong number"<<endl;
		return -1;
	}//set value

	num_words= stoul(argv[2], 0, 10);
	ifstream in;//open file
	in.open(argv[1]);
	//check open
	if(!in.is_open()) 
	{
		cout<< "Invalid input file. No file was opened. Please try again.\n";
		return -1;
	}
	string s;
	//clear in
	in.seekg(0, ios_base::beg);
	int hashSize= 2*num_words;
	int h1[hashSize];//create array
	int h2[hashSize];
	for(int i=0;i<hashSize;i++){
		h1[i]=0;
		h2[i]=0;
	}
	int testsize=2000;//test the hash is correct
	int otest1;int otest2;int otest3;
	int ttest1;int ttest2;int ttest3;
	otest1=hash1("a",testsize);otest2=hash1("bc",testsize);otest3=hash1("cse",testsize);
	ttest1=hash2("a",testsize);ttest2=hash2("bc",testsize);ttest3=hash2("cse",testsize);
	cout<<"test for insert hash1,test case a,bc,cse , it should all be 1"<<endl;
	cout<<"case insert a "<<otest1<<endl;
	cout<<"caseinsert bc "<<otest2<<endl;
	cout<<"caseinsert cse "<<otest3<<endl;


	cout<<"test for insert hash2,test case a,bc,cse , it should be 97 ,937,105 calculate by hand"<<endl;
	cout<<"case insert a "<<ttest1<<endl;
	cout<<"case insert bc "<<ttest2<<endl;
	cout<<"case insert cse "<<ttest3<<endl;//compare it with my answer

	int index1;
	int index2;
	int counter=num_words;
	float ave=0;
	while ( counter )
	{
		getline(in,s);//get line
		if (in.eof()) break;//check empty
		stripFrequency(s);
		index1=hash1(s,hashSize);//get the index to hash
		index2=hash2(s,hashSize);
		h1[index1]++;
		h2[index2]++;
		counter=counter-1;
	}  
	in.close();
	//analyse 
	cout<<"Printing the statistics for hashFunction1 with hash table size "<<hashSize<<endl;
	cout<<"#hits    #slots receiving the #hits"<<endl;
	int num=0;//slot number
	float sum=0;

	int worst=0;
	for(int i =0; i<hashSize;i++){//every possible hit number
		num=0;//count slot,i is for count hits
		for (int n=0;n<hashSize;n++){//find num slot

			if((h1[n])==i){
				num++;
			}

		}
		if(num!=0){sum=sum+addup(i)*num;cout <<i<<"       "<<num<<endl;worst=i;}

	}
	ave=sum/num_words;
	cout<<"The average number of steps for a successful search for hash function 1 would be "<< ave<<endl;
	cout<<"The worst case steps that would be needed to find a word is "<< worst<<endl;



	cout<<"Printing the statistics for hashFunction2 with hash table size "<<hashSize<<endl;
	cout<<"#hits    #slots receiving the #hits"<<endl;
	num=0;//slot number
	sum=0;

	worst=0;
	for(int i =0; i<hashSize;i++){//every possible hit number
		num=0;
		for (int n=0;n<hashSize;n++){//find num slot

			if((h2[n])==i){
				num++;
			}

		}
		if(num!=0){sum=sum+addup(i)*num;cout <<i<<"       "<<num<<endl;worst=i;}


	}
	ave=sum/num_words;
	cout<<"The average number of steps for a successful search for hash function 2 would be "<< ave<<endl;
	cout<<"The worst case steps that would be needed to find a word is "<< worst<<endl;

	return 0;
}	

