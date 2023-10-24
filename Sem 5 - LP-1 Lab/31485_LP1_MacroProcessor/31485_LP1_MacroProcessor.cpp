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

class OpcodeList
{
	vector<string> table;

public:
	OpcodeList()
	{
		// Imperative Statements

		table.push_back("STOP");

		table.push_back("ADD");
		table.push_back("SUB");
		table.push_back("MUL");

		table.push_back("MOVER");
		table.push_back("MOVEM");

		table.push_back("COMP");
		table.push_back("BC");
		table.push_back("DIV");

		table.push_back("READ");
		table.push_back("PRINT");

		// Assembler Directives

		table.push_back("START");
		table.push_back("END");

		table.push_back("ORIGIN");
		table.push_back("EQU");
		table.push_back("LTORG");

		// Conditional Code

		table.push_back("EQ");
		table.push_back("LT");
		table.push_back("GT");

		table.push_back("LE");
		table.push_back("GE");
		table.push_back("NE");

		// Declaration Statement

		table.push_back("DS");
		table.push_back("DC");

		// Model Statements

		table.push_back("LCL");
		table.push_back("SET");
		table.push_back("AIF");
		table.push_back("AGO");
		table.push_back("ANOP");
	}

	bool check_if_mnemonic(string key)
	{
		vector<string>::iterator it;
		for (it = table.begin(); it != table.end(); it++)
		{
			if (*it == key)
			{
				return true;
			}
		}
		return false;
	}

	void print()
	{
		cout << "\nOpcode List\n";
		cout << "Sr.No.\tMnemonic\n";

		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}
};

class PNTAB
{
	vector<string> table;

public:
	void addEntry(string pname)
	{
		table.push_back(pname);
	}

	void print()
	{
		cout << "\nPNTAB\n";
		cout << "Sr.No.\t"
			 << "PName" << endl;
		cout << "-------------------------" << endl;

		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}

	int getIndex(string ssname)
	{
		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			if (*it == ssname)
				return i;
			i++;
		}
		return -1;
	}
};

class KPDTAB
{
	vector<pair<string, string>> table;

public:
	void addEntry(string pname, string value)
	{
		table.push_back(make_pair(pname, value));
	}

	void print()
	{
		cout << "\nKPDTAB\n";
		cout << "Sr.No.\t"
			 << "KPname\t"
			 << "Default Value" << endl;
		cout << "-------------------------" << endl;

		vector<pair<string, string>>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << it->first << "\t" << it->second << endl;
		}
		cout << endl;
	}
};

class MNT
{
public:
	string name;
	int PP;
	int KP;
	int EV;
	int MDTP;
	int KPDTP;
	int SSTP;

	MNT()
	{
		name = "NULL";
		PP = KP = EV = MDTP = KPDTP = SSTP = 0;
	}

	void processPrototype(string prototype, PNTAB &pntab, KPDTAB &kpdtab)
	{
		string token;
		stringstream tokenStream(prototype);
		vector<string> tokenArray;
		while (tokenStream >> token)
		{
			tokenArray.push_back(token);
		}

		// prototype format: <name> [<parameter list>]
		name = tokenArray[0];

		vector<string>::iterator itr;
		for (itr = tokenArray.begin() + 1; itr != tokenArray.end(); itr++)
		{
			string formalParam;
			string defaultParam;

			bool flag = false;
			bool defaultValue = false;

			for (char c : *itr)
			{
				if (c == '=')
				{ // start of default value
					flag = true;
					continue;
				}
				if (flag)
				{
					defaultValue = true;
					defaultParam += c;
				}
				else
					formalParam += c;
			}

			if (flag)
			{
				// Keyword parameter
				pntab.addEntry(formalParam);

				if (defaultValue)
				{
					// Default parameter
					kpdtab.addEntry(formalParam, defaultParam);
					cout << "default value : " << defaultParam << endl;
				}
				else
				{
					// default value null
					kpdtab.addEntry(formalParam, "NULL");
				}
				this->KP++;
			}
			else
			{
				// Positional parameter
				pntab.addEntry(formalParam);
				this->PP++;
			}
		}
	}

	void print()
	{
		cout << "\nMNT\n";
		cout << "Name"
			 << "\t"
			 << "#PP"
			 << "\t"
			 << "#KP"
			 << "\t"
			 << "#EV"
			 << "\t"
			 << "MDTP"
			 << "\t"
			 << "KPDTP"
			 << "\t"
			 << "SSTP"
			 << "\t"
			 << endl;
		cout << "--------------------------------------------------------------"
			 << endl;

		cout << name << "\t" << PP << "\t" << KP << "\t" << EV << "\t" << MDTP
			 << "\t" << KPDTP << "\t" << SSTP << "\t" << endl;
	}
};

class APTAB
{
	vector<string> table;

public:
	void addEntry(string apname)
	{
		table.push_back(apname);
	}

	void print()
	{
		cout << "\nAPTAB\n";
		cout << "Sr.No.\t"
			 << "AP Name" << endl;
		cout << "-------------------------" << endl;

		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}
};

class EVNTAB
{
	vector<string> table;

public:
	void addEntry(string evname)
	{
		table.push_back(evname);
	}

	void print()
	{
		cout << "\nEVNTAB\n";
		cout << "Sr.No.\t"
			 << "EV Name" << endl;
		cout << "-------------------------" << endl;

		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}

	int getIndex(string ssname)
	{
		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			if (*it == ssname)
				return i;
			i++;
		}
		return -1;
	}
};

class EVTAB
{
	vector<int> table;

public:
	void addEntry(int evValue)
	{
		table.push_back(evValue);
	}

	void print()
	{
		cout << "\nEVTAB\n";
		cout << "Sr.No.\t"
			 << "EV Value" << endl;
		cout << "-------------------------" << endl;

		vector<int>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}
};

class Expression
{
public:
	string label;
	string mnemonic;
	string op1;
	string op2;

	Expression()
	{
		label = mnemonic = op1 = op2 = "NULL";
	}

	Expression(string loc, OpcodeList opcodeList)
	{
		label = mnemonic = op1 = op2 = "NULL";
		string token;
		stringstream tokenstream(loc);
		vector<string> exp;

		while (tokenstream >> token)
		{
			exp.push_back(token);
		}

		// check for label
		if (opcodeList.check_if_mnemonic(exp[0]))
		{
			// not a label
			mnemonic = exp[0];
			// check for number of operands
			if (exp.size() == 2)
			{
				op1 = exp[1];
			}
			else if (exp.size() == 4)
			{
				op1 = exp[1]; // 2nd is comma(,)
				op2 = exp[3];
			}
		}
		else
		{
			label = exp[0];
			mnemonic = exp[1];
			// check for number of operands
			if (exp.size() == 3)
			{
				op1 = exp[2];
			}
			else if (exp.size() == 5)
			{
				op1 = exp[2]; // 3rd is comma(,)
				op2 = exp[4];
			}
		}

		if (mnemonic == "AIF")
		{
			op1 = exp[1] + " " + exp[2] + " " + exp[3];
			op1 = op1.substr(1, op1.length() - 2);
			op2 = exp[5];
		}
	}
};

class MDT
{
	vector<pair<int, Expression>> table;

public:
	void addEntry(int lc, Expression newEntry)
	{
		table.push_back(pair<int, Expression>(lc, newEntry));
	}

	void setLastLabel(string label)
	{
		table.back().second.label = label;
	}

	void setLastOp1(string op1)
	{
		table.back().second.op1 = op1;
	}

	void setLastOp2(string op2)
	{
		table.back().second.op2 = op2;
	}

	void print()
	{
		cout << "\nMacro Definition Table (MDT)\n";
		cout << "Sr.No.\t"
			 << "Label\t"
			 << "Opcode\t"
			 << "Op 1\t\t"
			 << "Op 2" << endl;
		cout << "------------------------------------------------------" << endl;

		vector<pair<int, Expression>>::iterator it;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << it->first << "\t" << it->second.label << "\t"
				 << it->second.mnemonic << "\t" << it->second.op1 << "\t\t"
				 << it->second.op2 << endl;
		}
		cout << endl;
	}
};

class SSNTAB
{
	vector<string> table;

public:
	void addEntry(string ssname)
	{
		table.push_back(ssname);
	}

	void print()
	{
		cout << "\nSSNTAB\n";
		cout << "Sr.No.\t"
			 << "SS Name" << endl;
		cout << "-------------------------" << endl;

		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}

	int getSize()
	{
		return table.size();
	}

	int getIndex(string ssname)
	{
		vector<string>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			if (*it == ssname)
				return i;
			i++;
		}
		return -1;
	}
};

class SSTAB
{
	vector<int> table;

public:
	void addEntry(int ssValue)
	{
		table.push_back(ssValue);
	}

	void print()
	{
		cout << "\nSSTAB\n";
		cout << "Sr.No.\t"
			 << "MDT Entry #" << endl;
		cout << "-------------------------" << endl;

		vector<int>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t" << *it << endl;
		}
		cout << endl;
	}
};

class MacroProcessor
{
	MNT mnt;
	PNTAB pntab;
	KPDTAB kpdtab;
	APTAB aptab;
	EVNTAB evntab;
	EVTAB evtab;
	SSNTAB ssntab;
	SSTAB sstab;
	MDT mdt;
	OpcodeList opcodeList;

public:
	void pass1(string inputFile, string outputFile)
	{
		ifstream fin;
		fin.open(inputFile);

		ofstream fout; // intermediate code file
		fout.open(outputFile);

		int MDTptr = 0;
		int EV = 0;

		while (!fin.eof())
		{
			// input expression from input file
			string loc;
			getline(fin, loc, '\n');
			cout << "\n> " << loc << endl;

			if (loc == "MACRO")
			{
				getline(fin, loc, '\n');
				cout << "\n> " << loc << endl;

				mnt.processPrototype(loc, pntab, kpdtab);
			}

			else if (loc == "MEND")
			{
				if (ssntab.getSize() == 0)
				{
					mnt.SSTP = 0;
				}
				else
				{
					mnt.SSTP = ssntab.getSize();
				}

				if (mnt.KP == 0)
				{
					mnt.KPDTP = 0;
				}
				break;
			}

			else
			{
				Expression exp(loc, opcodeList);
				mdt.addEntry(MDTptr, exp);

				if (exp.mnemonic == "LCL")
				{
					evntab.addEntry(exp.op1);
					mnt.EV++;
				}
				else
				{
					// model statement

					// If label is a sequencing symbol
					if (exp.label[0] == '.')
					{
						string specification;
						int idx;
						idx = ssntab.getIndex(exp.label);
						if (idx == -1)
						{
							// Sequencing Symbol (SS) is not present in SSNTAB
							ssntab.addEntry(exp.label);
							sstab.addEntry(MDTptr);
						}
						specification = "(S, " + idx + ")";
						mdt.setLastLabel(specification);
					}

					// operand - 1
					if (exp.op1 != "NULL")
					{
						string specification;
						int idx;
						idx = pntab.getIndex(exp.op1);
						if (exp.op1[0] == '&' && idx != -1)
						{
							// Parameter
							specification = "(P, " + idx + ")";
						}

						idx = evntab.getIndex(exp.op1);
						else if (exp.op1[0] == '&' && idx != -1)
						{
							// Expansion time variable (EV)
							specification = "(E, " + idx + ")";
						}

						mdt.setLastOp1(specification);
					}

					// operand - 2
					if (exp.op2 != "NULL")
					{
						string specification;
						int idx;
						idx = pntab.getIndex(exp.op2);
						if (exp.op2[0] == '&' && idx != -1)
						{
							// Parameter
							specification = "(P, " + idx + ")";
						}

						idx = evntab.getIndex(exp.op2);
						else if (exp.op2[0] == '&' && idx != -1)
						{
							// Expansion time variable (EV)
							specification = "(E, " + idx + ")";
						}
						mdt.setLastOp2(specification);
					}
				}

				mdt.print();
			}

			MDTptr++;
		}

		mnt.print();
		pntab.print();
		kpdtab.print();
		aptab.print();
		evntab.print();
		evtab.print();
		ssntab.print();
		sstab.print();
		mdt.print();
	}
};

void testCase1(string inputFile)
{
	ofstream fout;
	fout.open(inputFile);

	while (fout)
	{
		fout << "MACRO" << endl;
		fout << "CLRMEM &P &Q &R1=AREG" << endl;
		fout << "LCL &A" << endl;
		fout << "&A SET 0" << endl;
		fout << "MOVER &R1 , ='0'" << endl;
		fout << ".MORE MOVEM &R1 , &P+&A" << endl;
		fout << "&A SET &A+1" << endl;
		fout << "AIF (&A NE &Q) , .MORE" << endl;
		fout << "MEND" << endl;

		break;
	}

	fout.close();
}

int main()
{
	MacroProcessor MP;

	// Files to be generated
	string inputFile = "input.txt";
	string outputFile1 = "output.txt";

	// Test Case 1 --------------

	testCase1(inputFile);
	MP.pass1(inputFile, outputFile1);

	return 0;
}
