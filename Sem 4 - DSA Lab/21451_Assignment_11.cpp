/*
 * 21451_Assignment_11.cpp
 *
 *  Created on: 19-May-2023
 *      Author: student
 */
/* PROBLEM STATEMENT ------------------------------------------------------------------

Department maintains a student information.
The file contains roll number, name, division and address.
Allow user to add, delete information of student.
Display information of particular employee.
If record of student does not exist an appropriate message is displayed.
If it is, then the system displays the student details.
Use sequential file to main the data.

------------------------------------------------------------------------------------ */

/*
 * 21451_Assignment_12.cpp
 *
 *  Created on: 30-May-2023
 *      Author: student
 */


#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
using namespace std;

class student
{
    int rollno;
    char div;
    //char name[20], div, address[20];
    string name, address;
public:
    student()
    {
        rollno=0;
        div=' ';
        name=" ";
        address=" ";
    }
    void input();
    void display();
    int getrollno()
    {
        return rollno;
    }

};

void student::input()
{
    cout<<"\n******************Student Details*********************";
    cout<<"\n Enter Student Roll No :";
    cin>>rollno;

    cout<<"\n Enter Student Name :";
    cin>>name;

    cout<<"\n Enter Student Division :";
    cin>>div;

    cout<<"\n Enter student address :";
    getline(cin>>ws,address);


}

void student::display()
{
    cout<<"\n"<<rollno<<setw(15)<<name<<setw(10)<<div<<setw(10)<<address;
}


class sequential_file
{
    fstream file;
    student obj;

public:
    void create(); //Creates new file
    void add();
    void search();
    void del();
    void print();
};

void sequential_file::create()
{
    char ch='y';
    file.open("student_data.txt",ios::out|ios::binary);
    while(ch=='y'||ch=='Y')
    {
        obj.input();
        file.write((char*)&obj,sizeof(obj));
        cout<<"\nWant to enter more entries?(y/n) :";
        cin>>ch;
    }
    file.close();

}

void sequential_file::add()
{
    char ch='y';
    file.open("student_data.txt",ios::app |ios::binary);
    while(ch=='y'||ch=='Y')
    {
        obj.input();
        file.write((char*)&obj,sizeof(obj));
        cout<<"\nWant to enter more entries?(y/n) :";
        cin>>ch;
    }
    file.close();

}

void sequential_file::print()
{
 file.open("student_data.txt",ios::in|ios::binary);
 if(!file)
 {
     cout<<"File Not Found! ";

 }
 else
    {
	 cout<<"\nRoll_no"<<setw(10)<<"Name"<<setw(10)<<"Division"<<setw(10)<<"Address"<<endl;
     file.read((char*)&obj,sizeof(obj));
     while(!file.eof())
     {
         obj.display();
         cout<<endl;
         file.read((char*)&obj,sizeof(obj));
     }
    }
    file.close();
}

void sequential_file::search()
{
 int n,fl=0;
 cout<<"Enter roll no . to be searched :";
 cin>>n;
 file.open("student_data.txt",ios::in|ios::binary);
 if(!file)
 {
     cout<<"File Not Found! ";
     exit(0);

 }
 else
 {
     file.read((char*)&obj,sizeof(obj));
     while(!file.eof())
     {
         if(n==obj.getrollno())
         {
             obj.display();
             fl=1;
             break;
         }
         else
            file.read((char*)&obj,sizeof(obj));


    }
     if(fl==0)
     {
         cout<<"Record Not Found!";
     }


 }
}

int main()
{
    student obj;
    int ch;
    char choice;
    sequential_file sobj;
    do{


    cout<<"\n MENU! \n";
    cout<<"1.Create\n2.Append\n3.Display\n4.Search\nEnter choice";
    cin>>ch;
    switch(ch){
    case 1:
    	sobj.create();
    	break;
    case 2:
    	sobj.add();
    	break;
    case 3:
    	sobj.print();
    	break;
    case 4:
    	sobj.search();
    	break;
    default:
    	cout<<"Invalid choice!";
    	break;

    }
    cout<<"\nDo you want to continue?(y/n): ";
    cin>>choice;
    }while(choice=='y' || choice=='Y');
    return 0;
}
