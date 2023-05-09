/*
 * 21451_SLL.cpp
 *
 *  Created on: 02-NOV-2022
 *      Author: PICT
 */
// --------------------------------------------------

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

    friend class SLL;
};

// ---------------------------Singly Linked List ------------------------------

class SLL{
    node* head;      //pointer to first node
    int length;      //total nodes in LL

public:
    //default constructor
    SLL(){
        head = NULL;
        length = 0;
    }

    //parameterized constructor
    SLL(node* head, int length){
        this->head = head;
        this->length = length;
    }

    //member functions
    void insert_at_tail(int val);
    void insert_at_head(int val);
    void insert_at_position(int pos, int val);
    void insert_sorted(int val);

    void display();
    int size();
    int search(int val);

    void deleteNode(int val);

    void reverse();
    void reverse_recursive();	//called by user
    node* reverse_recursive(node* &head);	//called by function - returns new head obtained by reversing SLL
};

// ------------------------------ Function Definitions ----------------------------------
int SLL::size(){
	return this->length;
}

void SLL::insert_at_tail(int val){
    node* n = new node(val);

    //if LL is empty
    if(head == NULL){
        head = n;
        length++;
        return;
    }

    node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = n;
    length++;
    return;
}


void SLL::insert_at_head(int val){
	node* n = new node(val);

    //if LL is empty
    if(head == NULL){
        head = n;
        length++;
        return;
    }

    n->next = head;
    head = n;
    length++;
    return;
}

void SLL::insert_at_position(int pos, int val){
	if(pos == 1){
		this->insert_at_head(val);
		return;
	}

	node* n = new node(val);

	node* temp = head;
	pos--;
	while(--pos){
		temp = temp->next;
	}
	n->next = temp->next;
	temp->next = n;
	return;
}

void SLL::insert_sorted(int val){
	node* n = new node(val);

    //if LL is empty
    if(head == NULL){
        head = n;
        length++;
        return;
    }

    node* temp = head;
    while(temp->next != NULL){
    	if (temp->data > val){
    		this->insert_at_head(val);
    		return;
    	}
    	else if(temp->next->data <= val){
    		temp = temp->next;
    	}
    	else {
    		n->next = temp->next;
    		temp->next = n;
    		return;
    	}
    }
	if (temp->data > val){
		this->insert_at_head(val);
		return;
	}
    this->insert_at_tail(val);
	return;
}

void SLL::display(){
    //if LL is empty
    if(head == NULL){
        cout << "|NULL|" << endl;
        return;
    }

    node* temp = head;
    while(temp->next != NULL){
        cout << "|" << temp->data << "| -> ";
        temp = temp->next;
    }
    cout << "|" << temp->data << "| -> NULL" << endl;
}

int SLL::search(int val){
	node* temp = head;
	int counter = 1;
	while(temp->next != NULL){
		if (temp->data == val){
			return counter;
		}
		counter++;
		temp = temp->next;
	}
	if (temp->data == val){
		return counter;
	}
	return -1;
}

void SLL::deleteNode(int val){

    //SLL is empty
    if (head == NULL){
    	return;
    }

	node* toDelete = new node(0);
    //delete at head
    if (head->data == val){
    	toDelete = head;
    	//more than 1 node in SLL
    	if (length > 1){
        	head = head->next;
    	}
    	//only one node
    	if (length == 1){
    		head = NULL;
    	}
    	--length;
    }

    //delete anywhere
    else{
        node* temp = head;
        while(temp->next != NULL){
        	if (temp->next->data == val){
        		toDelete = temp->next;
        		temp->next = temp->next->next;
        		--length;
        		break;
        	}
        }
        //last node
    	if (temp->next->data == val){
    		toDelete = temp->next;
    		temp->next = temp->next->next;
    		--length;
    	}
    }

	delete toDelete;
	toDelete = NULL;
	return;
}

void SLL::reverse(){
	//SLL has 0 or 1 element
	if (length <= 1){
		return;
	}

	node* left = NULL;
	node* curr = head;
	node* right;

	while(curr != NULL){
		right = curr->next;
		curr->next = left;
		left = curr;
		curr = right;
	}
	head = left;
	return;
}

// returns new head obtained by reversing SLL
node* SLL::reverse_recursive(node* &currNode){

	//base case - 0 or 1 element present
	if (currNode == NULL || currNode->next == NULL){
		return currNode;
	}

	node* newHead = reverse_recursive(currNode->next);
	currNode->next->next = currNode;
	currNode->next = NULL;
	return newHead;
}

void SLL::reverse_recursive(){
	head = this->reverse_recursive(head);
}


// ------------------------------------- Driver Code -----------------------------
int main()
{
	ios::sync_with_stdio(false);

    SLL myList;

    for (int i=10; i<50; i+=10){
        myList.insert_at_tail(i);
    }

    myList.display();

//    myList.insert_at_head(90);
//    myList.display();
//
//    cout << myList.search(30) << endl;
//    cout << myList.search(100) << endl;
//
//    myList.deleteNode(10);
//    myList.display();
//
//    myList.deleteNode(90);
//    myList.display();
//
//    SLL myList2;
//    myList2.display();
//
//    myList2.insert_at_head(90);
//    myList2.display();
//
//    myList2.deleteNode(90);
//    myList2.display();
//
//    myList2.insert_at_head(70);
//    myList2.display();

//    myList.reverse();
//   	myList.display();
//
//    myList.reverse_recursive();
//   	myList.display();

//    myList.insert_at_position(3,50);
//    myList.display();
//
//    myList.insert_at_position(1,80);
//    myList.display();

//    myList.insert_sorted(90);
//    myList.insert_sorted(30);
//	myList.insert_sorted(70);
//	myList.insert_sorted(100);
//	myList.display();

    cout << endl;

    return 0;
}

