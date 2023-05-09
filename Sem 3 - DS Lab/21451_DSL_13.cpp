/*
 * 21451_DSL_13.cpp
 *
 *  Created on: 30-Nov-2022
 *      Author: pict
 */
// ------------------------------------------------------------------------------------------------------------
/*A double-ended queue (deque) is a linear list in which additions and deletions may be made
at either end. Obtain a data representation mapping a deque into a one dimensional array.
Write C++ program to simulate deque with functions to add and delete elements from either
end of the deque.*/
// ------------------------------------------------------------------------------------------------------------

# include <iostream>
#define default_size 10
using namespace std;


// ----------------------------------- DEQUEUE DEFINITION ----------------------------------------------------
template <class T> class dequeue{
	T* elements;
	int front;
	int rear;
	int capacity;

public:
	dequeue(){
		capacity = default_size;
		elements = new T(default_size);
		front = -1;
		rear = -1;
	}

	dequeue(int size){
		capacity = size;
		elements = new T[size];
		front = -1;
		rear = -1;
	}

	dequeue(int size, int front){
		capacity = size;
		elements = new T[size];
		this->front = front;
		this->rear = front;
	}

	bool isEmpty();

	void insert_at_front(T data);
	void insert_at_rear(T data);

	void remove_at_front();
	void remove_at_rear();

	T Front();
	T Rear();

	void display();
	void display_reverse();
};

// ----------------------------------- fUNCTION DEFINITIONS ---------------------------------------------------

template <class T> bool dequeue<T>::isEmpty(){
	if(front == -1 || front == rear + 1){
		return true;
	}
	return false;
}

template <class T> void dequeue<T>::insert_at_front(T data){
	if(front == 0){
		cout << "cannot insert" << endl;
		return;
	}

	if(this->isEmpty()){
		front = rear = 0;
	}
	else{
		front--;
	}
	this->elements[front] = data;
	cout << "Data added!" << endl;
}

template <class T> void dequeue<T>::insert_at_rear(T data){
	if(rear == this->capacity - 1){
		cout << "Overflow" << endl;
		return;
	}

	if(front == -1){
		front = 0;
	}
	rear++;
	this->elements[rear] = data;
	cout << "Data added!" << endl;
}

template <class T> void dequeue<T>::remove_at_front(){
	if (this->isEmpty()){
		cout << "Underflow" << endl;
		return;
	}
	front++;
}

template <class T> void dequeue<T>::remove_at_rear(){
	if (this->isEmpty()){
		cout << "Underflow" << endl;
		return;
	}
	rear--;
}

template <class T> T dequeue<T>::Front(){
	if (this->isEmpty()){
		cout << "Underflow" << endl;
		return 0;
	}
	return this->elements[front];
}

template <class T> T dequeue<T>::Rear(){
	if (this->isEmpty()){
		cout << "Underflow" << endl;
		return 0;
	}
	return this->elements[rear];
}

template <class T> void dequeue<T>::display(){
	while(!this->isEmpty()){
		cout << this->elements[front] << " ";
		this->remove_at_front();
	}
	cout << endl;
}

template <class T> void dequeue<T>::display_reverse(){
	while(!this->isEmpty()){
		cout << this->elements[rear] << " ";
		this->remove_at_rear();
	}
	cout << endl;
}

// --------------------------------- DRIVER CODE ------------------------------------

int main(){
	dequeue<int> q(6, 2);

	// ---------- MENU ------------
	int choice = -1;
	int temp = 0;

	while(choice){
		cout << "\n------- MENU -------" << endl
			 << "1. Insert data at front" << endl
			 << "2. Insert data at rear" << endl
			 << "3. Remove data at front" << endl
			 << "4. Remove data at rear" << endl
			 << "5. Display all data from front" << endl
			 << "6. Display all data from rear" << endl
			 << "0. Exit" << endl
			 << "--------------------" << endl
			 << "Enter Your Choice = ";
		cin >> choice;

		switch(choice){
		case 1: //Insert data at front
			cout << "Enter data = ";
			cin >> temp;
			q.insert_at_front(temp);
			break;

		case 2: //Insert data at rear
			cout << "Enter data = ";
			cin >> temp;
			q.insert_at_rear(temp);
			break;

		case 3: //Remove data at front
			temp = q.Front();
			if (q.isEmpty()){
				cout << "Queue is Empty" << endl;
				break;
			}
			q.remove_at_front();
			cout << "Removed data " << temp << endl;
			break;

		case 4: //Remove data at rear
			temp = q.Rear();
			if (q.isEmpty()){
				cout << "Queue is Empty" << endl;
				break;
			}
			q.remove_at_rear();
			cout << "Removed data " << temp << endl;
			break;

		case 5: //Display all data from front
			cout << "Data in Queue from front : ";
			q.display();
			break;

		case 6: //Display all data from rear
			cout << "Data in Queue from rear : ";
			q.display_reverse();
			break;

		case 0: //exit
			while(!q.isEmpty()){
				q.remove_at_front();
			}
			cout << "All Data removed!" << endl;
			cout << "Exit" << endl;
			break;

		default:
			while(!q.isEmpty()){
				q.remove_at_front();
			}
			cout << "Error Occurred!" << endl;
			cout << "All Data removed!" << endl;
			cout << "Exit" << endl;
			break;
		}
	}

	return 0;
}








