#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

/* Problem Statement:

Implementation of a direct access file -
Insertion and deletion of a record from a direct access file
============================================================== */

// Class Declaration
class record
{
public:
    uint32_t rollno;
    char name[20];
    uint32_t marks;
};

class DirectAccessFile
{
    string filename;
    ifstream fin;
    ofstream fout;
    int size = 10;

public:
    // constructor
    DirectAccessFile()
    {
        filename = "abc.txt";
    }

    DirectAccessFile(string fname)
    {
        filename = fname;
        this->open();
        fout.seekp(0);
        for (int i = 0; i < size; ++i)
        {
            fout << -1 << "\n";
            fin.ignore(1000, '\n');
        }
        fout.close();
    }

    // setter
    void setFileName(string fname)
    {
        filename = fname;
        this->open();
        fout.seekp(0);
        for (int i = 0; i < size; ++i)
        {
            fout << -1 << "\n";
            fin.ignore(1000, '\n');
        }
        fout.close();
    }

    // getter
    string getFileName()
    {
        return this->filename;
    }

    // methods
    bool open();  // open file
    void close(); // close file

    void display();         // print all records
    void read(int roll);    // read a record having given roll number
    void write(record rec); // write a record

    int search(int roll); // search for a roll number
    void update();        // update data of a record
    bool remove();        // delete a record

    int find_slot(int key);

    ~DirectAccessFile()
    {
        this->close();
    }
};

// Utility Functions
void printRecord(record rec)
{
    cout << rec.rollno << setw(10) << rec.name << setw(10) << rec.marks << endl;
}

// Menu Driven Program
int main()
{
    DirectAccessFile student_record;
    record myrecord;
    int choice = -1;
    int temp = 0;
    string tstr = " ";

    cout << "# Student Records DB using Direct Access File\n";

    while (choice)
    {
        cout << "\n---------- MENU ----------\n"
             << "1. Create file\n"
             << "2. Write record into file\n"
             << "3. Display all records\n"
             << "4. Search/Read record\n"
             << "5. Delete a record\n"
             << "6. Update a record\n"
             << "0. Exit"
             << "\n--------------------------" << endl;
        cout << "Enter choice = ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Create File
        {
            string fname = " ";
            cout << "Enter filename = ";
            cin >> fname;
            student_record.setFileName(fname);
            break;
        }

        case 2: // Write record
        {
            int recordsNo = 0;
            cout << "Enter no. of records to write = ";
            cin >> recordsNo;

            for (int i = 0; i < recordsNo; ++i)
            {
                // Input record details
                cout << "Record " << i + 1 << endl;

                cout << "Enter Roll No (1-75) = ";
                cin >> myrecord.rollno;
                cout << "Enter Name (max 20 char) = ";
                cin >> myrecord.name;
                cout << "Enter Marks (out of 50) = ";
                cin >> myrecord.marks;

                student_record.write(myrecord);
            }
            break;
        }

        case 3: // Display all records
        {

            break;
        }

        case 4: // Search/Read record
        {
            int key = 0;
            cout << "Enter Roll No to search (1-75) = ";
            cin >> key;
            student_record.read(key);
            break;
        }

        case 5: // Delete a record
        {

            break;
        }

        case 6: // Update a record
        {

            break;
        }

        case 0: // Exit
        {
            cout << "Thank you :)" << endl;
            student_record.close();
            break;
        }

        default: // Forced exit
        {
            cout << "# Invalid choice" << endl;
            choice = -1;
            break;
        }
        }
    }

    return 0;
}

// Method Definition

bool DirectAccessFile::open()
{
    // returns status of whether file is opened successfully or not
    fin.open(filename, ios::in | ios::binary);
    fout.open(filename, ios::app | ios::binary);
    if (fin && fout)
    {
        return true;
    }
    return false;
}

void DirectAccessFile::close()
{
    if (fin && fout)
    {
        fin.close();
        fout.close();
    }
}

int DirectAccessFile::find_slot(int key)
{
    this->open();
    int idx = key % this->size;
    fin.seekg(sizeof(record) * idx, ios::beg);
    record currRecord;
    fin >> currRecord.rollno;
    for (int i = 0; i < size; ++i)
    {
        if (currRecord.rollno != -1)
        {
            idx = (idx + 1) % this->size;
            fin.seekg(sizeof(record) * idx, ios::beg);
            fin >> currRecord.rollno;
        }
        else 
        {
            this->close();
            return idx;
        }
    }
    this->close();
    return -1;
}

void DirectAccessFile::write(record rec)
{ // write a record
    this->open();
    int index = this->find_slot(rec.rollno);
    if (index != -1)
    {
        cout << "writing in file" << endl;
        fout.seekp(sizeof(record) * index, ios::beg);
        fout << rec.rollno << setw(10) << rec.name << setw(10) << rec.marks << "\n";
    }
    this->close();
}

void DirectAccessFile::read(int roll)
{ // read a record
    this->open();
    int index = this->search(roll);
    if (index != -1)
    {
        cout << "reading from file" << endl;
        record currRecord;
        fin.seekg(sizeof(record) * index, ios::beg);
        fin >> currRecord.rollno >> currRecord.name >> currRecord.marks;
        printRecord(currRecord);
        this->close();
        return;
    }
    cout << "Record not found" << endl;
    this->close();
}

int DirectAccessFile::search(int key)
{ // read a record
    this->open();
    int idx = key % this->size;
    fin.seekg(sizeof(record) * idx, ios::beg);
    record currRecord;
    fin >> currRecord.rollno;
    // while
    for (int i = 0; i < size; ++i)
    {
        if (currRecord.rollno != key)
        {
            idx = (idx + 1) % this->size;
            fin.seekg(sizeof(record) * idx, ios::beg);
            fin >> currRecord.rollno;
        }
        else
        {
            this->close();
            return idx;
        }
    }
    this->close();
    return -1;
}
