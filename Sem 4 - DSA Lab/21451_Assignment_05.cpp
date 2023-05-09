/*
 * 21451_Assignment_05.cpp
 *
 *  Created on: 28-Mar-2023
 *      Author: student
 */
/* PROBLEM STATEMENT ------------------------------------------------------------------

Implement all the functions of a dictionary (ADT) using open hashing technique:
separate chaining using linked list
Data: Set of (key, value) pairs
Keys are mapped to values
Keys must be comparable, and Keys must be unique.
Standard Operations: Insert(key, value), Find(key), Delete(key)

------------------------------------------------------------------------------------ */

#include <iostream>
using namespace std;

class Entry {
	string word;
	string meaning;
	Entry *next;

public:
	Entry(){
		word = meaning = " ";
		next = NULL;
	}

	Entry(string w, string m){
		word = w;
		meaning = m;
		next = NULL;
	}

	void print(){
		cout << word << " = " << meaning;
	}

	friend class Dictionary;
};

class Dictionary{
	Entry** table;
	int size;

public:
	Dictionary(){
		size = 10;
		table = new Entry*[10];
		for(int i=0; i<10; ++i){
			table[i] = NULL;
		}
	}

	Dictionary(int size){
		this->size = size;
		table = new Entry*[size];
		for(int i=0; i<size; ++i){
			table[i] = NULL;
		}
	}

	int hash_func(string key);
	void insert(string key, string value);
	void search(string key);
	void remove(string key);
	void display();

};

// driver code ------------
int main(){
	Dictionary dict;

	int choice = -1;
	int temp = 0;
	string key = " ";
	string value = " ";

	cout << "# Hash-Table Dictionary\n";
	while(choice){
		cout << "\n---------- MENU ----------\n"
			 << "1. Insert word-meaning pair\n"
			 << "2. Search meaning of word\n"
			 << "3. Display dictionary\n"
			 << "4. Delete entry\n"
			 << "0. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch(choice){
		case 1: // Insert word-meaning pair
		{
			cout << "Enter word = ";
			cin >> key;
			cout << "Enter meaning = ";
			cin.ignore(1000, '\n');
			getline(cin, value);
			dict.insert(key, value);
			break;
		}

		case 2: // Search meaning of word
		{
			cout << "Enter word to search = ";
			cin >> key;
			dict.search(key);
			break;
		}

		case 3: // Display dictionary
		{
			cout << "Dictionary : " << endl;
			dict.display();
			cout << endl;
			break;
		}

		case 4: // Delete entry
		{
			cout << "Enter name to delete = ";
			cin >> key;
			dict.remove(key);
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

// DEFINITIONS -------------------------------------------------------------------

int Dictionary::hash_func(string key) {
	int hash = 0;
	for(int i=0; i<key.size(); ++i){
		hash += key[i];
	}
	return (hash % size);
}

void Dictionary::insert(string key, string value) {
	int idx = hash_func(key);

	// empty slot
	if(table[idx] == NULL){
		table[idx] = new Entry(key, value);
		return;
	}

	// non-empty list - insert at tail
	Entry* temp = table[idx];
	while(temp->next != NULL){
		if (temp->word == key){
			cout << "duplicate entry for "<< key << endl;
			return;
		}
		temp = temp->next;
	}
	if (temp->word == key){
		cout << "duplicate entry for "<< key << endl;
		return;
	}
	temp->next = new Entry(key, value);
}

void Dictionary::search(string key) {
	int idx = hash_func(key);

	Entry* temp = table[idx];
	while(temp != NULL){
		if (temp->word == key){
			temp->print();
			cout << endl;
			return;
		}
		temp = temp->next;
	}
	cout << key << " not found." << endl;
}

void Dictionary::remove(string key) {
	int idx = hash_func(key);

	Entry* temp = table[idx];

	//delete at head
	if (temp->word == key){
		table[idx] = temp->next;

		delete temp;

		cout << key << " deleted." << endl;
		return;
	}

	// delete in-between
	Entry* prev = temp;
	temp = temp->next;
	while(temp->next != NULL){
		if (temp->word == key){
			prev->next = temp->next;

			delete temp;

			cout << key << " deleted." << endl;
			return;
		}
		prev = temp;
		temp = temp->next;
	}

	// delete at tail
	if(temp->word == key){
		prev->next = NULL;

		delete temp;

		cout << key << " deleted." << endl;
		return;
	}

	// key not found
	cout << key << " not found." << endl;
}

void Dictionary::display() {
	cout << "Sr.No. \t Word-Meaning Pairs" << endl;
	for(int i=0; i<size; ++i){
		cout << i << " \t ";
		Entry* temp = table[i];
		while(temp != NULL){
			temp->print();
			cout << " | ";
			temp = temp->next;
		}
		cout << endl;
	}
}
