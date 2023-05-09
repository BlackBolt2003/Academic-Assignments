/*
 * 21451_DSL_10.cpp
 *
 *  Created on: 24-Nov-2022
 *      Author: pict
 */
// ---------------------------------------------------------------------------
/*
Implement C++ program for expression conversion as infix to post-fix and its evaluation
using stack based on given conditions:
1. Operands and operator, both must be single character.
2. Input Post-fix expression must be in a desired format.
3. Only '+', '-', '*' and '/ ' operators are expected.
*/
// ---------------------------------------------------------------------------

# include <iostream>
# include <math.h>
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

// ------------------------------ EVALUATION FUNCTIONS ----------------------------

int precedence(char ch){
	if (ch == '+' || ch == '-'){
		return 1;
	}
	if (ch == '*' || ch == '/'){
		return 2;
	}
	if (ch == '^'){
		return 3;
	}
	// Default handler
	return -1;
}

string infix_to_postfix(string s){
	string res = "";
	Stack<char> st;

	for(auto ch : s){
		// opening brace
		if (ch == '('){
			st.push(ch);
		}

		//closing brace
		else if(ch == ')'){
			while(st.Top() != '('){
				res += st.get_and_pop();
			}
			st.pop();
		}

		//operator occurs
		else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'){
			while (!st.isEmpty() && precedence(ch) <= precedence(st.Top())){
				res += st.get_and_pop();
			}
			st.push(ch);
		}

		//operand occurs
		else if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
			res += ch;
		}
	}

	//pop remaining stack elements
	while(!st.isEmpty()){
		res += st.get_and_pop();
	}

	return res;
}

int evaluate_postfix(string s){
	int ans = 0;
	Stack<int> st;
	int op2 = 0;

	for (auto ch : s){
		//operand
		if (ch >= '0' && ch <= '9'){
			st.push(ch - '0');
		}

		//operator
		switch(ch){
		case '+':
		{
			ans = st.get_and_pop() + st.get_and_pop();
			st.push(ans);
			break;
		}
		case '-':
		{
			op2 = st.get_and_pop();
			ans = st.get_and_pop() - op2;
			st.push(ans);
			break;
		}
		case '*':
		{
			ans = st.get_and_pop() * st.get_and_pop();
			st.push(ans);
			break;
		}
		case '/':
		{
			op2 = st.get_and_pop();
			ans = st.get_and_pop() / op2;
			st.push(ans);
			break;
		}
		case '^':
		{
			op2 = st.get_and_pop();
			ans = pow(st.get_and_pop(),op2);
			st.push(ans);
			break;
		}
		default:
			break;
		}
	}
	ans = st.get_and_pop();
	return ans;
}


// --------------------------------- DRIVER CODE ------------------------------------

int main(){
	string s1 = "((9-2)*4)+2";
	cout << "infix = " << s1 << endl;
	cout << "postfix = " << infix_to_postfix(s1) << endl;
	s1 = infix_to_postfix(s1);
	cout << "ans = " << evaluate_postfix(s1) << endl << endl;

	string s2 = "((3*(5+3))^2)/5";
	cout << "infix = " << s2 << endl;
	cout << "postfix = " <<  infix_to_postfix(s2) << endl;
	s2 = infix_to_postfix(s2);
	cout << "ans = " << evaluate_postfix(s2) << endl << endl;

	string s;
	cout << "Enter Infix Expression = ";
	cin >> s;
	s = infix_to_postfix(s);
	cout << "postfix = " << s << endl;
	cout << "ans = " << evaluate_postfix(s) << endl;
	return 0;
}
















