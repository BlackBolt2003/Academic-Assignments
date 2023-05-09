/*
 * 21451_DSL_08.cpp
 *
 *  Created on: 16-Nov-2022
 *      Author: pict
 */
// --------------------------------------------------------------------------------------------
// Write C++ program for storing appointment schedule for day. Appointments are booked
// randomly using linked list. Set start and end time and min and max duration for visit slot.
// Write functions for-
// a) Display free slots
// b) Book appointment
// c) Cancel appointment (check validity, time bounds, availability)
// d) Sort list based on time
// e) Sort list based on time using pointer manipulation
// --------------------------------------------------------------------------------------------

# include <iostream>
using namespace std;
# define daySt 1
# define dayEt 6
# define duration 1

//code uses military time
//e.g. 5.17 => 517, 1.05 => 105

class visitSlotNode{
    int aptNo;			// appointment number
    int startTime;
    int endTime;
    int visitDuration;
    visitSlotNode* next;

    public:

    //default constructor
    visitSlotNode(){
        this->aptNo = 0;
        this->next = NULL;
        startTime = 0;
        endTime = 0;
        visitDuration = 0;
    }

    //parameterized constructor
    visitSlotNode(int st){
        this->aptNo = st;
        this->next = NULL;
        startTime = st;
        endTime = st + duration;
        visitDuration = duration;
    }

    //copy constructor
    visitSlotNode(visitSlotNode* &n){
        this->aptNo = n->aptNo;
        this->next = n->next;
        this->startTime = n->startTime;
        this->endTime = n->endTime;
        this->visitDuration = n->visitDuration;
    }

    bool validate_slot();

    friend class scheduleSLL;
};

// ---------------------------Singly Linked List for Schedule ------------------------------

class scheduleSLL{
    visitSlotNode* head;      //pointer to first visitSlotNode
    int length;      		  //total visitSlotNodes in LL

public:
    //default constructor
    scheduleSLL(){
        head = NULL;
        length = 0;
    }

    //parameterized constructor - 1
    scheduleSLL(visitSlotNode* head, int length){
        this->head = head;
        this->length = length;
    }

    //insertion
    void insert_at_tail(int val);
    void insert_at_head(int val);
    void insert_at_position(int pos, int val);
    void insert_sorted(int val);

    //display and other
    void display();
    int size();
    int search(int val);

    //deletion
    void deleteNode(int val);

    //reversal
    void reverse();

    //Scheduling functions
    void display_schedule();
    void book_slot(int st);
    void cancel_slot(int st);
    void sort_schedule();
    void sort_schedule_by_pointers();
    bool validate_slot(visitSlotNode n);
    void display_available_slots();

};

// ------------------------------ Function Definitions ----------------------------------

int scheduleSLL::size(){
	return this->length;
}

void scheduleSLL::insert_at_tail(int val){
    visitSlotNode* n = new visitSlotNode(val);

    //if LL is empty
    if(head == NULL){
        head = n;
        length++;
        return;
    }

    visitSlotNode* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = n;
    length++;
    return;
}


void scheduleSLL::insert_at_head(int val){
	visitSlotNode* n = new visitSlotNode(val);

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

void scheduleSLL::insert_at_position(int pos, int val){
	if(pos == 1){
		this->insert_at_head(val);
		return;
	}

	visitSlotNode* n = new visitSlotNode(val);

	visitSlotNode* temp = head;
	pos--;
	while(--pos){
		temp = temp->next;
	}
	n->next = temp->next;
	temp->next = n;
	return;
}

void scheduleSLL::insert_sorted(int val){
	visitSlotNode* n = new visitSlotNode(val);

    //if LL is empty
    if(head == NULL){
        head = n;
        length++;
        return;
    }

    visitSlotNode* temp = head;
    while(temp->next != NULL){
    	if (temp->aptNo > val){
    		this->insert_at_head(val);
    		return;
    	}
    	else if(temp->next->aptNo <= val){
    		temp = temp->next;
    	}
    	else {
    		n->next = temp->next;
    		temp->next = n;
    		return;
    	}
    }
	if (temp->aptNo > val){
		this->insert_at_head(val);
		return;
	}
    this->insert_at_tail(val);
	return;
}

void scheduleSLL::display(){
    //if LL is empty
    if(head == NULL){
        cout << "|NULL|" << endl;
        return;
    }

    visitSlotNode* temp = head;
    while(temp->next != NULL){
        cout << "|" << temp->aptNo << "| -> ";
        temp = temp->next;
    }
    cout << "|" << temp->aptNo << "| -> NULL" << endl;
}

int scheduleSLL::search(int val){
	visitSlotNode* temp = head;
	int counter = 1;
	while(temp->next != NULL){
		if (temp->aptNo == val){
			return counter;
		}
		counter++;
		temp = temp->next;
	}
	if (temp->aptNo == val){
		return counter;
	}
	return -1;
}

void scheduleSLL::deleteNode(int val){

    //scheduleSLL is empty
    if (head == NULL){
    	return;
    }

	visitSlotNode* toDelete = new visitSlotNode(0);
    //delete at head
    if (head->aptNo == val){
    	toDelete = head;
    	//more than 1 visitSlotNode in scheduleSLL
    	if (length > 1){
        	head = head->next;
    	}
    	//only one visitSlotNode
    	if (length == 1){
    		head = NULL;
    	}
    	--length;
    }

    //delete anywhere
    else{
        visitSlotNode* temp = head;
        while(temp->next != NULL){
        	if (temp->next->aptNo == val){
        		toDelete = temp->next;
        		temp->next = temp->next->next;
        		--length;
        		break;
        	}
        }
        //last visitSlotNode
    	if (temp->next->aptNo == val){
    		toDelete = temp->next;
    		temp->next = temp->next->next;
    		--length;
    	}
    }

	delete toDelete;
	toDelete = NULL;
	return;
}

void scheduleSLL::reverse(){
	//scheduleSLL has 0 or 1 element
	if (length <= 1){
		return;
	}

	visitSlotNode* left = NULL;
	visitSlotNode* curr = head;
	visitSlotNode* right;

	while(curr != NULL){
		right = curr->next;
		curr->next = left;
		left = curr;
		curr = right;
	}
	head = left;
	return;
}

// ----------------------------- Scheduling Functions ---------------------------

void scheduleSLL::display_schedule(){
	cout << "---------- Schedule -------------" << endl;
    //if schedule is empty
    if(head == NULL){
        cout << "No appointments today." << endl;
        cout << "---------------------------------" << endl;
        return;
    }

    visitSlotNode* temp = head;
    int i=1;
    while(temp != NULL){
        cout << "(" << i++ << ")" << endl;
        cout << "Start Time: " << temp->startTime << " PM" << endl;
        cout << "End Time: " << temp->endTime << " PM" << endl;
        cout << "Total Visit Duration: 1 Hr" << endl;
        cout << "-----------------------------" << endl;
        temp = temp->next;
    }
}

void scheduleSLL::display_available_slots(){
	cout << "---------- Available slots -------------" << endl;

    visitSlotNode* temp = head;
    int k = 1;
    for (int i=1; i<6; i++){
    	if (temp == NULL || temp->startTime != i){
            cout << "(" << k++ << ")" << endl;
            cout << "Start Time: " << i << " PM" << endl;
            cout << "End Time: " << (i+1) << " PM" << endl;
            cout << "Total Visit Duration: 1 Hr" << endl;
            cout << "-----------------------------" << endl;
    	}
    	else{
    		temp = temp->next;
    	}
    }
}

void scheduleSLL::book_slot(int st){
	visitSlotNode* n = new visitSlotNode(st);

	//check if slot is valid
	if (n->validate_slot() && this->validate_slot(n)){
	    //if schedule is empty
	    if(head == NULL){
	        head = n;
	        length++;
		    cout << "Booking Successful!" << endl;
	        return;
	    }

	    //insert at end of schedule
	    visitSlotNode* temp = head;
	    while(temp->next != NULL){
	        temp = temp->next;
	    }
	    temp->next = n;
	    length++;
	    cout << "Booking Successful!" << endl;
	    return;
	}
}

void scheduleSLL::cancel_slot(int st){
    //scheduleSLL is empty
    if (head == NULL){
    	cout << "No bookings were made yet!";
    	return;
    }

    bool flag = false;

	visitSlotNode* toDelete = new visitSlotNode();
    //delete at head
    if (head->startTime == st){
    	toDelete = head;
    	//more than 1 visitSlotNode in scheduleSLL
    	if (head->next != NULL){
        	head = head->next;
    	}
    	//only one visitSlotNode
    	else{
    		head = NULL;
    	}
    	--length;
    	flag = true;
    }

    //delete anywhere
    else{
        visitSlotNode* temp = head;
        while(temp->next != NULL){
        	if (temp->next->startTime == st){
        		toDelete = temp->next;
        		temp->next = temp->next->next;
        		--length;
        		flag = true;
        		break;
        	}
        }
        //last visitSlotNode
    	if (temp->next->startTime == st){
    		toDelete = temp->next;
    		temp->next = temp->next->next;
    		--length;
    		flag = true;
    	}
    }

    if(flag){
    	delete toDelete;
    	toDelete = NULL;
    	cout << "Booking cancelled!" << endl;
    }
    else{
    	cout << "No such booking was made!" << endl;
    }

	return;
}

bool scheduleSLL::validate_slot(visitSlotNode n){
	visitSlotNode* temp = head;
	while(temp != NULL){
		if (temp->startTime == n.startTime){
			cout << "Slot is already booked!" << endl;
			return false;
		}
		temp = temp->next;
	}
	return true;
}

bool visitSlotNode::validate_slot(){
	if (this->startTime < daySt){
		cout << "Appointments available from 1 PM only!" << endl;
		return false;
	}
	else if (this->endTime > dayEt){
		cout << "Appointments available till 6 PM only!" << endl;
		return false;
	}
	return true;
}

void scheduleSLL::sort_schedule(){
	visitSlotNode* curr = head;
	while(curr != NULL){
		visitSlotNode* minNode = curr;
		visitSlotNode* temp = curr->next;
		while(temp != NULL){
			if (temp->startTime < minNode->startTime){
				minNode = temp;
			}
			temp = temp->next;
		}
		int minST = minNode->startTime;
		int minET = minNode->endTime;
		int minApt = minNode->aptNo;

		minNode->startTime = curr->startTime;
		minNode->endTime = curr->endTime;
		minNode->aptNo = curr->aptNo;

		curr->startTime = minST;
		curr->endTime = minET;
		curr->aptNo = minApt;

		curr = curr->next;
	}
}

// ----------------------------- Driver Code ------------------------------------

int main(){
	ios::sync_with_stdio(false);

	scheduleSLL schedule;
	int st = 0;

	//modular program
	cout << "Welcome to Reception!" << endl;
	cout << "How can we help you ?" << endl << endl;

	int choice = -1;
	while(choice){
		cout << "\n---------- OPTIONS ----------" << endl
			 << "1. Show Available Slots" << endl
			 << "2. Book Slot" << endl
			 << "3. Cancel Slot" << endl
			 << "4. Sort Schedule" << endl
			 << "5. Display Schedule" << endl
			 << "0. Exit" << endl
			 << "-----------------------------" << endl
			 << "Enter your choice = ";
		cin >> choice;
		cout << endl;

		switch(choice){
			case 0: //exit
			{
				cout << "\n :) Thank you ! Have a great day!" << endl;

				break;
			}

			case 1: // Show Available Slots
			{
				schedule.sort_schedule();
				schedule.display_available_slots();
				break;
			}

			case 2: // Book Slot
			{

				cout << "Enter Start time for booking appointment =" ;
				cin >> st;

				schedule.book_slot(st);
				break;
			}

			case 3: // Cancel Slot
			{
				cout << "Enter Start time for canceling appointment =" ;
				cin >> st;

				schedule.cancel_slot(st);
				break;
			}

			case 4: // sort schedule
			{
				schedule.sort_schedule();
				cout << "Schedule Sorted!" << endl;
				break;
			}

			case 5: // display schedule
			{
				schedule.display_schedule();
				break;
			}
		}
	}

	return 0;
}

