/*
 * 21451_OOP_assignment_4.cpp
 *
 *  Created on: 18-Oct-2022
 *      Author: Ashwin
 */
//Write a C++ program that creates an output file, writes information to it, closes the file, open
//it again as an input file and read the information from the file
// ------------------------------------------------------------------------------------------------

# include <iostream>
# include <fstream>
# include <string>
using namespace std;


class student{
	int rollno;
	string name;
public:
	student(){
		rollno = 0;
		name = "xxx";
	}

	void setData(int rollNo, string name){
		this->rollno = rollNo;
		this->name = name;
	}

	int getRoll(){
		return this->rollno;
	}

	string getName(){
		return this->name;
	}
};


// driver code
int main()
{
	ofstream fout;
	ifstream fin;
	string line;
	bool menu = true;
	int choice;
	int rollNo;
	string name;

	cout << "Welcome to Student Profile System!" << endl;

	while(menu){

		cout << "\n------------ MENU -----------"
			 << "\n1. Create New File"
			 << "\n2. Edit File"
			 << "\n3. Open and Read File"
			 << "\n-1. Exit"
			 << "\n------------------------------" << endl;
		cout << "Enter your choice : ";
		cin >> choice;
		switch(choice)
		{
		case 1 : // create new file
		{
			fout.open("myFile.txt", ios::app);
			cout << "$ myFile.txt created!" << endl;
			break;
		}
		case 2 : // edit file and close
		{
			cout << "$ Inside File Editor, press '-1' to exit" << endl;
			while(fout){
				student s;
				cin >> rollNo;
				if (rollNo == -1) break;
				cin >> name;
				s.setData(rollNo, name);
				fout << s.getRoll() << "  " << s.getName() << endl;
			}
			cout << "$ File Edited Successfully!" << endl;
			fout.close();
			cout << "$ File Closed!" << endl;
			break;
		}

		case 3: // open and read file
		{
			cout << "$ Inside File Reader" << endl;
			fin.open("myFile.txt", ios::in);
			while(fin){
				getline(fin, line);
				cout << line << endl;
			}
			break;
		}
		case -1: // exit
			menu = false;
			cout << "$ Exit from My Files . . ." << endl;
			break;
		}
	}

	return 0;
}
