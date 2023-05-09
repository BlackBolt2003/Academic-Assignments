/*
 * 21451_oop_2.cpp
 *
 *  Created on: 30-08-2022
 *      Author: ASHWIN TARAS
 * 	   Roll No: 21451
 */

/* PROBLEM STATEMENT
 * Develop a program in C++ to create a database of student’s information system containing the
following information: Name, Roll number, Class, Division, Date of Birth, Blood group, Contact
address, Telephone number, Driving license no. and other. Construct the database with
suitable member functions. Make use of constructor, default constructor, copy constructor,
destructor, static member functions, friend class, this pointer, inline code and dynamic
memory allocation operators-new and delete as well as exception handling.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


class Student{
private:
	//Data of student
	string *name, *Class, *div, *dob;
	string *bloodGrp, *contactNo, *licNo;
	int *rollNo, *marks;
		//Count of student
	static int count;

public:


	//Default Constructor
	Student();

	//Function to get roll number of Student
	int rollCall(){
		return *this->rollNo;
	}

	//Function to obtain student data from user
	void setData();

	//Function to display student data from DB
	void readData();

	//Function to delete data of student from DB
	void deleteData();

	//Function to declare pass or fail
	friend void result(int m);

	//Copy Constructor
	Student(Student &obj);
	Student(const Student &obj);

	//Destructor
	~Student();

	//Static Function to return current count of students in DB - in-line function
	inline static int objectCount(){
		return count;
	}

};


Student::Student(){					//Default constructor
	name = new string;
	rollNo = new int;
	Class = new string;
	div = new string;
	dob = new string;
	bloodGrp = new string;
	contactNo = new string;
	licNo = new string;
	marks = new int;

	Student::count++;		//update no of students in DB
	setData();
}

void Student::setData(){

	string tempS;			//Temporary storage for all string data

	cout << "Enter name = ";		//Name
	cin.ignore();
	getline(cin, tempS);
	*name = tempS;

	while(true)						//Roll number with exception handling
	{
		cout << "Enter Roll Number = ";
		if (cin >> *rollNo){		//May set error flag if roll no. not read properly by cin
			break;
		}

		else{
			cout << "Invalid Roll Number!\n";		//error flag generated
			cin.clear();								//clears error flag
			cin.ignore(1000, '\n');						//clears buffer till 1k char or new line
		}
	}

	cout << "Enter your Class = ";		//Class
	cin.ignore();
	cin >> tempS;
	*Class = tempS;

	cout << "Enter your Division = ";		//Division
	cin.ignore();
	cin >> tempS;
	*div = tempS;

	//DOB with exception handling
	while(true){
		try
		{
			cout << "Enter Date of Birth (dd/mm/yyyy) = \n";
			cin >> tempS;
			int dayInt, monthInt, yearInt;
			stringstream dayStream, monthStream, yearStream;	//convert d, m, y into int

			dayStream << tempS.substr(0,2);		//day
			dayStream >> dayInt;
			monthStream << tempS.substr(3,2);	//month
			monthStream >> monthInt;
			yearStream << tempS.substr(6,4);	//year
			yearStream >> yearInt;

			if (dayInt > 31 || dayInt < 1){
				throw "Invalid day input!";
			}

			if (monthInt > 12 || monthInt < 1){
				throw "Invalid month input!";
			}

			if (yearInt > 2022){
				throw "Invalid year input!";
			}

			*dob = tempS;
			break;
		}

		catch (const string *msg){
			cout << msg << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}

	//blood group and exception handling
	while(true)
	{
		cout << "Enter your blood group (e.g A+ / AB-) = ";
		try
		{
			cin >> *this->bloodGrp;
			string temp = *this->bloodGrp;
			if (temp == "A+" || temp == "A-" || temp == "B+" || temp == "B-" || temp == "AB+" || temp == "AB-" || temp == "O+" || temp == "O-")
			{
				break;
			}

			else{
				throw "Invalid Blood Group!";
			}
		}

		catch (const string *msg){
			cout << msg << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}

	//contact number with exception handling
	while(true)
	{
		cout << "Enter your contact number = ";
		try
		{
			cin >> tempS;
			if (tempS.size() != 10){
				throw "Phone number must be 10 digit!";
			}
			for (char i : tempS){
				if (!isdigit(i)){
					throw "Phone number must contain only digits\n";
					break;
				}
			}
			*contactNo = tempS;
			break;
		}
		catch (const char *msg){
			cout << msg << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}

	cout << "Enter Driving License No = ";	//License number
	cin.ignore();
	cin >> *licNo;

	cout << "\nEnter Marks = "; 	//Marks
	cin >> *marks;
}

Student::Student(Student &obj)			//Copy Constructor
{
	this->name = new string;
	*name = *obj.name;

	this->rollNo = new int;
	*rollNo = *obj.rollNo;

	this->Class = new string;
	*Class = *obj.Class;

	this->div = new string;
	*div = *obj.div;

	this->dob = new string;
	*dob = *obj.dob;

	this->bloodGrp = new string;
	*bloodGrp = *obj.bloodGrp;

	this->contactNo = new string;
	*contactNo = *obj.contactNo;

	this->licNo = new string;
	*licNo = *obj.licNo;

	this->marks = new int;
	*marks = *obj.marks;

	count++;
}

Student::Student(const Student &obj)			//Copy Constructor for vector.pushback
{
	this->name = new string;
	*name = *obj.name;

	this->rollNo = new int;
	*rollNo = *obj.rollNo;

	this->Class = new string;
	*Class = *obj.Class;

	this->div = new string;
	*div = *obj.div;

	this->dob = new string;
	*dob = *obj.dob;

	this->bloodGrp = new string;
	*bloodGrp = *obj.bloodGrp;

	this->contactNo = new string;
	*contactNo = *obj.contactNo;

	this->licNo = new string;
	*licNo = *obj.licNo;

	this->marks = new int;
	*marks = *obj.marks;
}

void result(int m){			//Friend function to show result of student
	if (m >= 95){
		cout << "Pass : Grade O" << endl;
	}
	else if (m >= 90){
		cout << "Pass : Grade A+" << endl;
	}
	else if (m >= 80){
		cout << "Pass : Grade A" << endl;
	}
	else if (m >= 70){
			cout << "Pass : Grade B" << endl;
		}
	else if (m >= 55){
			cout << "Pass : Grade C" << endl;
		}
	else if (m >= 40){
			cout << "Pass : Grade D" << endl;
		}
	else {
		cout << "Fail" << endl;
	}
}

void Student::readData(){
	cout << "---------------- STUDENT DATA ----------------"
		 << "\nName = " << *this->name
		 << "\nRoll No. = " << *this->rollNo
		 << "\nClass = " << *this->Class
		 << "\nDivision = " << *this->div
		 << "\nDate of Birth = " << *this->dob
		 << "\nBlood Group = " << *this->bloodGrp
		 << "\nContact No. = " << *this->contactNo
		 << "\nLicense No. = " << *this->licNo
		 << "\nMarks = " << *this->marks << endl;

	cout << "Result = ";
	result(*this->marks);

	cout << "Current No. of studentsin Database = " << objectCount() << endl;
	cout << "----------------------------------------------" << endl;
}

void Student::deleteData(){
	delete name;
	delete Class;
	delete div;
	delete dob;
	delete bloodGrp;
	delete contactNo;
	delete licNo;
	delete rollNo;
	delete marks;
	cout << "Student data deleted" << endl;
	Student::count--;
}

Student::~Student(){ 		//destructor
	delete name,
	delete Class;
	delete div;
	delete dob;
	delete bloodGrp;
	delete contactNo;
	delete licNo;
	delete rollNo;
	delete marks;
}

int Student::count;

int main(){

	vector<Student> database;	//vector containing database elements
	int idx;		//index to iterate over vector

	cout << "---- Welcome to PICT Students Database! ----" << endl;
	int choice = 0;

	while(choice != -1){
		cout << "\n---- MENU ----" << endl;
		cout << "1. Get current students count in DB\n"
			 << "2. Create new student entry in DB\n"
			 << "3. Get data of a student in DB\n"
			 << "4. Delete data of a student from DB\n"
			 << "5. Copy data of a student in DB\n"
			 << "-1. Exit" << endl;

		cout << "Enter you choice = ";

		cin >> choice;

		switch (choice)
		{
		case 1 : // Get current students count in DB
			cout << "Current student count in DB = " << Student::objectCount() << endl;
			break;

		case 2 : // Create new student entry in DB
			{cout << "New entry at index = " << Student::objectCount() + 1 << endl;
			Student newStudent;
			database.push_back(newStudent);
			break;}

		case 3 : // Get data of a student in DB
			cout << "Enter index of student to get data = ";
			cin >> idx;
			cout << endl;
			database[idx].readData();
			break;

		case 4 : // Delete data of a student from DB
			cout << "Enter index of student to delete data = ";
			cin >> idx;
			database[idx].deleteData();
			database.erase(database.begin() + idx);
			break;

		case 5: // Copy data of a student in DB
			{cout << "New entry at index = " << Student::objectCount() + 1 << endl;
			cout << "Enter index of student to copy data = ";
			int idx;
			cin >> idx;
		    Student newStudent(database[idx]);
			database.push_back(newStudent);
			break;}

		case -1 : //Exit
			cout << "\n---- Exit from Database ----" << endl;
			choice = -1;
			break;

		default :
			cout << "Enter a valid choice" << endl;
			break;
		}
	}
	return 0;
}


