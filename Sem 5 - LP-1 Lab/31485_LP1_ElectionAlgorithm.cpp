//============================================================================
// Name        : 31485_ElectionAlgorithm.cpp
// Author      : Ashwin Taras
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

class Node{
public:
	int id;
	Node(){
		id = 0;
	}
	Node(int i){
		id = i;
	}
};

class Ring{
public:
	int num;
	vector <Node> vec;
	Ring(){
		cout<<"\n\tRING ALGORITHM\n";
		num = 0;
		cout<<"Enter number of Nodes : ";
		cin>>num;
		for(int i=0; i<num; i++){
			Node obj;
			cout<<"Enter ID of "<<i+1<<" Node : ";
			cin>>obj.id;
			vec.push_back(obj);
		}
	}
	void detect(){
		sort( vec.begin( ), vec.end( ), [ ]( const Node& lhs, const Node& rhs )
		{
		   return lhs.id < rhs.id;
		});
		sleep(2);
		cout<<"\nCo-ordinator "<<vec.back().id<<" failed !\n\n";
		vec.pop_back();
		num--;
	}

	void elect(){
		cout<<"\nLet "<<vec.back().id<<" is new Co-ordinator\n\n";
		cout<<"\tMessage Passing\n\n";
		sleep(2);
		int i=0;
		int index = num-1;
		while(i<num){
			cout<<"Message passed from "<< vec[index].id <<" to "<< vec[(index+1)%(num)].id <<endl;
			sleep(2);
			i++;
			index = (index+1)%num;
		}
		cout<<"\n\nHence, new elected Co-ordinator is : "<<vec.back().id<<" !";
	}
};

class Bully{
public:

	int num;
	vector <Node> vec;

	Bully(){
		num = 0;
		cout<<"\n\tBULLY ALGORITHM\n";
		cout<<"Enter number of Nodes : ";
		cin>>num;
		for(int i=0; i<num; i++){
			Node obj;
			cout<<"Enter ID of "<<i+1<<" Node : ";
			cin>>obj.id;
			vec.push_back(obj);
		}
	}

	void detect(){
		sort( vec.begin( ), vec.end( ), [ ]( const Node& lhs, const Node& rhs )
		{
		   return lhs.id < rhs.id;
		});
		cout<<"\n\nCurrent Co-ordinator is : "<<vec.back().id<<endl;
		sleep(1);
		cout<<"\nCo-ordinator "<<vec.back().id<<" failed !\n\n";
		vec.pop_back();
		num--;
	}
	void elect(){
		int newCo = rand()%(num);
		sleep(1);
		cout<<"Detected by : "<<newCo<<endl;
		sleep(1);
		cout<<"ELECTION INITIALIZE\n";
		sleep(1);
		while(newCo != num+1){
			int j = newCo;
			for(int i=newCo; i<=num; i++){
				if(j>num+1) break;
				sleep(1);
				cout<<"Message sent from "<<newCo<<" to "<<++j<<endl;
			}
			for(int i=num; i>newCo; i--){
				sleep(1);
				cout<<"ACK sent from "<<i<<" to "<<newCo<<endl;
			}
			newCo++;
		}
		cout<<"\nHence, new elected Co-ordinator is : "<<vec.back().id<<" !";
	}
};

int main() {
	cout<<"\n========= ELECTION ALGORITHM ===========\n\n";
	while(true){
		int choice;
		cout<<"\n\tSelect option : \n\t1. Ring Algorithm\n\t2. Bully Algorithm\n";
		cout<<"\nEnter choice : ";
		cin>>choice;

		if(choice == 1){
			Ring r;
			r.detect();
			r.elect();
		}
		else if(choice == 2){
			Bully b;
			b.detect();
			b.elect();
		}
		else{
			cout<<"\n========= THANK YOU ==========\n\n";
			break;
		}
	}
	return 0;
}
