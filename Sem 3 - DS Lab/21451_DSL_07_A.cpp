/*
 * 21451_DSL_07.cpp
 *
 *  Created on: 03-Nov-2022
 *      Author: pict
 */
// ---------------------------------------------------------------------------------------------

// The ticket booking system of Cinemax theater has to be implemented using C++ program.
// There are 10 rows and 7 seats in each row. Doubly circular linked list has to be maintained
// to keep track of free seats at rows. Assume some random booking to start with. Use array to
// store pointers (Head pointer) to each row. On demand
// (a) The list of available seats is to be displayed
// (b) The seats are to be booked
// (c) The booking can be cancelled

// ---------------------------------------------------------------------------------------------
# include <iostream>
# include <string>
using namespace std;

class node{
	bool avail;
    int data;
    node* next;
    node* prev;

    public:

    //default constructor
    node(){
    	this->avail = true;
        this->data = 0;
        this->next = NULL;
        this->prev = NULL;
    }

    //parameterized constructor
    node(int data){
    	this->avail = true;
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }

    friend class DCLL;
    friend class Theatre;
};


class DCLL{
    node* head;      //pointer to first node
    int length;      //total nodes in LL

public:
    //default constructor
    DCLL(){
        head = NULL;
        length = 0;
    }

    //parameterized constructor
    DCLL(node* head, int length){
        this->head = head;
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
    void display_available();

    friend class Theatre;
};


void DCLL::insert_in_empty(int val){
	node* n = new node(val);

	head = n;
	n->next = n;
	n->prev = n;
	++length;
	return;
}

void DCLL::insert_at_tail(int val){
	node* n = new node(val);

	//if DCLL is empty
	if (head == NULL){
		this->insert_in_empty(val);
		return;
	}

	n->prev = head->prev;
	head->prev->next = n;
	n->next = head;
	head->prev = n;

	++length;
	return;
}

void DCLL::insert_at_head(int val){
	node* n = new node(val);

	//if DCLL is empty
	if (head == NULL){
		this->insert_in_empty(val);
		return;
	}

	n->next = head;
	n->prev = head->prev;
	head->prev = n;
	head = n;
	++length;
	return;
}

void DCLL::insert_at_position(int pos, int val){
	node* n = new node(val);

	//if position = 1
	if (pos == 1){
		this->insert_at_head(val);
		return;
	}

	int counter = 1;
	node* temp = head;
	while(counter != pos){
		temp = temp->next;
		++counter;
	}
	n->next = temp;
	n->prev = temp->prev;
	temp->prev->next = n;
	temp->prev = n;

	++length;
	return;
}

void DCLL::delete_node(int val){

	//if DCLL is empty
	if (head == NULL){
		return;
	}

	node* temp = head;

	//deletion at head
	if (temp->data == val){
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		head = temp->next;
		delete temp;
		--length;
		return;
	}

	temp = temp->next;

	while(temp != head){
		if (temp->data == val){
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			--length;
			return;
		}
		temp = temp->next;
	}

	return;
}

void DCLL::display(){
	//DCLL is empty
	if (head == NULL){
		cout << " |NULL|" << endl;
		return;
	}

	node* temp = head;
	while(temp != head->prev){
		cout << " | " << temp->data;
		temp = temp->next;
	}
	cout << " | " << temp->data << " |" << endl;
	return;
}

void DCLL::display_available(){
	//DCLL is empty
	if (head == NULL){
		cout << " |NULL|" << endl;
		return;
	}

	node* temp = head;
	while(temp != head->prev){
		if (temp->avail){
			cout << " | " << temp->data << "  . ";
		}
		else {
			cout << " | " << temp->data << "  X ";
		}
		temp = temp->next;
	}
	if (temp->avail){
		cout << " | " << temp->data << "  . " << " |" << endl;
	}
	else {
		cout << " | " << temp->data << "  X " << " |" << endl;
	}
	return;
}

// ------------------------------THEATRE CLASS-------------------------------------
class Theatre{

public:
	DCLL* rowArray;
	int rowCapacity;
	int seatCapacity;

	//default
	Theatre(){
		rowCapacity = 0;
		seatCapacity = 0;
		rowArray = new DCLL[10];
	}

	//parameterized
	Theatre(int rowCapacity, int seatCapacity){
		this->rowCapacity = rowCapacity;
		this->seatCapacity = seatCapacity;
		this->rowArray = new DCLL[rowCapacity];
	}

	//functions
	void create_theatre();
	void display_available_seats();

	bool validate_seat(int rowNo, int seatNo);

	void book_seat(int rowNo, int seatNo);
	void cancel_seat(int rowNo, int seatNo);

	void bulk_book(int rowNo, int startSeat, int endSeat);
	bool bulk_validate(int rowNo, int startSeat, int endSeat);
};


// --------------------------------THEATRE FUNCTIONS--------------------------------

void Theatre::create_theatre(){
	for(int i=1; i<=rowCapacity; i++){
		DCLL row;
		for (int j=1; j<=seatCapacity; j++){
			row.insert_at_tail(j);
		}
		rowArray[i] = row;
	}
}

void Theatre::display_available_seats(){
	for (int i=1; i<rowCapacity; i++){
		cout << "(" << i << ")  ";
		rowArray[i].display_available();
	}
	cout << "(" << rowCapacity  << ") ";
	rowArray[rowCapacity].display_available();
	cout << endl;
	return;
}

void Theatre::book_seat(int rowNo, int seatNo){
	node* temp = rowArray[rowNo].head;
	for (int i=1; i<seatNo; i++){
		temp = temp->next;
	}
	//at position
	if(temp->avail){
		temp->avail = false;
		cout << "Booking successful!" << endl;
	}
	else{
		cout << "Sorry! Seat is already booked!" << endl;
		cout << "Please check the available seats." << endl;
	}
	return;
}

void Theatre::cancel_seat(int rowNo, int seatNo){
	node* temp = rowArray[rowNo].head;
	for (int i=1; i<seatNo; i++){
		temp = temp->next;
	}
	//at position
	if(!temp->avail){
		temp->avail = true;
		cout << "Booking cancelled." << endl;
	}
	else{
		cout << "Seat was already available" << endl;
		cout << "Check seat number again" << endl;
	}
	return;
}

bool Theatre::validate_seat(int rowNo, int seatNo){
	if (rowNo <= rowCapacity && seatNo <= seatCapacity){
		return true;
	}
	else{
		return false;
	}
}

void Theatre::bulk_book(int rowNo, int startSeat, int endSeat){
	bool validity = this->bulk_validate(rowNo, startSeat, endSeat);
	if (validity){
		node* temp = rowArray[rowNo].head;
		for (int i=1; i<startSeat; i++){
			temp = temp->next;
		}
		//at starting seat
		for (int i=startSeat; i<=endSeat; i++){
			if(temp->avail){
				temp->avail = false;
			}
			temp = temp->next;
		}
		cout << "Booking successful!" << endl;

	}
	return;
}

bool Theatre::bulk_validate(int rowNo, int startSeat, int endSeat){
	node* temp = rowArray[rowNo].head;
	for (int i=1; i<startSeat; i++){
		temp = temp->next;
	}
	//at starting seat
	for (int i=startSeat; i<=endSeat; i++){
		if(!temp->avail){
			cout << "Sorry! Some seats in range are already booked!" << endl;
			cout << "Please check the available seats." << endl;
			return false;
		}
		else{
			temp = temp->next;
		}
	}
	return true;
}

// ----------------------------------- DRIVER CODE ----------------------------------

int main(){
	ios::sync_with_stdio(0);

	Theatre cinemax(10, 7);
	cinemax.create_theatre();

	//modular program
	cout << "Welcome to Cinemax Theatre !" << endl;
	cout << "How can we help you ?" << endl << endl;

	int choice = -1;
	int r, s;
	int r2, s2;
	while(choice){
		cout << "\n---------- OPTIONS ----------" << endl
			 << "1. Show Available Seats" << endl
			 << "2. Book Single Seat" << endl
			 << "3. Book seats in a range" << endl
			 << "4. Cancel Booking" << endl
			 << "0. Exit" << endl
			 << "-----------------------------" << endl
			 << "Enter your choice = ";
		cin >> choice;
		cout << endl;

		switch(choice){
		case 0: //exit
			cout << "\n :) Thank you ! Enjoy your show !" << endl;
			break;

		case 1: // Show Available Seats
			cinemax.display_available_seats();
			break;

		case 2: // Book seat
			cout << "Enter Row and Seat Number to book = ";
			cin >> r >> s;
			if (cinemax.validate_seat(r, s)){
				cinemax.book_seat(r, s);

			}
			else{
				cout << "Invalid seat number!" << endl;
				cout << "Please check the available seats." << endl;
			}
			break;

		case 3: // Book seats in bulk
			cout << "Enter Row number = ";
			cin >> r;
			cout << "Enter Seat Number of first seat = ";
			cin >> s;
			cout << "Enter Seat Number of last seat = ";
			cin >> s2;
			if (cinemax.validate_seat(r, s) && cinemax.validate_seat(r, s2)){
				cinemax.bulk_book(r, s, s2);

			}
			else{
				cout << "Invalid seat numbers!" << endl;
				cout << "Please check the available seats." << endl;
			}
			break;

		case 4: // Cancel Seat
			int r, s;
			cout << "Enter Row and Seat Number to cancel = ";
			cin >> r >> s;
			if (cinemax.validate_seat(r, s)){
				cinemax.cancel_seat(r, s);

			}
			else{
				cout << "Invalid seat number!" << endl;
				cout << "Please check the available seats." << endl;
			}
			break;
		}
	}

	return 0;
}





