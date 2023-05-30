/*
 * 21451_Assignment_01.cpp
 *
 *  Created on: 17-Feb-2023
 *      Author: student
 */
// Problem statement ---------------------
/*
 Beginning with an empty binary search tree. Construct the binary search tree by
 inserting the values in given order. After constructing binary search tree perform
 following operations
 1) Insert a new node
 2) Find numbers of node in longest path
 3) Minimum and maximum data value found in tree
 4) Change a tree so that the roles of the left and right pointers are swapped at every node
 5) Search an element.
*/

// code -----------------------

#include <iostream>
using namespace std;
#define _ NULL

// Node --------------------------------------

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
		left = right = _;
	}

	// parameterized constructor
	node(T data)
	{
		this->data = data;
		left = right = _;
	}

	template <class B>
	friend class BST;
};

// Binary Search Tree -------------------------

template <class T>
class BST
{
	node<T> *root;

public:
	// default constructor
	BST()
	{
		root = _;
	}

	// member functions
	node<T> *get_root()
	{
		return this->root;
	}

	void insert(T data);
	void remove(T key);

	void inorder_traversal(node<T> *curr);
	void preorder_traversal(node<T> *curr);
	void postorder_traversal(node<T> *curr);

	bool empty();

	bool search(int key, node<T> *&curr, node<T> *&parent);
	T min_value();
	T max_value();

	void mirror(node<T> *curr);

	int longest_path(node<T> *curr);
};

template <class T>
bool BST<T>::empty()
{
	if (this->root == _)
		return true;
	return false;
}

template <class T>
void BST<T>::insert(T data)
{
	node<T> *n = new node<T>(data);
	// check if BST is empty
	if (this->empty())
	{
		root = n;
		return;
	}

	// non-empty BST
	else
	{
		// *curr = for traversal
		// *parent = to keep track of parent

		node<T> *curr = root;
		node<T> *parent = _;

		search(data, curr, parent);

		if (curr != _)
		{
			cout << "Node" << data << "already exists." << endl;
			return;
		}

		else
		{
			if (parent->data > data)
			{
				parent->left = n;
			}
			else
			{
				parent->right = n;
			}
		}
	}
}

template <class T>
void BST<T>::remove(T key)
{
	// check empty tree
	if (this->empty())
	{
		cout << "BST is empty!" << endl;
		return;
	}
	else
	{
		node<T> *curr = root;
		node<T> *parent = _;

		search(key, curr, parent);

		if (curr == _)
		{
			cout << "Node not found!" << endl;
			return;
		}

		// case 1 - Both children are present
		if (curr->left != _ && curr->right != _)
		{
			// nearest successor of current node
			node<T> *cs = curr->right;
			parent = curr;

			while (cs->left != _)
			{
				parent = cs;
				cs = cs->left;
			}

			curr->data = cs->data; // change todelete data into successor's data
			curr = cs;			   // make original cs as current node (todelete)
		}

		// case 2 - Only left child present
		if (curr->left != _ && curr->right == _)
		{
			if (parent->left == curr)
			{
				parent->left = curr->left;
			}
			else
			{
				parent->right = curr->left;
			}
			delete curr;
			cout << "deleted!" << endl;
		}

		// case 3 - Only right child present
		if (curr->left == _ && curr->right != _)
		{
			if (parent->left == curr)
			{
				parent->left = curr->right;
			}
			else
			{
				parent->right = curr->right;
			}
			delete curr;
			cout << "deleted!" << endl;
		}

		// case 4 - leaf node
		if (curr->left == _ && curr->right == _)
		{
			if (parent->left == curr)
			{
				parent->left = _;
			}
			else
			{
				parent->right = _;
			}
			delete curr;
			cout << "deleted!" << endl;
		}
	}
}

template <class T>
void BST<T>::inorder_traversal(node<T> *curr)
{
	if (curr != _)
	{
		this->inorder_traversal(curr->left);
		cout << curr->data << " ";
		this->inorder_traversal(curr->right);
	}
}

template <class T>
void BST<T>::preorder_traversal(node<T> *curr)
{
	if (curr != _)
	{
		cout << curr->data << " ";
		this->preorder_traversal(curr->left);
		this->preorder_traversal(curr->right);
	}
}

template <class T>
void BST<T>::postorder_traversal(node<T> *curr)
{
	if (curr != _)
	{
		this->postorder_traversal(curr->left);
		this->postorder_traversal(curr->right);
		cout << curr->data << " ";
	}
}

template <class T>
bool BST<T>::search(int key, node<T> *&curr, node<T> *&parent)
{
	while (curr != _)
	{
		if (curr->data == key)
		{
			return true;
		}

		else
		{
			parent = curr;
			if (key < curr->data)
			{
				curr = curr->left;
			}
			else
			{
				curr = curr->right;
			}
		}
	}
	return false;
}

template <class T>
T BST<T>::min_value()
{
	// check if empty
	if (this->empty())
	{
		cout << "BST is empty";
		return 0;
	}

	// traverse till left-most leaf node
	node<T> *temp = root;
	while (temp->left != _)
	{
		temp = temp->left;
	}

	return (temp->data);
}

template <class T>
T BST<T>::max_value()
{
	// check if empty
	if (this->empty())
	{
		cout << "BST is empty";
		return 0;
	}

	// traverse till right-most leaf node
	node<T> *temp = root;
	while (temp->right != _)
	{
		temp = temp->right;
	}

	return (temp->data);
}

template <class T>
void BST<T>::mirror(node<T> *curr)
{
	if (curr != _)
	{
		// swap children
		node<T> *temp = curr->left;
		curr->left = curr->right;
		curr->right = temp;

		// recursive call
		this->mirror(curr->left);
		this->mirror(curr->right);
	}
}

template <class T>
int BST<T>::longest_path(node<T> *curr)
{
	if (curr == _)
		return 0;

	const int leftLen = longest_path(curr->left);
	const int rightLen = longest_path(curr->right);

	return (max(leftLen, rightLen) + 1);
}

// driver code ---------------------------------
int main()
{
	BST<int> myTree;

	int choice = -1;
	int temp = 0;

	while (choice)
	{
		cout << "\n---------- MENU ----------\n"
			 << "1. Insert Node\n"
			 << "2. Traversal\n"
			 << "3. Search Value\n"
			 << "4. Minimum Value\n"
			 << "5. Maximum Value\n"
			 << "6. Mirror BST\n"
			 << "7. Delete Node\n"
			 << "8. Longest path length\n"
			 << "0. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch (choice)
		{
		case 0: // Exit
			cout << "Thank you! :)" << endl;
			break;

		case 1: // Insert Node
		{
			cout << "Enter no. of values =";
			int x;
			cin >> x;
			cout << "Enter values = ";
			for (int i = 0; i < x; i++)
			{
				cin >> temp;
				myTree.insert(temp);
			}
			cout << "Inserted values" << endl;
			break;
		}

		case 2: // Traversal Sub-menu
		{
			cout << "Types of traversal :"
				 << "a. In-order\n"
				 << "b. Pre-order\n"
				 << "c. Post-order\n";

			char subChoice = 'x';
			cout << "Enter choice of traversal = ";
			cin >> subChoice;

			switch (subChoice)
			{
			case 'a': // in-order traversal
				cout << "In-order traversal = ";
				myTree.inorder_traversal(myTree.get_root());
				cout << endl;
				break;

			case 'b': // pre-order traversal
				cout << "Pre-order traversal = ";
				myTree.preorder_traversal(myTree.get_root());
				cout << endl;
				break;

			case 'c': // post-order traversal
				cout << "Post-order traversal = ";
				myTree.postorder_traversal(myTree.get_root());
				cout << endl;
				break;

			default: // back
				break;
			}
			break;
		}

		case 3: // Search a Node
		{
			cout << "Enter value to search = ";
			cin >> temp;
			node<int> *curr = myTree.get_root();
			node<int> *parent = _;
			if (myTree.search(temp, curr, parent))
			{
				cout << temp << " found !" << endl;
			}
			else
			{
				cout << temp << " not found !" << endl;
			}
			cout << endl;
			break;
		}

		case 4: // Minimum value
			cout << "Minimum value = " << myTree.min_value() << endl;
			break;

		case 5: // Maximum value
			cout << "Maximum value = " << myTree.max_value() << endl;
			break;

		case 6: // Mirror BST
			myTree.mirror(myTree.get_root());
			cout << "BST mirrored." << endl;
			break;

		case 7: // Delete a Node
			cout << "Enter value to delete = ";
			cin >> temp;
			myTree.remove(temp);
			cout << endl;
			break;

		case 8: // No. of nodes in longest path
			cout << "No. of nodes in longest path = " << myTree.longest_path(myTree.get_root()) << endl;
			break;

		default: // Forced exit
			cout << "Forced exit due to error ..." << endl;
			exit(0);
		}
	}

	return 0;
}
