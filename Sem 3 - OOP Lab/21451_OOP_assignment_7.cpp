/*
 * 21451_OOP_assignment_07.cpp
 *
 *  Created on: 07-Nov-2022
 *      Author: se
 */
//---------------------------------------------------

#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <map>
using namespace std;

void createMap(map<string, int> &population){

	population.insert(pair<string, int> ("Bihar", 104099452));
	population.insert(pair<string, int> ("Maharashtra", 112374333));
	population.insert(pair<string, int> ("Rajasthan", 68548437));
//	population.insert(pair<string, int> ("Gujarat", 60439692));
//	population.insert(pair<string, int> ("Odisha", 41974219));
//	population.insert(pair<string, int> ("Kerala", 33406061));
}


//driver code
int main(){
	map<string, int> population;

	createMap(population);

	//menu driven program
	int choice = 1;
	while(choice){
		cout << "\n---------- MENU ----------"
			 << "\n1. Insert Data"
			 << "\n2. Display All Data"
			 << "\n3. Search Data"
			 << "\n0. Exit"
			 << "\n--------------------------"
			 << "\n\nEnter your choice :";

		cin >> choice;
		switch (choice){
		case 1: //insert data
			{string state;
			int pop;
			cout << "Enter name of state: ";
			cin >> state;
			cout << "\nEnter population: ";
			cin >> pop;
			population.insert(pair<string, int> (state, pop));
			cout << "\nData saved successfully!" << endl;
			break;}

		case 2: //display data
			{cout << "# Population Data #" << endl;
			map<string, int> :: iterator itr;
			for (itr = population.begin(); itr != population.end(); itr++){
				cout << "[] " << itr->first << " : " << itr->second << endl;
			}
			break;}

		case 3: //search data
			{string state;
			cout << "Enter state to search: ";
			cin >> state;
			cout << "\n[] " << state << " : " << population[state] << endl;
			break;}

		case 0: //exit
			{cout << "# Exit from Database" << endl;
			break;}
		}
	}

	return 0;
}

