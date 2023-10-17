/*
 * 31485_LP1_MacroProcessor.cpp
 *      Author: student
 */
/* --------------------------------------

 PROBLEM STATEMENT

 Design suitable data structures and implement
 Pass-I and Pass-II of a two-pass macro- processor.
 The output of Pass-I (MNT, MDT, and intermediate
 code file without any macro definitions)
 should be input for Pass-II.

 -------------------------------------- */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <utility>

using namespace std;

class PNTAB {
	vector<string> table;
public:
	void addEntry(string pname) {
		table.push_back(pname);
	}

	void print() {
		cout << "\nPNTAB\n";
		cout << "Sr.No.\t" << "PName" << endl;
		cout << "-------------------------" << endl;

		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++) {
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}
};

class KPDTAB {
	vector<pair<string, string>> table;
public:
	void addEntry(string pname, string value) {
		table.push_back(make_pair(pname, value));
	}

	void print() {
		cout << "\nKPDTAB\n";
		cout << "Sr.No.\t" << "KPname\t" << "Default Value" << endl;
		cout << "-------------------------" << endl;

		vector<pair<string, string>>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++) {
			cout << i++ << "\t" << it->first << "\t" << it->second
					<< endl;
		}
		cout << endl;
	}
};

class MNT {
	string name;
	int PP;
	int KP;
	int EV;
	int MDTP;
	int KPDTP;
	int SSTP;

public:
	MNT() {
		name = "NULL";
		PP = KP = EV = MDTP = KPDTP = SSTP = 0;
	}

	void processPrototype(string prototype, PNTAB &pntab, KPDTAB &kpdtab) {
		string token;
		stringstream tokenStream(prototype);
		vector<string> tokenArray;
		while (tokenStream >> token) {
			tokenArray.push_back(token);
		}

		// prototype format: <name> [<parameter list>]
		name = tokenArray[0];

		vector<string>::iterator itr;
		for (itr = tokenArray.begin() + 1; itr != tokenArray.end(); itr++) {
			string formalParam;
			string defaultParam;

			bool flag = false;
			bool defaultValue = false;

			for (char c : *itr) {
				if (c == '&') {	//start of formal parameter
					continue;
				}
				if (c == '=') {	//start of default value
					flag = true;
					continue;
				}
				if (flag) {
					defaultValue = true;
					defaultParam += c;
				} else
					formalParam += c;
			}

			if (flag) {
				// Keyword parameter
				pntab.addEntry(formalParam);

				if (defaultValue) {
					// Default parameter
					kpdtab.addEntry(formalParam, defaultParam);
					cout << "default value : " << defaultParam << endl;
				} else {
					// default value null
					kpdtab.addEntry(formalParam, "NULL");
				}
				this->KP++;
			} else {
				// Positional parameter
				pntab.addEntry(formalParam);
				this->PP++;
			}

		}
	}

	void print() {
		cout << "\nMNT\n";
		cout << "Name" << "\t" << "#PP" << "\t" << "#KP" << "\t"
				<< "#EV" << "\t" << "MDTP" << "\t" << "KPDTP"
				<< "\t" << "SSTP" << "\t" << endl;
		cout << "--------------------------------------------------------------"
				<< endl;

		cout << name << "\t" << PP << "\t" << KP << "\t" << EV
				<< "\t" << MDTP << "\t" << KPDTP <<"\t" << SSTP
				<< "\t" << endl;

	}

};

class MacroProcessor {
	MNT mnt;
	PNTAB pntab;
	KPDTAB kpdtab;

public:
	void pass1(string inputFile, string outputFile) {
		ifstream fin;
		fin.open(inputFile);

		ofstream fout;	//intermediate code file
		fout.open(outputFile);

		while (!fin.eof()) {
			// input expression from input file
			string loc;
			getline(fin, loc, '\n');
			cout << "\n> " << loc << endl;

			if(loc == "MACRO"){
				getline(fin, loc, '\n');
				cout << "\n> " << loc << endl;

				mnt.processPrototype(loc, pntab, kpdtab);
				mnt.print();
				pntab.print();
				kpdtab.print();
			}
		}
	}
};

void testCase1(string inputFile) {
	ofstream fout;
	fout.open(inputFile);

	while (fout) {
		fout << "MACRO" << endl;
		fout << "CLRMEM &P &Q &R1=AREG" << endl;
		fout << "LCL &A" << endl;
		fout << "&A SET 0" << endl;
		fout << "MOVER &R1 ='0'" << endl;
		fout << ".MORE MOVEM &R1 &P+&A" << endl;
		fout << "&A SET &A+1" << endl;
		fout << "AIF (&A NE &Q) MORE" << endl;
		fout << "MEND" << endl;

		break;
	}

	fout.close();
}

int main() {
	MacroProcessor MP;

// Files to be generated
	string inputFile = "input.txt";
	string outputFile1 = "output.txt";

// Test Case 1 --------------

	testCase1(inputFile);
	MP.pass1(inputFile, outputFile1);

	return 0;
}

