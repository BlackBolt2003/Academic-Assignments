/*
 * 21451_Assignment_08.cpp
 *
 *  Created on: 09-May-2023
 *      Author: student
 */
/* PROBLEM STATEMENT ------------------------------------------------------------------

Given sequence k = k1 <k2 < ... <kn of n sorted keys, with a search probability pi
for each key ki. Build the Binary search tree that has the least search cost given
the access probability for each key.

------------------------------------------------------------------------------------ */

#include <iostream>
#include <climits>
using namespace std;

template <class T>
class node
{
	T data;
	node<T> *left;
	node<T> *right;

public:
	// default constructor
	node()
	{
		left = right = NULL;
	}

	// parameterized constructor
	node(T data)
	{
		this->data = data;
		left = right = NULL;
	}

	template <class B>
	friend class OBST;
};

// Optimal Binary Search Tree ------------------------------------------------------

template <class T>
class OBST
{
	node<T> *root;

public:
	// default constructor
	OBST()
	{
		root = NULL;
	}

	// getter
	node<T> *get_root()
	{
		return this->root;
	}

	// member functions
	void calculate_weight(double *, double *, int, T *);
	node<T> *create_tree(int, int, double **, T *);

	void inorder_traversal(node<T> *curr);
	void preorder_traversal(node<T> *curr);
	void postorder_traversal(node<T> *curr);
};

// DRIVER CODE -------------------------------------------------------------------

int main()
{
	OBST<string> ST;
	int choice = -1;
	int temp = 0;

	cout << "# Implementation of OBST\n";

	while (choice)
	{
		cout << "\n---------- MENU ----------\n"
			 << "1. Input identifiers\n"
			 << "2. Inorder Traversal\n"
			 << "3. Preorder Traversal\n"
			 << "4. Postorder Traversal\n"
			 << "0. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch (choice)
		{
		case 1: // Input identifiers
		{
			cout << "Enter no. of identifiers = ";
			cin >> temp;
			string *input = new string[temp + 1];
			double *p = new double[temp];
			double *q = new double[temp + 1];
			cout << "Enter identifiers = " << endl;

			input[0] = "NULL"; // dummy node
			for (int i = 0; i < temp; ++i)
			{
				cout << "Enter identifier " << i + 1 << " = ";
				cin >> input[i + 1];
			}
			cout << "Enter probabilities of successful search = " << endl;
			for (int i = 0; i < temp; ++i)
			{
				cout << "Enter probability " << i + 1 << " = ";
				cin >> p[i];
			}
			cout << "Enter probabilities of unsuccessful search = " << endl;
			for (int i = 0; i < temp + 1; ++i)
			{
				cout << "Enter probability " << i + 1 << " = ";
				cin >> q[i];
			}
			ST.calculate_weight(p, q, temp, input);
			break;
		}

		case 2: // Inorder Traversal
		{
			cout << "Inorder Traversal = " << endl;
			ST.inorder_traversal(ST.get_root());
			break;
		}

		case 3: // Preorder Traversal
		{
			cout << "Preorder Traversal = " << endl;
			ST.preorder_traversal(ST.get_root());
			break;
		}

		case 4: // Postorder Traversal
		{
			cout << "Postorder Traversal = " << endl;
			ST.postorder_traversal(ST.get_root());
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
void OBST<T>::calculate_weight(double *p, double *q, int n, T *input)
{
	// p = array of probability of successful search
	// q = array of probability of unsuccessful search
	// n = number of identifiers

	// Calculations matrix

	double **w = new double *[n + 1]; // 2D matrix for weights
	for (int i = 0; i < n + 1; ++i)
	{
		w[i] = new double[n + 1];
	}

	double **c = new double *[n + 1]; // 2D matrix for costs
	for (int i = 0; i < n + 1; ++i)
	{
		c[i] = new double[n + 1];
	}

	double **r = new double *[n + 1]; // 2D matrix for roots
	for (int i = 0; i < n + 1; ++i)
	{
		r[i] = new double[n + 1];
	}

	for (int i = 0; i < n; ++i)
	{
		// calculate wts, costs of null tree
		w[i][i] = q[i];
		r[i][i] = c[i][i] = 0;

		// calculate wts, costs of tree with one node
		w[i][i + 1] = q[i] + q[i + 1] + p[i];
		r[i][i + 1] = i + 1;
		c[i][i + 1] = w[i][i + 1];
	}

	// for last entry
	w[n][n] = q[n];
	r[n][n] = c[n][n] = 0;

	// calculate wt and cost of tree having more than one node
	for (int m = 2; m <= n; ++m)
	{
		// m = row number in calculations matrix
		for (int i = 0; i <= n - m; ++i)
		{
			double Min = 999;

			int j = i + m;
			int k = 0;
			w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

			// find minimum cost :
			// C<i,j> = min(i<k<= j){C<i,k-1> + C<k,j>} + W<i,j>

			for (int x = i + 1; x <= j; ++x)
			{
				// find minimum sum
				double sum = c[i][x - 1] + c[x][j];
				//					cout << "Before:" << Min << endl;
				if (sum < Min)
				{
					Min = sum;
					k = x;
				}
				//					cout << "After:" << Min << endl;
			}
			// set cost and root
			c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
			r[i][j] = k;
		}
	}

	// 	To check if calculations matrix values are correct or not :
	//	for (int i=0; i<n+1; ++i){
	//		for(int j=0; j<n+1; ++j){
	//			cout << w[i][j] << "\t";
	//			cout << c[i][j] << "\t";
	//			cout << r[i][j] << "\t";
	//		}
	//		cout << "\n";
	//	}

	this->root = this->create_tree(0, n, r, input);
}

template <class T>
node<T> *OBST<T>::create_tree(int i, int j, double **r, T *input)
{
	if (i != j)
	{
		int k = r[i][j];
		node<T> *t = new node<T>(input[k]);

		t->left = this->create_tree(i, k - 1, r, input);
		t->right = this->create_tree(k, j, r, input);

		return t;
	}
	else
	{
		return NULL;
	}
}

template <class T>
void OBST<T>::inorder_traversal(node<T> *curr)
{
	if (curr != NULL)
	{
		this->inorder_traversal(curr->left);
		cout << curr->data << " ";
		this->inorder_traversal(curr->right);
	}
}

template <class T>
void OBST<T>::preorder_traversal(node<T> *curr)
{
	if (curr != NULL)
	{
		cout << curr->data << " ";
		this->preorder_traversal(curr->left);
		this->preorder_traversal(curr->right);
	}
}

template <class T>
void OBST<T>::postorder_traversal(node<T> *curr)
{
	if (curr != NULL)
	{
		this->postorder_traversal(curr->left);
		this->postorder_traversal(curr->right);
		cout << curr->data << " ";
	}
}

// TEST CASES -------------------------------------------------------------------

// Test Case - 1

// string input[] = {" ", "do", "if", "while"};
// double p[] = {0.5, 0.1, 0.05};
// double q[] = {0.15, 0.1, 0.05, 0.05};
// OBST<string> tree;
// tree.calculate_weight(p, q, 3, input);
// tree.inorder_traversal(tree.get_root());

// Test Case - 2

//	string input[] = {" ", "A1", "A2", "A3"};
//	double p[] = {0.4, 0.1, 0.2};
//	double q[] = {0.1, 0.04, 0.09, 0.07};
// OBST<string> tree;
// tree.calculate_weight(p, q, 3, input);
// tree.inorder_traversal(tree.get_root());