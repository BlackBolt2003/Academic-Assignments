// ------------------------------------------------------------------------------------------------------------
/*Write program to implement a priority queue in C++ using an inorder list to store the
items in the queue. Create a class that includes the data items (which should be
template) and the priority (which should be int). The inorder list should contain these
objects, with operator <= overloaded so that the items with highest priority appear at the
start of the list (which will make it relatively easy to retrieve the highest item.)*/
// ------------------------------------------------------------------------------------------------------------

# include <iostream>
#define default_size 10
using namespace std;


// ----------------------------------- PRIORITY QUEUE DEFINITION ----------------------------------------------------

template <class T> class data{
	T info;
	int priority;

public:
	data(){
		info = 0;
		priority = 0;
	}

	data(T info, int p){
		this->info = info;
		this->priority = p;
	}

	void getData(T info, int p){
		this->info = info;
		this->priority = p;
	}

	bool operator <= (data<T> d2);

	template <class S> friend class priority_queue;
};

template <class T> bool data<T>::operator <= (data<T> d2){
	if (this->priority <= d2.priority){
		return true;
	}
	return false;
}

template <class T> class priority_queue{
	data<T>* elements;
	int front;
	int rear;
	int capacity;

public:
	priority_queue(){
		capacity = default_size;
		elements = new data<T>(default_size);
		front = -1;
		rear = -1;
	}

	priority_queue(int size){
		capacity = size;
		elements = new data<T>[size];
		front = -1;
		rear = -1;
	}

	bool isEmpty();

	void insert(data<T> d);
	void remove();

	T Front();

	void display();
};

// ----------------------------------- fUNCTION DEFINITIONS ---------------------------------------------------

template <class T> bool priority_queue<T>::isEmpty(){
	if(front == -1 || front == rear + 1){
		return true;
	}
	return false;
}

template <class T> void priority_queue<T>::insert(data<T> d){
    //queue is full
    if(rear == capacity-1){
        cout << "Overflow" << endl;
    	return;
    }

    //queue is empty
    if(front == -1){
            rear=0;
            front=0;
            elements[front]=d;
        	cout << "Data added!" << endl;
        	return;
    }

    //insertion sort
    int j=0;
    rear++;
    j=rear-1;

    while(this->elements[j] <= d && j>=0)
    {
    	elements[j+1] = elements[j];
        j--;

    }
    elements[j+1] = d;
    cout << "Data added!" << endl;
}

template <class T> void priority_queue<T>::remove(){
	if (this->isEmpty()){
		cout << "Underflow" << endl;
		return;
	}
	front++;
}

template <class T> T priority_queue<T>::Front(){
	if (this->isEmpty()){
		cout << "Underflow" << endl;
		return 0;
	}
	return this->elements[front].info;
}

template <class T> void priority_queue<T>::display(){
	while(!this->isEmpty()){
		cout << this->elements[front].info << " ";
		this->remove();
	}
	cout << endl;
}

// --------------------------------- DRIVER CODE ------------------------------------

int main(){
	priority_queue<int> q(10);

	// ---------- MENU ------------
	int choice = -1;
	int temp = 0;
	int prior = 0;
	data<int> d;

	while(choice){
		cout << "\n------- MENU -------" << endl
			 << "1. Insert data" << endl
			 << "2. Remove data" << endl
			 << "3. Display all data" << endl
			 << "0. Exit" << endl
			 << "--------------------" << endl
			 << "Enter Your Choice = ";
		cin >> choice;

		switch(choice){
		case 1: //Insert data
			cout << "Enter data = ";
			cin >> temp;
			cout << "Enter priority = ";
			cin >> prior;

			d.getData(temp, prior);
			q.insert(d);
			break;

		case 2: //Remove data
			temp = q.Front();
			if (q.isEmpty()){
				cout << "Queue is Empty" << endl;
				break;
			}
			q.remove();
			cout << "Removed data " << temp << endl;
			break;

		case 3: //Display all data
			cout << "Data in Queue : ";
			q.display();
			break;

		case 0: //exit
			while(!q.isEmpty()){
				q.remove();
			}
			cout << "All Data removed!" << endl;
			cout << "Exit" << endl;
			break;

		default:
			while(!q.isEmpty()){
				q.remove();
			}
			cout << "Error Occurred!" << endl;
			cout << "All Data removed!" << endl;
			cout << "Exit" << endl;
			break;
		}
	}

	return 0;
}








