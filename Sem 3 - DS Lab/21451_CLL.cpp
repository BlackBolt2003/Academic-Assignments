/*
 * 21451_CLL.cpp
 *
 *  Created on: 03-Nov-2022
 *      Author: pict
 */

// ---------------- Singly CLL ---------------------
# include <iostream>
using namespace std;


class node{
    int data;
    node* next;

    public:

    //default constructor
    node(){
        this->data = 0;
        this->next = NULL;
    }

    //parameterized constructor
    node(int data){
        this->data = data;
        this->next = NULL;
    }

    friend class CLL;
};


class CLL{
    node* last;      //pointer to first node
    int length;      //total nodes in LL

public:
    //default constructor
    CLL(){
        last = NULL;
        length = 0;
    }

    //parameterized constructor
    CLL(node* last, int length){
        this->last = last;
        this->length = length;
    }

    // insertion
    void insert_in_empty(int val);
    void insert_at_tail(int val);
    void insert_at_head(int val);
    void insert_at_position(int pos, int val);

    //deletion
    void delete_node(int val);

    //print
    void display();
};


void CLL::insert_in_empty(int val){
	node* n = new node(val);

	last = n;
	n->next = n;
	++length;
	return;
}

void CLL::insert_at_tail(int val){
	node* n = new node(val);

	//if CLL is empty
	if (last == NULL){
		this->insert_in_empty(val);
		return;
	}

	n->next = last->next;
	last->next = n;
	last = n;
	++length;
	return;
}

void CLL::insert_at_head(int val){
	node* n = new node(val);

	//if CLL is empty
	if (last == NULL){
		this->insert_in_empty(val);
		return;
	}

	n->next = last->next;
	last->next = n;
	++length;
	return;
}

void CLL::insert_at_position(int pos, int val){
	node* n = new node(val);

	//if position = 1
	if (pos == 1){
		this->insert_at_head(val);
		return;
	}

	int counter = 1;
	node* temp = last->next;
	while(counter != pos-1){
		temp = temp->next;
		++counter;
	}
	n->next = temp->next;
	temp->next = n;
	++length;
	return;
}

void CLL::delete_node(int val){

	//if CLL is empty
	if (last == NULL){
		return;
	}

	node* prev = last;
	node* temp = last->next;
	while(temp != last){
		if (temp->data == val){
			prev->next = temp->next;
			delete temp;
			--length;
			return;
		}
		prev = temp;
		temp = temp->next;
	}

	if (temp->data == val){
		prev->next = temp->next;
		last = prev;
		delete temp;
		--length;
		return;
	}
	return;
}

void CLL::display(){
	//CLL is empty
	if (last == NULL){
		cout << " |NULL|" << endl;
		return;
	}

	node* temp = last->next;
	while(temp != last){
		cout << "|" << temp->data << "| -> ";
		temp = temp->next;
	}
	cout << "|" << temp->data << "| -> #" << endl;
	return;
}


int main(){
	ios::sync_with_stdio(0);

	CLL myList;
	for (int i=10; i<60; i+=10){
		myList.insert_at_tail(i);
	}
	myList.display();

	myList.insert_at_head(70);
	myList.display();

	myList.insert_at_position(3, 80);
	myList.display();

	myList.delete_node(30);
	myList.display();

	myList.delete_node(50);
	myList.display();

	myList.delete_node(10);
	myList.display();

	return 0;
}









