/*
 * 21451_DSL_07B.cpp
 *
 *  Created on: 16-Nov-2022
 *      Author: pict
 */
// ----------------------------------------------------------------
// Write C++ program for storing binary number using doubly linked lists. Write functions-
// a) To compute 1‘s and 2‘s complement
// b) Add two binary numbers
// ----------------------------------------------------------------


# include <iostream>
using namespace std;

class binaryNode{
    int data;
    binaryNode* prev;
    binaryNode* next;

    public:
    // default constructor
    binaryNode(){
        data = 0;
        prev = NULL;
        next = NULL;
    }

    // parameterized constructor
    binaryNode(int val){
        data = val;
        prev = NULL;
        next = NULL;
    }

    friend class binaryDLL;
};

// ----------------------------- Doubly Linked List ------------------------------

class binaryDLL{
    binaryNode* head;     // pointer to first binaryNode
    binaryNode* tail;	  // pointer to last binaryNode
    int length;     // number of binaryNodes

    public:
    // default constructor
    binaryDLL(){
        head = NULL;
        tail = NULL;
        length = 0;
    }

    // parameterized constructor
    binaryDLL(binaryNode* head, binaryNode* tail){
        this->head = head;
        this->tail = tail;
        length = 0;
    }

    // insertion functions
    void insert_at_tail(int val);
    void insert_at_head(int val);
    void insert_at_position(int pos, int val);

    // deletion
    void delete_binaryNode(int val);

    // printing values
    void display();

    // binary functions
    void decimal_to_binary(int dec);
    void display_binary();
    binaryDLL ones_compliment();
    binaryDLL twos_compliment();

    // overloaded binary functions
    binaryDLL operator + (binaryDLL bin);
};

// ----------------------------- Function Definitions ------------------------------

void binaryDLL::insert_at_tail(int val){
    binaryNode* n = new binaryNode(val);

    // binaryDLL is empty
    if (head == NULL){
        head = n;
        tail = n;
        ++length;
        return;
    }

    n->prev = tail;
    tail->next = n;
    tail = n;
    ++length;
    return;
}

void binaryDLL::insert_at_head(int val){
    binaryNode* n = new binaryNode(val);

    // binaryDLL is empty
    if (head == NULL){
        head = n;
        tail = n;
        ++length;
        return;
    }
    n->next = head;
    head->prev = n;
    head = n;
    ++length;
    return;
}

void binaryDLL::insert_at_position(int pos, int val){
    binaryNode* n = new binaryNode(val);

    // binaryDLL is empty
    if (head == NULL){
        head = n;
        tail = n;
        ++length;
        return;
    }

    if (pos == 1){
        this->insert_at_head(val);
        return;
    }

    if (pos == length){
    	this->insert_at_tail(val);
    	return;
    }

    binaryNode* temp = head;
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

void binaryDLL::display(){
    // binaryDLL is empty
    if (head == NULL){
        cout << "|NULL|" << endl;
        return;
    }

    binaryNode* temp = head;
    while(temp->next != NULL){
        cout << "|" << temp->data << "| <=> ";
        temp = temp->next;
    }
    cout << "|" << temp->data << "| --> NULL" << endl;
    return;
}

void binaryDLL::delete_binaryNode(int val){

    // empty binaryDLL
    if (head == NULL){
    	return;
    }

    binaryNode* temp = head;
    binaryNode* toDelete = NULL;

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
        tail = temp->prev;
        tail->next = NULL;
        delete toDelete;
        --length;
    }
}

// ----------------------------- Binary Functions  ------------------------------

void binaryDLL::decimal_to_binary(int dec){
	while(dec){
		this->insert_at_head(dec % 2);
		dec /= 2;
	}
}

void binaryDLL::display_binary(){
    // binaryDLL is empty
    if (head == NULL){
        cout << 0 << endl;
        return;
    }

    binaryNode* temp = head;
    while(temp != NULL){
        cout << temp->data;
        temp = temp->next;
    }
    cout << endl;
    return;
}

binaryDLL binaryDLL::ones_compliment(){
	binaryDLL bin;

	binaryNode* temp = head;
	while(temp != NULL){
		bin.insert_at_tail(!temp->data);
		temp = temp->next;
	}
	return bin;
}

binaryDLL binaryDLL::twos_compliment(){
	binaryDLL bin;
	bin = this->ones_compliment();
	binaryDLL bit;
	bit.decimal_to_binary(1);

	bin = bin + bit;
	return bin;
}

binaryDLL binaryDLL::operator + (binaryDLL bin){
	binaryDLL sum;

	binaryNode* t1 = this->tail;
	binaryNode* t2 = bin.tail;
	int carry = 0;

	while(t1 != NULL && t2 != NULL){
		sum.insert_at_head(0);
		sum.head->data = (t1->data ^ t2->data ^ carry);
		carry = (t1->data & t2->data) | (t2->data & carry) | (carry & t1->data);

		t1 = t1->prev;
		t2 = t2->prev;
	}

	while(t1 != NULL){
		sum.insert_at_head(0);
		sum.head->data = (t1->data ^ carry);
		carry = (carry & t1->data);

		t1 = t1->prev;
	}

	while(t2 != NULL){
		sum.insert_at_head(0);
		sum.head->data = (t2->data ^ carry);
		carry = (carry & t2->data);

		t2 = t2->prev;
	}

	if (carry){
		sum.insert_at_head(carry);
	}
	return sum;
}

// ----------------------------- Driver Code ------------------------------------

int main(){
	ios::sync_with_stdio(false);

	binaryDLL bin1;
	int dec1 = 16;
	bin1.decimal_to_binary(dec1);

	cout << dec1 << " = ";
	bin1.display_binary();

	binaryDLL bin2;
	bin2 = bin1.ones_compliment();
	bin2.display_binary();

	binaryDLL bin3;
	bin3 = bin1.twos_compliment();
	bin3.display_binary();

	binaryDLL bin4;
	int dec2 = 97;
	bin4.decimal_to_binary(dec2);
	cout << dec2 << " = ";
	bin4.display_binary();

	binaryDLL binSum = bin1 + bin4;
	cout << "Sum  = " << dec1 + dec2 << " = ";
	binSum.display_binary();

	return 0;
}


