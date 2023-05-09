/*
 * 21451_DSL_09.cpp
 *
 *  Created on: 23-Nov-2022
 *      Author: pict
 */
// -----------------------------------------------------------------------------------------
// Write C++ program using stack to check whether given expression is well-parenthesized or not.
// -----------------------------------------------------------------------------------------

# include <iostream>
using namespace std;

// ---------------------------- STACK ----------------------------

template <class T> class node{

	T data;
	node<T>* prev;

public:
	node(){
		data = 0;
		prev = NULL;
	}

	node(int val){
		data = val;
		prev = NULL;
	}

	 template <class S> friend class Stack;
};

template <class T> class Stack{
	node<T>* top;

public:
	Stack(){
		top = NULL;
	}

	void push(int val);
	void pop();
	bool isEmpty();
	T Top();
	T get_and_pop();
	void display();
};

// ---------------------------- STACK FUNCTION DEFINITIONS ----------------------------

template <class T> bool Stack<T>::isEmpty(){
	if (top == NULL){
		return true;
	}
	return false;
}

template <class T> void Stack<T>::push(int val){
    node<T>* n = new node<T>(val);

    // stack is empty
    if (this->isEmpty()){
        top = n;
        return;
    }

    n->prev = top;
    top = n;
    return;
}

template <class T> void Stack<T>::pop(){
    // stack is empty
    if (this->isEmpty()){
    	cout << "stack underflow" << endl;
        return;
    }

    node<T>* toDelete = top;
    top = top->prev;

    delete toDelete;
    toDelete = NULL;
    return;
}

template <class T> T Stack<T>::Top(){
	if (this->isEmpty()){
		return -1;
	}
	return top->data;
}

template <class T> T Stack<T>::get_and_pop(){
    // stack is empty
    if (this->isEmpty()){
        return -1;
    }

    node<T>* toDelete = top;
    top = top->prev;

    int popped = toDelete->data;

    delete toDelete;
    toDelete = NULL;

    return popped;
}

template <class T> void Stack<T>::display(){
	while(! this->isEmpty()){
		cout << this->get_and_pop() << endl;
	}
}

// ---------------------- PARENTHISIS CHECKER -----------------------

bool check_parenthisis(string s){
	Stack<char> st;
	for(auto ele : s){
		if (ele == '{' || ele == '(' || ele == '['){
			st.push(ele);
		}
		else if (ele == '}'){
			char temp = st.get_and_pop();
			if (temp == '{'){
				continue;
			}
			else{
				cout << "Unbalanced occurrence of : " << ele << endl;
				return false;
			}
		}
		else if (ele == ']'){
			char temp = st.get_and_pop();
			if (temp == '['){
				continue;
			}
			else{
				cout << "Unbalanced occurrence of : " << ele << endl;
				return false;
			}
		}
		else if (ele == ')'){
			char temp = st.get_and_pop();
			if (temp == '('){
				continue;
			}
			else{
				cout << "Unbalanced occurrence of : " << ele << endl;
				return false;
			}
		}
	}
	if(st.isEmpty()){
		return true;
	}

	cout << "Unbalanced occurrence of : " << st.Top() << endl;
	return false;
}

// --------------------------- DRIVER CODE --------------------------

int main(){

	// ------------- basic functions -----------
/*
	Stack<int> s;
	cout << s.Top() << endl;
	s.push(5);
	s.push(3);
	s.push(1);

	while(!s.isEmpty()){
		cout << s.Top() << endl;
		s.pop();
	}

	Stack<char> sc;
	sc.push('a');
	sc.push('b');
	sc.push('c');

	while(!sc.isEmpty()){
		cout << sc.get_and_pop() << endl;
	}

	Stack<int> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);

	s1.display();
*/

	// -------- Assignment ------------

	string msg;

	string s = "{a + b*[c - (d*e)]}";
	(check_parenthisis(s))?(msg = "Well Balanced!"):(msg = "Not Balanced!");
	cout << msg << endl << endl;

	s = "{10 *[3 - 8)] + 9}";
	(check_parenthisis(s))?(msg = "Well Balanced!"):(msg = "Not Balanced!");
	cout << msg << endl << endl;

	s = "{a*b - [1 / (2+c)] + a*d";
	(check_parenthisis(s))?(msg = "Well Balanced!"):(msg = "Not Balanced!");
	cout << msg << endl << endl;

	s = "{p - q*[z + a/(5 + [r* {a - 4}])] / b}";
	(check_parenthisis(s))?(msg = "Well Balanced!"):(msg = "Not Balanced!");
	cout << msg << endl << endl;



	return 0;
}
