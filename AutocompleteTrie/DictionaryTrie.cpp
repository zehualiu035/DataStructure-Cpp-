#include "util.h"
#include <queue>
#include <vector>
#include <stack>
#include "DictionaryTrie.h"
using namespace std;
//Zehua Liu A92406573
/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
	root=0;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{std::string ::iterator it1=word.begin();
	for(;it1!=word.end();++it1){
		if((*it1>'z'||*it1<'a')&&*it1!=' '){
			cout<<"Invalid Input. Please retry with correct input1"<<endl;

			return false;}
	}

	bool change=false;
	if(word.size()==0){

		return false;
	} 

	//test word is exist or not

	if(DictionaryTrie::find(word,freq)){return false;}
	std::string ::iterator it=word.begin();


	Node* cur=root;
	if (root==0){//if root is 0 ,make a new root


		Node* start=new Node();//make the new node

		start->c=*it;

		root=start;
		if((it+1)==word.end()){root->end=true;cur->s=word;root->fre=freq;}//find the end of word
		it++;
		cur=root;
		change=true;
		for(;it!=word.end();++it){//make the rest of the word
			Node* n=new Node();
			n->c=*it;cur->mid=n;cur=cur->mid;change =true; 
			if((it+1)==word.end()){cur->end=true;cur->s=word;cur->fre=freq;//find the end of word
				return true;
			}   

		}

	}

	for(;it!=word.end();++it){
		//letter by letter

		while(1){

			Node* n=new Node();
			n->c=*it;
			if((it+1)==word.end()){n->end=true;n->s=word;n->fre=freq;}//find the end word



			if(cur->c==*it){
				//if find the same letter
				if(cur->mid==0){change=true;

					it=it+1;	
					delete n;//insrt the rest of them

					for(;it!=word.end();++it){

						if(change){


							Node* n1=new Node();

							n1->c=*it;

							if((it+1)==word.end()){n1->end=true;n1->s=word;n1->fre=freq;n1->s=word;}

							cur->mid=n1;cur=cur->mid;
						}
					}return change;
				}
				//if is last letter
				if(cur->mid!=0){if((it+1)==word.end()){cur->end=true;cur->s=word;cur->fre=freq;cur->s=word;	delete n;return true;}
					cur=cur->mid;it=it+1;
					delete n;//move down

					continue;}
			}






			if(cur->c>*it){//if is cur larger

				if(cur->left==0){cur->left=n;cur=cur->left;change=true;

					it=it+1;

					for(;it!=word.end();++it){//create the rest of word


						if(change){

							Node* n1=new Node();

							n1->c=*it;

							if((it+1)==word.end()){n1->end=true;n1->s=word;n1->fre=freq;}//find the end 
							cur->mid=n1;cur=cur->mid;

						}
					}return change;




				}
				if(cur->left!=0){	//goes to left
					cur=cur->left;
					delete n;
					continue;}

			}







			if(cur->c<*it){//if cur is smaller than it

				if(cur->right==0){cur->right=n;cur=cur->right;change=true;//create the rest

					it=it+1;

					for(;it!=word.end();++it){//if is no end

						if(change){
							Node* n1=new Node();
							n1->c=*it;

							if((it+1)==word.end()){n1->end=true;n1->s=word;n1->fre=freq;}

							cur->mid=n1;cur=cur->mid;
						}
					}return change;

				}
				if(cur->right!=0){

					cur=cur->right;
					delete n;//no mem leak

					continue;}
				delete n;
				//break;

			}



		}return change;}
	return change;

}
























/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{std::string ::iterator it1=word.begin();
	for(;it1!=word.end();++it1){
		if((*it1>'z'||*it1<'a')&&*it1!=' '){cout<<"Invalid Input. Please retry with correct input2"<<endl;
			return false;}
	}



	Node* cur=root;
	if(word.size()==0){//if word is empty

		return false;
	} 

	if (root==0){//tree is empty
		return false;}



	std::string ::iterator it=word.begin();
	for(;it!=word.end();++it){//find the letter


		while(1){
			//get to correct position and check if is the end of the word and then check if is end node`

			if(cur->c==*it){


				if(cur->mid==0){


					if((it+1)==word.end()&&cur->end){//find the end
						return true;}
					else{
						return false;}

				}
				else{
					if((it+1)==word.end()&&cur->end){
						return true;}

					cur=cur->mid;

					break;}
			}



			if(cur->c<*it){//smaller go right

				if(cur->right==0){
					return false;}
				else {


					cur= cur->right;

					continue;}
			}
			if(cur->c>*it){//if cur is big,go left

				if(cur->left==0){
					return false;}

				else {

					cur= cur->left;
					continue;
				}
			}
		}
	}return false;
}


//second find method,to update frequency

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word,unsigned int freq) const
{

	std::string ::iterator it1=word.begin();
	for(;it1!=word.end();++it1){
		if((*it1>'z'||*it1<'a')&&*it1!=' '){cout<<"Invalid Input. Please retry with correct input3"<<endl;//check vaild
			return false;}
	}

	Node* cur=root;
	if(word.size()==0){//check size

		return false;
	} 

	if (root==0){
		return false;}



	std::string ::iterator it=word.begin();
	for(;it!=word.end();++it){


		while(1){



			if(cur->c==*it){


				if(cur->mid==0){


					if((it+1)==word.end()&&cur->end){
						if (cur->fre<freq){//update

							cout<<endl<<"update frequence! old freq is "<<cur->fre;
							cur->fre=freq;cout<<" new freq is "<<cur->fre<<endl;
							cout<<" "<<endl;

						}
						return true;}
					else{
						return false;}

				}//update
				else{
					if((it+1)==word.end()&&cur->end){
						if (cur->fre!=freq){cout<<endl<<"old freq is "<<cur->fre;
							cur->fre=freq;cout<<" update freq,new freq is"<<cur->fre<<endl;

						}

						return true;}

					cur=cur->mid;

					break;}
			}



			if(cur->c<*it){//go right

				if(cur->right==0){
					return false;}
				else {


					cur= cur->right;

					continue;}
			}
			if(cur->c>*it){//go left

				if(cur->left==0){
					return false;}

				else {

					cur= cur->left;
					continue;
				}
			}
		}
	}return false;
}













//this is like find()but return the last node 





Node* DictionaryTrie::findLast(std::string word) const
{



	Node* cur=root;
	if(word.size()==0){//

		return 0;
	} 

	if (root==0){
		return 0;}



	std::string ::iterator it=word.begin();
	for(;it!=word.end();++it){


		while(1){


			if(cur->c==*it){


				if(cur->mid==0){


					if((it+1)==word.end()){

						return cur;}
					else{
						return 0;}

				}
				else{
					if((it+1)==word.end()){


						return cur;}

					cur=cur->mid;
					break;}
			}



			if(cur->c<*it){

				if(cur->right==0){
					return 0;}
				else {


					cur= cur->right;

					continue;}
			}
			if(cur->c>*it){

				if(cur->left==0){
					return 0;}

				else {

					cur= cur->left;
					continue;
				}
			}
		}
	}return 0;
}

//BFS find the end node,find and push it to pqueue

void DictionaryTrie::BFS(std::queue<Node*> q,std::priority_queue<Node*,std::vector<Node*>,  NodePtrComp> &save)
{

	//cout<< "here is 128"<<endl;
	while(!q.empty()){

		//cout<< "here is 138"<<endl;
		Node* n=q.front();
		//if(!n){return;}
		//cout<< "here is 148"<<endl;
		q.pop();
		//cout<< "here is 158"<<endl;
		if(n->end){


			save.push(n);

		}

		//cout<< "here is 168"<<endl;
		if(n->left!=0){



			q.push(n->left);
		}
		if(n->mid!=0){


			q.push(n->mid);
		}
		if(n->right!=0){

			q.push(n->right);
		}

		//cout<< "here is 188 q front is "<<q.front()->s<<endl;
		//cout<<"q size is "<<q.size()<<"save size"<<save.size()<<endl;
	}
}







/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
	std::vector<std::string> words;
	std::queue<Node*> q;

	//inout is wrong
	std::string ::iterator it1=prefix.begin();

	for(;it1!=prefix.end();++it1){
		if((*it1>'z'||*it1<'a')&&*it1!=' '){cout<<"Invalid Input. Please retry with correct input4"<<endl;
			return words;}
	}

	//input is empty
	if(prefix.length()==0){
		cout<<"Invalid Input. Please retry with correct input"<<endl;
		return words;}
	//cout<< "here is 16"<<endl;

	std::priority_queue<Node*,std::vector<Node*>,  NodePtrComp> save;


	Node* last=findLast(prefix);
	if(!last){return words;}
	q.push(last);
	//get the last node of word
	BFS(q,save);//search every word is end
	int size1=save.size();//save the size



	if(save.size()==0){return words;}

	int ifbreak=0;

	std::priority_queue<Node*,std::vector<Node*>,  NodePtrComp> process;
	std::string ::iterator it2=prefix.begin();
	std::string ::iterator it3=prefix.begin();
	while(save.size()){ //get rid of the word which is not correct save the right one in "process" queue
		string ck=save.top()->s;ifbreak=0;
		it3=ck.begin();it2=prefix.begin();
		for(;it2!=prefix.end();++it2){
			if((*it3)!=*(it2)){//cout<<"here"<<endl;
				ifbreak=1;save.pop();break;
			}it3++;

		}if(ifbreak==1){continue;}
		process.push(save.top());
		save.pop();
	}


	size1=process.size();
	//load to word
	if(process.size()>=num_completions){
		for(unsigned int i=0;i<num_completions;i++){

			words.push_back(process.top()->s);
			process.pop();
			//cout<<"first case"<<endl;
		}
	}
	else {//num_completeions is too big

		for(int i=0;i<size1;i++){

			words.push_back(process.top()->s);
			process.pop();
			//	cout<<"sec case"<<endl;
		}

	}

	return words;
}

Node::~Node(){


}


/* Destructor */
DictionaryTrie::~DictionaryTrie(){

	deleteNode(root);
}

void DictionaryTrie::deleteNode(Node* node){
	//cout<<"delete here"<<endl;
	if(node==0){return;}

	if(node->left!=0){deleteNode(node->left);}
	if(node->mid!=0){deleteNode(node->mid);}

	if(node->right!=0){deleteNode(node->right);}
	delete node;
}



