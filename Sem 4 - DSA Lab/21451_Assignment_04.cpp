/*
 * 21451_Assignment_04.cpp
 *
 *  Created on: 24-Mar-2023
 *      Author: student
 */

// PROBLEM STATEMENT --------------------------------------------------------------------
/*
Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use of two
collision handling techniques and compare them using number of comparisons
required to find a set of telephone numbers (Note: Use linear probing with
replacement and without replacement)
*/

// CODE ---------------------------------------------------------------------------------

# include <iostream>
using namespace std;

// classes ----------------

class Entry {
	string name;
	string teleNo;

public:
	Entry(){
		name = teleNo = ' ';
	}

	Entry(string name, string teleNo){
		this->name = name;
		this->teleNo = teleNo;
	}

	friend class hashtable;

};

class hashtable {
	Entry* ht;
	int size;

public:
	hashtable(){
		size = 10;
		ht = new Entry[10];
		for (int i=0; i<10; i++){
			ht[i] = Entry();
		}
	}

	hashtable(int size){
		this->size = size;
		ht = new Entry[size];
		for (int i=0; i<size; i++){
			ht[i] = Entry();
		}
	}

	int hash_func(string key);
	int find_slot(string key);

	void insert_no_replacement(string key, string value);
	void insert_with_replacement(string key, string value);

	int search(string key);				// return number of passes
	int search_index(string key);		// return index of key

	void display();

	void remove(string key);
};


// driver code ------------
int main(){
	hashtable ht1;	// without replacement
	hashtable ht2;	// with replacement

	int choice = -1;
	int temp = 0;
	string name = " ";
	string teleNo = " ";

	cout << "# Hash-Table Telephone Record\n";
	while(choice){
		cout << "\n---------- MENU ----------\n"
			 << "1. Insert name-number pair\n"
			 << "2. Search number by name\n"
			 << "3. Display List\n"
			 << "4. Delete entry\n"
			 << "0. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch(choice){
		case 1: // Insert name-number pair
		{
			cout << "Enter name = ";
			cin >> name;
			cout << "Enter telephone no. = ";
			cin >> teleNo;
			ht1.insert_no_replacement(name, teleNo);
			ht2.insert_with_replacement(name, teleNo);
			break;
		}

		case 2: // Search number by name
		{
			cout << "Enter name to search = ";
			cin >> name;
			temp = ht1.search(name);
			cout << "No of passes (without replacement) = " << temp << endl;

			temp = ht2.search(name);
			cout << "No of passes (with replacement) = " << temp << endl;
			break;
		}

		case 3: // Display list
		{
			cout << "Without replacement : " << endl;
			ht1.display();
			cout << endl;
			cout << "With replacement : " << endl;
			ht2.display();
			break;
		}

		case 4: // Delete entry
		{
			cout << "Enter name to delete = ";
			cin >> name;
			ht1.remove(name);
			ht2.remove(name);
			break;
		}

		case 0: // Exit
		{
			cout << "Thank you :)" << endl;
			break;
		}

		default : // forced exit
		{
			cout << "# Forced exit due to error" << endl;
			exit(0);
		}
		}
	}

	return 0;
}


// definitions ------------

int hashtable::hash_func(string key) {
	int hash = 0;
	for(auto ch : key){
		hash += int(ch);
	}
	return hash;
}

int hashtable::find_slot(string key) {
	int idx = hash_func(key) % size;
	while (ht[idx].name != " " && ht[idx].name != key){
		idx = (idx + 1) % size;
	}
	return idx;
}

void hashtable::insert_no_replacement(string key, string value) {
	int idx = find_slot(key);
	ht[idx].name = key;
	ht[idx].teleNo = value;
}

void hashtable::insert_with_replacement(string key, string value) {
	int idx = hash_func(key) % size;
	string tname, tnum;
	while( ht[idx].name != " " && ht[idx].name != key){
		int x = hash_func(ht[idx].name) % size;

		if (x != idx) {
			tname = ht[idx].name;
			tnum = ht[idx].teleNo;

			ht[idx].name = key;
			ht[idx].teleNo = value;

			key = tname;
			value = tnum;
		}
		idx = (idx + 1) % size;
	}
	ht[idx].name = key;
	ht[idx].teleNo = value;
}


int hashtable::search(string key) {
	int pass = 0;
	int idx = hash_func(key) % size;
	for (int i=0; i<size; ++i){
		pass++;
		if (ht[idx].name == key){
			cout << "Name = " << key << endl;
			cout << "Telephone No. = " << ht[idx].teleNo << endl;
			return pass;
		}
		else idx = (idx + 1) % size;
	}
	cout << key << " not present in record!" << endl;
	return pass;
}

int hashtable::search_index(string key) {
	int idx = hash_func(key) % size;
	for (int i=0; i<size; ++i){
		if (ht[idx].name == key){
			cout << "Name = " << key << endl;
			cout << "Telephone No. = " << ht[idx].teleNo << endl;
			return idx;
		}
		else idx = (idx + 1) % size;
	}
	cout << key << " not present in record!" << endl;
	return -1;
}

void hashtable::display() {
	cout << "Index\t" << "Name\t\t" << "Telephone Number" << endl;
	for(int i=0; i<size; ++i){
		cout << (i) << "\t" << ht[i].name << "\t\t" << ht[i].teleNo << endl;
	}
}

void hashtable::remove(string key) {
	int idx = this->search_index(key);

	if(idx != -1){
		ht[idx].name = " ";
		ht[idx].teleNo = " ";
		cout << "Entry deleted." << endl;
	}
}
// end ---------------------















