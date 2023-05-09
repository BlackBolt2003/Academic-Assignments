/*
 * 21451_Assignment_02.cpp
 *
 *  Created on: 24-Feb-2023
 *      Author: student
 */
// Beginning with an empty binary tree, Construct binary tree by inserting the values
// in the order given. After constructing a binary tree perform following operations
// on it-
// *1) Perform in-order, pre-order and post-order traversal
// *2) Change a tree so that the roles of the left and right pointers are swapped at every node
// *3) Find the height of tree
// *4) Copy this tree to another [operator=]
// 5) Count number of leaves, number of internal nodes.
// *6) Erase all nodes in a binary tree.
// (Implement both recursive and non-recursive methods)

// --------------------------------------------------------------------------------------------

# include <iostream>
# include <queue>
# include <stack>

using namespace std;
# define _ NULL

// CLASSES ------------------------------------------------------------------------------------
template <class T> class node{
	T data;
	node<T> *left, *right;

public:
	node(){
		left = right = _;
	}

	node(T data){
		this->data = data;
		left = right = _;
	}

	template <class S> friend class BinaryTree;
};

template <class T> class BinaryTree{
	node<T> *root;

public:
	BinaryTree(){
		root = _;
	}

	void setRoot(node<T>* root){
		this->root = root;
	}

	node<T>* getRoot(){
		return root;
	}

	// recursive
	node<T>* create();

	void inorder_rec(node<T> *curr);
	void preorder_rec(node<T> *curr);
	void postorder_rec(node<T> *curr);

	void mirror(node<T>* curr);
	int height_rec(node<T>* curr);

	void operator = (BinaryTree<T> bt);
	node<T>* copyTree(node<T>* curr);

	void eraseTree(node<T> *curr);
	void calc_nodes(node<T> *curr, int &total, int &leaf);

	// iterative
	void insert(T data);

	void inorder();
	void preorder();
	void postorder();

	int height();

};

// RECURSIVE METHODS----------------------------------------------------------------------------

// recursive create
template <class T> node<T>* BinaryTree<T> :: create(){
	T data;
	cout << "Enter data (-1 if none) = ";
	cin >> data;

	if (data == -1){
		return _;
	}
	else{
		node<T>* p = new node<T>(data);

		cout << "Is " << data << " a leaf node? [1/0] = ";
		bool leaf;
		cin >> leaf;

		if(leaf){
			return p;
		}
		else{

			cout << "Left child of " << data << " : ";
			p->left = create();

			cout << "Right child of " << data << " : ";
			p->right = create();
		}
		return p;
	}
}

// recursive in-order traversal
template <class T> void BinaryTree<T> :: inorder_rec(node<T> *curr){
	if(curr != _){
		this->inorder_rec(curr->left);
		cout << curr->data << " ";
		this->inorder_rec(curr->right);
	}
}

// recursive pre-order traversal
template <class T> void BinaryTree<T> :: preorder_rec(node<T>* curr){
	if(curr != _){
		cout << curr->data << " ";
		this->preorder_rec(curr->left);
		this->preorder_rec(curr->right);
	}
}

// recursive post-order traversal
template <class T> void BinaryTree<T> :: postorder_rec(node<T>* curr){
	if(curr != _){
		this->postorder_rec(curr->left);
		this->postorder_rec(curr->right);
		cout << curr->data << " ";
	}
}

// recursive mirroring
template <class T> void BinaryTree<T> :: mirror(node<T>* curr){
	if (curr != _){
		// swap children
		node<T>* temp = curr->left;
		curr->left = curr->right;
		curr->right = temp;

		// recursive mirror
		this->mirror(curr->left);
		this->mirror(curr->right);
	}
}

// find height of tree using recursion
template <class T> int BinaryTree<T> :: height_rec(node<T>* curr){
	if (curr == _){
		return -1;
	}

	int leftHeight = height_rec(curr->left);
	int rightHeight = height_rec(curr->right);

	return (max(leftHeight, rightHeight) + 1);
}

// overloaded = operator to copy tree
template <class T> void BinaryTree<T> ::operator = (BinaryTree<T> bt){
	this->root = bt.copyTree(bt.getRoot());
}

// copy contents of tree
template <class T> node<T>* BinaryTree<T> :: copyTree(node<T>* curr){
	node<T> *copyNode = _;

	if(curr == _){
		return _;
	}

	else {
		copyNode = new node<T>(curr->data);
		copyNode->left = copyTree(curr->left);
		copyNode->right = copyTree(curr->right);
	}

	return copyNode;
}

// delete all nodes of tree
template <class T> void BinaryTree<T> :: eraseTree(node<T> *curr){
	if(curr != _){
		eraseTree(curr->left);
		eraseTree(curr->right);

		delete curr;
		curr = _;
	}
	else{
		return;
	}
}

template <class T> void BinaryTree<T> :: calc_nodes(node<T> *curr, int &total, int &leaf){
	if(curr != _){
		total++;
		if (curr->left == _ && curr->right == _){
			leaf++;
			return;
		}
		else{
			this->calc_nodes(curr->left, total, leaf);
			this->calc_nodes(curr->right, total, leaf);
		}
	}
}

// ITERATIVE METHODS----------------------------------------------------------------------------

// iterative insert
template <class T> void BinaryTree<T> :: insert(T data){
	if (root == _){
		root = new node<T>(data);
		return;
	}

	queue< node<T>* > q;
	q.push(root);

	while(!q.empty()){
		node<T> *temp = q.front();
		q.pop();

		// check if left child is present
		if (temp->left != _){
			q.push(temp->left);
		} else {
			temp->left = new node<T>(data);
			return;
		}

		// check if right child is present
		if (temp->right != _){
			q.push(temp->right);
		} else{
			temp->right = new node<T>(data);
			return;
		}
	}
}

// iterative in-order traversal
template <class T> void BinaryTree<T> :: inorder(){
	stack<node<T>*> st;
	node<T> *temp = this->root;

	while(!st.empty() || temp != _){
		if (temp != _){
			st.push(temp);
			temp = temp->left;
		}
		else{
			temp = st.top();
			st.pop();
			cout << temp->data << " ";
			temp = temp->right;
		}
	}
}

// iterative pre-order traversal
template <class T> void BinaryTree<T> :: preorder(){
	stack<node<T>*> st;
	node<T>* temp = root;
	st.push(temp);

	while(!st.empty()){
		if(temp != _){
			cout << temp->data << " ";
			if(temp->right != _){
				st.push(temp->right);
			}
			if(temp->left != _){
				temp = temp->left;
			}
			else{
				temp = st.top();
				st.pop();
			}
		}
	}

}

// iterative post-order traversal
template <class T> void BinaryTree<T> :: postorder(){
	stack<node<T>*> s1;		//children
	stack<node<T>*> s2;		//parent

	node<T> *temp = root;
	node<T> *ptr = _;
	s1.push(temp);

	while(!s1.empty()){
		if (temp != _){
			temp = s1.top();
			s1.pop();
			s2.push(temp);
		}
		ptr = s2.top();
		if(ptr->left != _) s1.push(ptr->left);
		if(ptr->right != _) s1.push(ptr->right);

	}

	while(!s2.empty()){
		cout << s2.top()->data << " ";
		s2.pop();
	}
}

template <class T> int BinaryTree<T> :: height(){
	queue< node<T>* > q;
	q.push(this->root);

	int h = -1;

	while(!q.empty()){
		int nodeCount = q.size();
		while(nodeCount){
			node<T>* temp = q.front();
			q.pop();

			if(temp->left != _){
				q.push(temp->left);
			}
			if(temp->right != _){
				q.push(temp->right);
			}
			--nodeCount;
		}
		++h;
	}
	return h;
}

// DRIVER CODE --------------------------------------------------------------------------------

int main(){
	BinaryTree<int> myTree;

		int choice = -1;
		int temp = 0;
		char approach = ' ';


		while (approach != 'c'){
			cout << "\n---------- MENU ----------\n"
				 << "a. Iterative\n"
				 << "b. Recursive\n"
				 << "c. Exit"
				 << "\n--------------------------" << endl;
			cout << "Enter choice = ";
			cin >> approach;

			switch(approach){
			case 'c': // Exit
				{cout << "Thank you! :)" << endl;
				break;}

			case 'a': // Iterative
	            {
	        		while (choice){
	        			cout << "\n----------Iterative Methods----------\n"
	        				 << "1. Insert node\n"
	        				 << "2. In-order Traversal\n"
							 << "3. Pre-order Traversal\n"
							 << "4. Post-order Traversal\n"
							 << "5. Height of Tree\n"
	        				 << "0. Back"
	        				 << "\n-------------------------------------" << endl;
	        			cout << "Enter choice = ";
	        			cin >> choice;

						switch(choice){
						case 0: // Back
							break;

						case 1: // Insert node
			            {
			            	cout << "Enter no. of values =";
							int x;
							cin >> x;
							cout << "Enter values = ";
							for(int i=0; i<x; i++){
								cin >> temp;
								myTree.insert(temp);
							}
							cout << "Inserted values" << endl;
							break;
			            }

						case 2: // in-order iterative
						{
							cout << "In-order traversal = ";
							myTree.inorder();
							cout << endl;
							break;
						}

						case 3: // pre-order iterative
						{
							cout << "Pre-order traversal = ";
							myTree.preorder();
							cout << endl;
							break;
						}

						case 4: // post-order iterative
						{
							cout << "Post-order traversal = ";
							myTree.postorder();
							cout << endl;
							break;
						}

						case 5: // Height of Tree
						{
							cout << "Height of tree = " << myTree.height() << endl;
							break;
						}

						default : // Forced exit
							cout << "Forced exit due to error ..." << endl;
							exit(0);
						}
			            }
	        		choice = -1;
	        		break;
				}
			case 'b': // Recursive
				{
					while (choice){
						cout << "\n---------- Recursive Methods ----------\n"
							 << "1. Create Tree\n"
							 << "2. In-order Traversal\n"
							 << "3. Pre-order Traversal\n"
							 << "4. Post-order Traversal\n"
							 << "5. Mirror Tree\n"
							 << "6. Height of Tree\n"
							 << "7. Copy Tree\n"
							 << "8. Erase all nodes\n"
							 << "9. Number of Nodes\n"
							 << "0. Exit"
							 << "\n----------------------------------------" << endl;
						cout << "Enter choice = ";
						cin >> choice;

						switch(choice){
						case 0: // Back
							break;

						case 1: // create
						{
							cout << "started creating tree" << endl;
							node<int>* t = myTree.create();
							myTree.setRoot(t);
							cout << "tree created!" << endl;
							break;
						}

						case 2: // in-order recursive
						{
							cout << "In-order traversal = ";
							myTree.inorder_rec(myTree.getRoot());
							cout << endl;
							break;
						}

						case 3: // pre-order recursive
						{
							cout << "Pre-order traversal = ";
							myTree.preorder_rec(myTree.getRoot());
							cout << endl;
							break;
						}

						case 4: // post-order recursive
						{
							cout << "Post-order traversal = ";
							myTree.postorder_rec(myTree.getRoot());
							cout << endl;
							break;
						}

						case 5: // Mirror
						{
							myTree.mirror(myTree.getRoot());
							cout << "Tree mirrored!" << endl;
							cout << "In-order traversal = ";
							myTree.inorder_rec(myTree.getRoot());
							cout << endl;
							break;
						}

						case 6: // Height of Tree
						{
							cout << "Height of tree = " << myTree.height_rec(myTree.getRoot()) << endl;
							break;
						}

						case 7: // Copy Tree
						{
							BinaryTree<int> bt;
							bt = myTree;
							cout << "Tree copied." << endl;
							cout << "In-order traversal of copied tree = ";
							bt.inorder();
							cout << endl;
							break;
						}

						case 8: // erase all nodes
						{
							myTree.eraseTree(myTree.getRoot());
							cout << "Tree erased." << endl;
							break;
						}

						case 9 : // no of nodes
						{
							int total = 0;
							int leaf = 0;
							myTree.calc_nodes(myTree.getRoot(), total, leaf);
							int internal = total - leaf;

							cout << "Total nodes = " << total << endl;
							cout << "Internal nodes = " << internal << endl;
							cout << "Leaf nodes = " << leaf << endl;

							break;
						}

						default : // Forced exit
							cout << "Forced exit due to error ..." << endl;
							exit(0);
						}
					}
					choice = -1;
					break;
				}

				default : // Forced exit
					cout << "Forced exit due to error ..." << endl;
					exit(0);
		}
	}
	return 0;
}
