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

# include <iostream>
# include <climits>
using namespace std;

template <class T>
class node {
	T data;
	node<T> *left;
	node<T> *right;

public:
	// default constructor
	node(){
		left = right = NULL;
	}

	// parameterized constructor
	node(T data){
		this->data = data;
		left = right = NULL;
	}

	template <class B> friend class OBST;
};

// Optimal Binary Search Tree ------------------------------------------------------

template <class T>
class OBST {
	node<T> *root;

public:
	// default constructor
	OBST(){
		root = NULL;
	}

	// member functions

	node<T>* get_root(){
		return root;
	}

	void calculate_weight(double*, double*, int, T*);
	node<T>* create_tree(int, int, double**, T*);
	void inorder_traversal(node<T>* curr);

};

// DRIVER CODE -------------------------------------------------------------------

int main(){
	string input[] = {" ", "A1", "A2", "A3"};
	double p[] = {0.4, 0.1, 0.2};
	double q[] = {0.1, 0.04, 0.09, 0.07};

	OBST<string> tree;
	tree.calculate_weight(p, q, 3, input);
	tree.inorder_traversal(tree.get_root());
	return 0;
}

// DEFINITIONS -------------------------------------------------------------------

template<class T>
void OBST<T>::calculate_weight(double* p, double* q, int n, T* input) {
	// p = array of probability of successful search
	// q = array of probability of unsuccessful search
	// n = number of identifiers

	// Calculations matrix

	double** w = new double*[n+1];		// 2D matrix for weights
	for (int i=0; i<n+1; ++i){
		w[i] = new double[n+1];
	}

	double** c = new double*[n+1];		// 2D matrix for costs
	for (int i=0; i<n+1; ++i){
		c[i] = new double[n+1];
	}

	double** r = new double*[n+1];		// 2D matrix for roots
	for (int i=0; i<n+1; ++i){
		r[i] = new double[n+1];
	}

	for (int i=0; i<n; ++i){
		//calculate wts, costs of null tree
		w[i][i] = q[i];
		r[i][i] = c[i][i] = 0;

		//calculate wts, costs of tree with one node
		w[i][i+1] = q[i] + q[i+1] + p[i];
		r[i][i+1] = i+1;
		c[i][i+1] = w[i][i+1];
	}

	// for last entry
	w[n][n] = q[n];
	r[n][n] = c[n][n] = 0;

	//calculate wt and cost of tree having more than one node
	for (int m = 2; m <= n; ++m){
		// m = row number in calculations matrix
		for (int i=0; i<=n-m; ++i){
			double Min = 999;

			int j = i + m;
			int k = 0;
			w[i][j] = w[i][j-1] + p[j-1] + q[j];

			// find minimum cost
			// C<i,j> = min(i<k<= j){C<i,k-1> + C<k,j>} + W<i,j>

			for (int x = i+1; x <= j; ++x){
				// find minimum sum
					double sum = c[i][x-1] + c[x][j];
//					cout << "Before:" << Min << endl;
					if (sum < Min){
						Min = sum;
						k = x;
					}
//					cout << "After:" << Min << endl;
			}
			// set cost and root
			c[i][j] = w[i][j] + c[i][k-1] + c[k][j];
			r[i][j] = k;
		}
	}

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

template<class T>
node<T>* OBST<T>::create_tree(int i, int j, double** r, T* input) {
	if (i != j){
		int k = r[i][j];
		node<T> *t = new node<T>(input[k]);

		t->left = this->create_tree(i, k-1, r, input);
		t->right = this->create_tree(k, j, r, input);

		return t;
	}
	else{
		return NULL;
	}
}

template<class T>
void OBST<T>::inorder_traversal(node<T> *curr) {
	if (curr != NULL){
		this->inorder_traversal(curr->left);
		cout << curr->data << " ";
		this->inorder_traversal(curr->right);
	}
}
