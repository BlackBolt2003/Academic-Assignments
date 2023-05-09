/*
 * 21451_DSL_11.cpp
 *
 *  Created on: 24-Nov-2022
 *      Author: pict
 */
// ------------------------------------------------------------------------------------------------------------
/*Queues are frequently used in computer programming, and a typical example is the creation
of a job queue by an operating system.
If the operating system does not use priorities, then the jobs are processed in the order they enter the system.

Write C++ program for simulating job queue.
Write functions to 1) add job, 2) display job and  3) delete job from queue.*/
// ------------------------------------------------------------------------------------------------------------

# include <iostream>
using namespace std;

// ---------------------------- QUEUE ----------------------------

template <class T> class node{
	T data;
	node* next;

public:
	node(){
		data = 0;
		next = NULL;
	}

	node(T data){
		this->data = data;
		next = NULL;
	}

	template <class Q> friend class Queue;
};

template <class T> class Queue{
private:
	node<T>* front;
	node<T>* rear;

public:
	Queue(){
		front = NULL;
		rear = NULL;
	}

	bool isEmpty();
	void insert(T data);
	void remove();
	T peek();
	void display();
};

// ---------------------------- QUEUE FUNCTION DEFINITIONS ----------------------------

template <class T> bool Queue<T>::isEmpty(){
	if (rear == NULL) return true;
	else return false;
}

template <class T> void Queue<T>::insert(T data){
	node<T>* n = new node<T>(data);

	//empty queue
	if (this->isEmpty()){
		front = n;
		rear = n;
		return;
	}

	//non-empty queue - append at rear end
	rear->next = n;
	rear = n;
}

template <class T> void Queue<T>::remove(){
	if (this->isEmpty()){
		cout << "underflow" << endl;
		return;
	}

	//non-empty queue
	node<T>* todelete = front;
	front = front->next;

	if(front == NULL){
		rear = NULL;
	}

	delete todelete;
}

template <class T> T Queue<T>::peek(){
	if (this->isEmpty()){
		return -1;
	}
	return this->front->data;
}

template <class T> void Queue<T>::display(){
	while(!this->isEmpty()){
		cout << this->peek() << " ";
		this->remove();
	}
}

// --------------------------------- DRIVER CODE ------------------------------------

int main(){
	Queue<int> q;

	// ---------- MENU ------------
	int choice = -1;
	int temp = 0;

	while(choice){
		cout << "\n------- MENU -------" << endl
			 << "1. Add Job to Queue" << endl
			 << "2. Display Current Job" << endl
			 << "3. Remove Job from Queue" << endl
			 << "0. Exit" << endl
			 << "--------------------" << endl
			 << "Enter Your Choice = ";
		cin >> choice;

		switch(choice){
		case 1: //Add job
			cout << "Enter job ID = ";
			cin >> temp;
			q.insert(temp);
			cout << "Job added!" << endl;
			break;

		case 2: //display job
			if (q.isEmpty()){
				cout << "Queue is Empty" << endl;
				break;
			}
			cout << "Currently processing job with ID = " << q.peek() << endl;
			break;

		case 3: //remove job
			temp = q.peek();
			if (temp == -1){
				cout << "Queue is Empty" << endl;
				break;
			}
			q.remove();
			cout << "Removed job with ID = " << temp << endl;
			break;

		case 0: //exit
			while(!q.isEmpty()){
				q.remove();
			}
			cout << "All jobs removed" << endl;
			cout << "Exit" << endl;
			break;

		default:
			while(!q.isEmpty()){
				q.remove();
			}
			cout << "Error Occurred!" << endl;
			cout << "All jobs removed" << endl;
			cout << "Exit" << endl;
			break;
		}
	}

	return 0;
}
