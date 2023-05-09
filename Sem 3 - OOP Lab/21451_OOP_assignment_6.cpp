/*
 * 21451_OOP_assignment_6.cpp
 *
 *  Created on: 01-Nov-2022
 *      Author: se
 */

//Write C++ program using STL for sorting and searching user defined records such
//as Item records (Item code, name, cost, quantity etc) using vector container.

// ----------------------------------------------------------------------------------------

# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
using namespace std;

class item{
	int code;
	string name;
	int cost;
	int quantity;

public:
	// default constructor
	item(){
		code = -1;
		name = "xxxx";
		cost = -1;
		quantity = -1;
	}

	// parameterized constructor
	item(int code, string name, int cost, int quantity){
		this->code = code;
		this->name = name;
		this->cost = cost;
		this->quantity = quantity;
	}

	// get record of item
	friend istream & operator >> (istream &in, item &obj);

	// display record of item
	friend ostream & operator << (ostream &out, item &obj);

	// compare items
	bool operator == (const item &obj);

	void print();
	friend bool compareItems(item, item);

};

// get record of item
istream & operator >> (istream &in, item &obj){
	in >> obj.code >> obj.name >> obj.cost >> obj.quantity;
	return in;
}

// display record of item
ostream & operator << (ostream &out, item &obj){
	out << "Item Details :\n"
		<<	"() " << "item code = #" << obj.code
		<< "\n() " << "item name = " << obj.name
		<< "\n() " << "cost = " << obj.cost << "/-"
		<< "\n() " << "quantity = " << obj.quantity << endl;

	return out;
}

// compare two items
bool item::operator ==(const item &obj){
	if (this->code == obj.code && this->name == obj.name && this->cost == obj.cost && this->quantity == obj.quantity){
		return true;
	}
	return false;
}

// function to print details of item
void printItem(item obj){
	cout << obj << endl;
	return;
}

// search in given vector for a certain item
void searchItem(vector<item> list, item obj){
	vector<item> :: iterator itr;
	itr = find(list.begin(), list.end(), obj);
	if (itr != list.end()){
		cout << "item fount at position = " << (itr - list.begin()) << endl;
	}
	else{
		cout << "item not found" << endl;
	}
	return;
}

// comparision basis for sort by code
bool compareItems(item i1, item i2){
	return(i1.code < i2.code);
}

// sort items in list a/c item code
void sortByCode(vector<item> &list){
	sort(list.begin(), list.end(), compareItems);
	return;
}

int main()
{
//	// create item record
//	item item1;
////	cout << "enter item details in format : <code, name, cost, quantity>" << endl;
////	cin >> item1;
//
//	// sample items
//	item item2(10, "book", 30, 4);
//	item item3(17, "pen", 10, 6);
//	item item4(9, "textbook", 67, 3);
//	item item5(23, "tape", 100, 1);
//
//	itemList.push_back(item1);
//	itemList.push_back(item2);
//	itemList.push_back(item3);
//	itemList.push_back(item4);
//
//	// print list of items before sort
//	cout << "Before sort:" << endl;
//	for_each(itemList.begin(), itemList.end(), printItem);
//
//	// search for an item
//	searchItem(itemList, item3);
//	searchItem(itemList, item5);
//
//	// after sort
//	sortByCode(itemList);
//
//	cout << "\nAfter sort:" << endl;
//	for_each(itemList.begin(), itemList.end(), printItem);

	// menu driven program
	// store items
	vector<item> itemList;

	cout << "---- Welcome to PICT Stationary Database! ----" << endl;
	int choice = 0;

	while(choice != -1){
		cout << "\n------------ MENU ------------" << endl;
		cout << "1. Create new item entry\n"
			 << "2. Display all items\n"
			 << "3. Search for an item\n"
			 << "4. Sort the items a/c item-code\n"
			 << "5. ---\n"
			 << "-1. Exit" << endl;
		cout << "--------------------------------" << endl;

		cout << "Enter you choice = ";
		cin >> choice;

		switch (choice){
		case 1: //Create new item entry
			{item item1;
			cout << "enter item details in format : <code, name, cost, quantity>" << endl;
			cin >> item1;
			itemList.push_back(item1);
			cout << "new entry added!\n";
			break;}

		case 2: //Display all items
			{for_each(itemList.begin(), itemList.end(), printItem);
			break;}

		case 3: //Search for an item
			{item keyItem;
			cout << "enter item to search: <code, name, cost, quantity>" << endl;
			cin >> keyItem;
			searchItem(itemList, keyItem);
			break;}

		case 4: //Sort the items a/c item-code
			{sortByCode(itemList);
			cout << "Items are Sorted!" << endl;
			break;}

		case -1: //exit
			{cout << "#-------Exit-------#" << endl;
			choice = -1;
			break;}
		}
	}
	return 0;
}


