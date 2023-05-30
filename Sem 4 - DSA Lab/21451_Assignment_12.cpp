/*
 * 21451_Assignment_12.cpp
 *
 *  Created on: 19-May-2023
 *      Author: student
 */
/* PROBLEM STATEMENT ------------------------------------------------------------------

Implementation of a direct access file -
Insertion and deletion of a record from adirect access file

------------------------------------------------------------------------------------ */

#include <iostream>
#include <fstream>
using namespace std;

class hash1
{
    int add;

public:
    friend class DirectFile;
};

class DirectFile
{
private:
    int emp_id;
    char emp_name[10];
    char emp_exp[10];
    int salary;
    hash1 HT[10];

public:
    DirectFile()
    {
        for (int i = 0; i < 10; i++)
            HT[i].add = -1;
        emp_id = 0;
        //		emp_name=;
        //		emp_exp=''
        //		salary=0;
    }
    void addRec()
    {
        int num;
        cout << "Enter no. of records to enter :";
        cin >> num;
        ofstream fout("Records.txt", ios::out);
        for (int i = 0; i < num; i++)
        {
            cout << "Enter <ID name experience salary> :";
            cin >> emp_id >> emp_name >> emp_exp >> salary;

            int Loc = fout.tellp();

            int index = emp_id % 10;
            HT[index].add = Loc;
            fout << emp_id << " " << emp_name << " " << emp_exp << " " << salary << endl;
            cout << "(" << Loc << "," << index << ") ";
        }
        fout.close();
    }
    void displayRec()
    {
        char buffer[40];
        fstream fobj("Records.txt", ios::in);
        fobj.seekg(0, ios::beg);
        while (!fobj.eof())
        {
            fobj.getline(buffer, 40);
            cout << buffer << endl;
        }
        fobj.close();
        cout << "----------------" << endl;
        for (int i = 0; i < 10; i++)
            cout << HT[i].add << endl;
    }
    void search()
    {
        int ID;

        cout << "Enter Id to be searched :";
        cin >> ID;
        int index = ID % 10;
        int LOC = HT[index].add;
        ifstream fin;
        fin.open("Records.txt", ios::in);
        char buffer[40];
        fin.getline(buffer, 40);
        fin.getline(buffer, 40);
        //		cout<<"("<<LOC<<","<<index<<") ";

        cout << buffer;
    }
};

int main()
{

    DirectFile obj;
    obj.addRec();
    obj.displayRec();
    obj.search();
    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    return 0;
}