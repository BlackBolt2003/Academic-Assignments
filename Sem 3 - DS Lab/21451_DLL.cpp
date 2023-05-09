/*
 * 21451_DLL.cpp
 *
 *  Created on: 03-Nov-2022
 *      Author: pict
 */

// --------------------------------------------

# include <iostream>
using namespace std;

class node{
    int data;
    node* prev;
    node* next;

    public:
    // default constructor
    node(){
        data = 0;
        prev = NULL;
        next = NULL;
    }

    // para constructor
    node(int val){
        data = val;
        prev = NULL;
        next = NULL;
    }

    friend class DLL;
};

// ----------------------------- Doubly Linked List ------------------------------

class DLL{
    node* head;     // pointer to first node
    int length;     // number of nodes

    public:
    // default constructor
    DLL(){
        head = NULL;
        length = 0;
    }

    // para constructor
    DLL(node* head){
        this->head = head;
        length = 0;
    }

    // insertion functions
    void insert_at_tail(int val);
    void insert_at_head(int val);
    void insert_at_position(int pos, int val);

    // deletion
    void delete_node(int val);

    // printing values
    void display();

};

// ----------------------------- Function Definitions ------------------------------

void DLL::insert_at_tail(int val){
    node* n = new node(val);

    // DLL is empty
    if (head == NULL){
        head = n;
        ++length;
        return;
    }

    node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = n;
    n->prev = temp;
    ++length;
    return;
}

void DLL::insert_at_head(int val){
    node* n = new node(val);

    // DLL is empty
    if (head == NULL){
        head = n;
        ++length;
        return;
    }
    n->next = head;
    head->prev = n;
    head = n;
    ++length;
    return;
}

void DLL::insert_at_position(int pos, int val){
    node* n = new node(val);

    // DLL is empty
    if (head == NULL){
        head = n;
        ++length;
        return;
    }

    if (pos == 1){
        this->insert_at_head(val);
        return;
    }

    node* temp = head;
    for (int i=1; i < (pos-1); ++i){
        temp = temp->next;
    }
    n->next = temp->next;
    temp->next->prev = n;
    n->prev = temp;
    temp->next = n;
    ++length;
    return;
}

void DLL::display(){
    // DLL is empty
    if (head == NULL){
        cout << "|NULL|" << endl;
        return;
    }

    node* temp = head;
    while(temp->next != NULL){
        cout << "|" << temp->data << "| <=> ";
        temp = temp->next;
    }
    cout << "|" << temp->data << "| --> NULL" << endl;
    return;
}

void DLL::delete_node(int val){
    node* temp = head;
    node* toDelete = NULL;

    // remove at head
    if (temp->data == val){
        toDelete = temp;
        head = temp->next;
        head->prev = NULL;
        delete toDelete;
        --length;
        return;
    }

    while(temp->next != NULL){
        if (temp->data == val){
            toDelete = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete toDelete;
            --length;
            return;
        }
        temp = temp->next;
    }

    // delete at tail
    if (temp->data == val){
        toDelete = temp;
        temp->prev->next = NULL;
        delete toDelete;
        --length;
    }
}


int main(){
    ios::sync_with_stdio(0);

    DLL myList;
    for (int i=10; i<60; i+=10){
        myList.insert_at_tail(i);
    }

    myList.display();

     myList.delete_node(10);
     myList.display();
     myList.delete_node(50);
     myList.display();
     myList.delete_node(30);
     myList.display();

     DLL myList2;
     myList2.insert_at_tail(90);
     myList2.insert_at_head(10);
     myList2.insert_at_position(2, 30);
     myList2.display();

     DLL myList3;
     myList3.display();

    return 0;
}


