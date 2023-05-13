/*
 * 21451_Assignment_10.cpp
 *
 *  Created on: 12-May-2023
 *      Author: student
 */
/* PROBLEM STATEMENT ------------------------------------------------------------------

Implement the Heap sort algorithm demonstrating heap data structure with
modularity of programming language.
OR
Read the marks obtained by students of second year in an online examination of
particular subject. Find out maximum / minimum marks obtained in that subject.
Use heap data structure. Analyze the algorithm.

------------------------------------------------------------------------------------ */

#include <iostream>
#include <climits>
using namespace std;

// Binary Heap (MinHeap) ------------------------------------------------------

template <class T>
class MinHeap
{
	T *arr;		  // array representation of heap
	int capacity; // maximum possible size of heap
	int size;	  // current no. of elements in heap

public:
	// constructor
	MinHeap()
	{
		capacity = 0;
		size = 0;
		arr = NULL;
	}

	// parameterized constructor
	MinHeap(int capacity)
	{
		this->capacity = capacity;
		size = 0;
		arr = new T[capacity];
	}

	// setter
	void setCapacity(int capacity)
	{
		this->capacity = capacity;
		size = 0;
		arr = new T[capacity];
	}

	// methods
	void insert(T data); // inserts element in heap
	T getMin();			 // returns minimum element

	void heapify(int i); // recursive heapify
	void heapify_itr();	 // iterative heapify
	void display();		 // display heap

	void remove(int i);			   // removes element at index i
	T extract_min_key();		   // removes minimum element
	void bubble_key_to_top(int i); // bubbles key at index i to top of heap

	// utility functions
	int parent(int i) // returns index of parent of node at index i
	{
		return (i - 1) / 2;
	}

	int Lchild(int i) // returns index of left child of node at index i
	{
		return (2 * 1 + 1);
	}

	int Rchild(int i) // returns index of right child of node at index i
	{
		return (2 * 1 + 2);
	}

	void swap(int a, int b)
	{
		// input : indices to swap between
		T temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}
};

// FUNCTIONS -----------------------------------------------------------------------
template <class T>
T *heap_sort(T *arr, int n) // sorts array using heap sort in-place
{
	// arr = array to be sorted
	// n = size of array
	MinHeap<T> heap(n);
	for (int i = 0; i < n; ++i)
	{ // insert all elements in heap
		heap.insert(arr[i]);
	}
	for (int i = 0; i < n; ++i)
	{ // extract minimum element n times
		arr[i] = heap.extract_min_key();
	}

	return arr;
}

// DRIVER CODE -------------------------------------------------------------------

int main()
{
	MinHeap<int> heap;
	int choice = -1;
	int temp = 0;
	int marksLength;
	int *marks = NULL;

	cout << "# Implementation of Heap DS and Heap Sort\n";

	while (choice)
	{
		cout << "\n---------- MENU ----------\n"
			 << "1. Input Marks of students\n"
			 << "2. Get minimum marks obtained\n"
			 << "3. Heap sort on marks\n"
			 << "4. Display heap\n"
			 << "0. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch (choice)
		{
		case 1: // Input Marks
		{
			cout << "Enter no. of entries = ";
			cin >> marksLength;
			heap.setCapacity(marksLength);
			marks = new int[marksLength];
			cout << "Enter Marks of students =" << endl;
			for (int i = 0; i < marksLength; ++i)
			{
				cout << "Enter marks of student " << i + 1 << " = ";
				cin >> marks[i];
				heap.insert(marks[i]);
			}
			break;
		}

		case 2: // Get minimum marks
		{
			temp = heap.getMin();
			if (temp != -1)
			{
				cout << "Minimum marks obtained = " << temp << endl;
			}
			else
			{
				for (int i = 0; i < marksLength; ++i)
				{
					heap.insert(marks[i]);
				}
				cout << "Minimum marks obtained = " << heap.getMin() << endl;
			}
			break;
		}

		case 3: // Heap Sort
		{
			cout << "Heap Sort = " << endl;
			int *sortedMarks = heap_sort(marks, marksLength);
			for (int i = 0; i < marksLength; ++i)
			{
				cout << sortedMarks[i] << " ";
			}
			cout << endl;
			break;
		}

		case 4: // Display heap
		{
			temp = heap.getMin();
			if (temp != -1)
			{
				heap.display();
			}
			else
			{
				for (int i = 0; i < marksLength; ++i)
				{
					heap.insert(marks[i]);
				}
				heap.display();
			}
			break;
		}

		case 0: // Exit
		{
			cout << "Thank you :)" << endl;
			break;
		}

		default: // Forced exit
		{
			cout << "# Forced exit due to error" << endl;
			exit(0);
		}
		}
	}

	return 0;
}

// DEFINITIONS -------------------------------------------------------------------

template <class T>
void MinHeap<T>::insert(T data)
{
	// overflow
	if (size == capacity)
	{
		cout << "Overflow: could not insert key" << endl;
	}
	else
	{

		// insert the new key at end of heap
		size++;
		int i = size - 1;
		arr[i] = data;

		// if min heap property is violated, make adjustments
		while (i >= 0 && arr[this->parent(i)] > arr[i])
		{
			// violation : parent is smaller than current node
			// adjustment : swap min element with parent
			swap(parent(i), i);
			// check again for new position of new node
			i = this->parent(i);
		}
	}
}

template <class T>
T MinHeap<T>::getMin()
{
	if (size <= 1) // underflow
	{
		cout << "Underflow: no element in heap" << endl;
		return -1;
	}
	else
	{ // return min element
		return arr[0];
	}
}

template <class T>
void MinHeap<T>::heapify(int i)
{
	// A recursive method to heapify a subtree with the root at given index
	// This method assumes that the subtrees are already heapified

	// identify children of node
	int l = Lchild(i);
	int r = Rchild(i);

	// initial assumption: current node is smallest
	int smallest = i;

	// check if min heap property is violated
	// condition-1: child exists (< size)
	// condition-2: child is smaller
	if (l < size && arr[l] < arr[smallest])
	{
		smallest = l;
	}
	if (r < size && arr[r] < arr[smallest])
	{
		smallest = r;
	}

	// swap current node with smaller node
	if (smallest != i)
	{
		// condition: current node is not smallest
		swap(i, smallest);
		// check again for new position of node
		heapify(smallest);
	}
}

template <class T>
void MinHeap<T>::heapify_itr()
{ // iterative version of heapify
	MinHeap<T> tempHeap(this->capacity);

	for (int i = 0; i < size; ++i)
	{ // copy elements to temp heap in order to heapify them
		tempHeap.insert(this->arr[i]);
	}

	for (int i = 0; i < size; ++i)
	{
		this->arr[i] = tempHeap.arr[i];
	}
}

template <class T>
void MinHeap<T>::display()
{
	cout << "Level Order Traversal: ";
	for (int i = 0; i < size; ++i)
	{ // print all elements
		cout << arr[i] << " ";
	}
	cout << endl;
}

template <class T>
void MinHeap<T>::remove(int i)
{
	// Purpose: Delete a desired key from heap

	this->bubble_key_to_top(i); // make desired key as min key and make it root (top) of heap
	this->extract_min_key();	// remove min key (root) from heap
}

template <class T>
T MinHeap<T>::extract_min_key()
{
	// Purpose: Remove min key (root) and return it

	// store min value
	T minKey = arr[0];
	// Store last value as min value
	arr[0] = arr[size - 1];
	// Logically remove last value
	size--;
	// Put fake min key (root) at its correct position
	heapify_itr();

	return minKey;
}

template <class T>
void MinHeap<T>::bubble_key_to_top(int i)
{
	// Purpose: Make a desired key as min key and make it root

	// Make desired key the min key
	arr[i] = INT_MIN;

	//
	// if min heap property is violated, make adjustments
	while (i != 0 && arr[parent(i)] > arr[i])
	{
		// violation : parent is smaller than current node
		// adjustment : swap min element with parent
		swap(parent(i), i);
		// check again for new position of new node
		i = parent(i);
	}
}

// TEST CASES --------------------------------------------------------------------
// int input[] = {20, 10, 30, 15, 9, 5};
// MinHeap<int> heap(10);

// for (int i = 0; i < 6; ++i)
// {
// 	heap.insert(input[i]);
// 	heap.display();
// }

// heap.remove(4);
// heap.display();

// OUTPUT :
// Minimum marks obtained = 3
// Heap Sort = 3 10 18 22 34
// Level order traversal = 3 10 22 34 18