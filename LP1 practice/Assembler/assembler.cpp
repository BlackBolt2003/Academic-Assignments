/*
 * 31485_LP1_02.cpp
 * Author: ASHWIN TARAS (31485)
 * 2 pass assembler
 */

/* --------------------------------------------------------
 PROBLEM STATEMENT

 Design suitable Data structures and implement Pass-I and Pass-II of a two-pass
 assembler for pseudo-machine. Implementation should consist of a few instructions
 from each category and a few assembler directives. The output of Pass-I
 (intermediate code file and symbol table) should be input for Pass-II.

------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class SYMTAB
{
	int size;
	int ptr;
	pair<string, int> *table;

public:
	SYMTAB()
	{
		size = 20;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	SYMTAB(int s)
	{
		size = s;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	void add_symbol(string sym)
	{
		table[ptr] = pair<string, int>(sym, -1);
		ptr++;
	}

	void add_symbol(string sym, int addr)
	{
		table[ptr] = pair<string, int>(sym, addr);
		ptr++;
	}

	void add_address(string sym, int addr)
	{
		for (int i = 0; i < size; ++i)
		{
			if (table[i].first == sym)
			{
				table[i].second = addr;
				break;
			}
		}
	}

	int getPtr()
	{
		return ptr;
	}

	string getSymbolAtIndex(int index)
	{
		return table[index].first;
	}

	int getAddressAtIndex(int index)
	{
		return table[index].second;
	}

	int searchIndex(string key)
	{
		for (int i = 0; i < size; i++)
		{
			if (table[i].first == key)
			{
				return i;
			}
		}
		return -1;
	}

	void print()
	{
		cout << "\nSYMBOL TABLE" << endl;
		cout << "\nSr.No.\tSymbol\tAddress\n";
		for (int i = 0; i < size; ++i)
		{
			cout << i << "\t"
				 << table[i].first << "\t"
				 << table[i].second << endl;
		}
		cout << endl;
	}

	void writeToFile(string outputFile)
	{
		ofstream fout;
		fout.open(outputFile);

		fout << "\nSYMBOL TABLE\n\n";
		fout << "Sr.No." << setw(10) << "Symbol" << setw(10) << "Address\n";
		fout << "----------------------------" << endl;

		for (int i = 0; i < size; ++i)
		{
			fout << i << setw(10)
				 << table[i].first << setw(10)
				 << table[i].second << endl;
		}
		fout << endl;
	}
};

class LITTAB
{
	int size;
	int ptr;
	pair<string, int> *table;

public:
	LITTAB()
	{
		size = 20;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	LITTAB(int s)
	{
		size = s;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	void add_literal(string lit)
	{
		table[ptr] = pair<string, int>(lit, -1);
		ptr++;
	}

	void add_address(string lit, int addr)
	{
		for (int i = 0; i < size; ++i)
		{
			if (table[i].first == lit)
			{
				table[i].second = addr;
				break;
			}
		}
	}

	int getPtr()
	{
		return ptr;
	}

	string getLiteralAtIndex(int index)
	{
		return table[index].first;
	}

	int getAddressAtIndex(int index)
	{
		return table[index].second;
	}

	int searchIndex(string key)
	{
		for (int i = 0; i < size; i++)
		{
			if (table[i].first == key)
			{
				return i;
			}
		}
		return -1;
	}

	void print()
	{
		cout << "\nLITERAL TABLE" << endl;
		cout << "\nSr.No.\tLiteral\tAddress\n";
		for (int i = 0; i < size; ++i)
		{
			cout << i << "\t"
				 << table[i].first << "\t"
				 << table[i].second << endl;
		}
		cout << endl;
	}

	void writeToFile(string outputFile)
	{
		ofstream fout;
		fout.open(outputFile);

		fout << "\nLITERAL TABLE\n\n";
		fout << "Sr.No." << setw(10) << "Literal" << setw(10) << "Address\n";
		fout << "----------------------------" << endl;

		for (int i = 0; i < size; ++i)
		{
			fout << i << setw(10)
				 << table[i].first << setw(10)
				 << table[i].second << endl;
		}
		fout << endl;
	}
};

class POOLTABLE
{
	int size;
	int *table;
	int ptr;

public:
	POOLTABLE()
	{
		size = 20;
		ptr = 0;
		table = new int[size];
		for (int i = 0; i < size; i++)
		{
			table[i] = 0;
		}
	}

	POOLTABLE(int n)
	{
		size = n;
		ptr = 0;
		table = new int[size];
		for (int i = 0; i < size; i++)
		{
			table[i] = 0;
		}
	}

	void incPointer()
	{
		ptr++;
	}

	void insert(int entry)
	{
		ptr++;
		table[ptr] = entry;
	}

	int getValue()
	{
		return table[ptr];
	}

	void print()
	{
		cout << "\nPOOLTABLE\n";
		for (int i = 0; i < size; ++i)
		{
			cout << i << "\t" << table[i] << endl;
		}
		cout << endl;
	}

	void writeToFile(string outputFile)
	{
		ofstream fout;
		fout.open(outputFile);

		fout << "\nPOOLTABLE\n\n";
		fout << "Sr.No." << setw(10) << "Entry\n";
		fout << "----------------------------" << endl;

		for (int i = 0; i < size; ++i)
		{
			fout << i << setw(10) << table[i] << endl;
		}
		fout << endl;
	}
};

class Mnemonic
{
public:
	string instr;
	string opcode;
	int num;

	Mnemonic()
	{
		instr = opcode = " ";
		num = -1;
	}

	Mnemonic(string i, string o, int n)
	{
		instr = i;
		opcode = o;
		num = n;
	}
};

class MOT
{
	vector<Mnemonic> table;

public:
	MOT()
	{
		// Imperative Statements

		table.push_back(Mnemonic("STOP", "IS", 0));

		table.push_back(Mnemonic("ADD", "IS", 1));
		table.push_back(Mnemonic("SUB", "IS", 2));
		table.push_back(Mnemonic("MULT", "IS", 3));

		table.push_back(Mnemonic("MOVER", "IS", 4));
		table.push_back(Mnemonic("MOVEM", "IS", 5));

		table.push_back(Mnemonic("COMP", "IS", 6));
		table.push_back(Mnemonic("BC", "IS", 7));
		table.push_back(Mnemonic("DIV", "IS", 8));

		table.push_back(Mnemonic("READ", "IS", 9));
		table.push_back(Mnemonic("PRINT", "IS", 10));

		// Assembler Directives

		table.push_back(Mnemonic("START", "AD", 1));
		table.push_back(Mnemonic("END", "AD", 2));

		table.push_back(Mnemonic("ORIGIN", "AD", 3));
		table.push_back(Mnemonic("EQU", "AD", 4));
		table.push_back(Mnemonic("LTORG", "AD", 5));

		// Registers

		table.push_back(Mnemonic("AREG", "RG", 1));
		table.push_back(Mnemonic("BREG", "RG", 2));
		table.push_back(Mnemonic("CREG", "RG", 3));

		// Conditional Code

		table.push_back(Mnemonic("EQ", "CC", 1));
		table.push_back(Mnemonic("LT", "CC", 2));
		table.push_back(Mnemonic("GT", "CC", 3));

		table.push_back(Mnemonic("LE", "CC", 4));
		table.push_back(Mnemonic("GE", "CC", 5));
		table.push_back(Mnemonic("NE", "CC", 6));

		// Declaration Statement

		table.push_back(Mnemonic("DS", "DL", 1));
		table.push_back(Mnemonic("DC", "DL", 2));
	}

	string get_opcode(string key)
	{
		vector<Mnemonic>::iterator it;
		for (it = table.begin(); it != table.end(); it++)
		{
			if (it->instr == key)
			{
				return it->opcode;
			}
		}
		return "NULL";
	}

	int get_opcode_num(string key)
	{
		vector<Mnemonic>::iterator it;
		for (it = table.begin(); it != table.end(); it++)
		{
			if (it->instr == key)
			{
				return it->num;
			}
		}
		return -1;
	}

	bool check_if_mnemonic(string key)
	{
		vector<Mnemonic>::iterator it;
		for (it = table.begin(); it != table.end(); it++)
		{
			if (it->instr == key)
			{
				return true;
			}
		}
		return false;
	}

	void print()
	{
		cout << "\nMachine Opcode Table (MOT)\n";
		cout << "Sr.No.\tMnemonic\tOpcode\n";

		vector<Mnemonic>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			cout << i++ << "\t"
				 << it->instr << "\t\t"
				 << "("
				 << it->opcode
				 << ","
				 << it->num
				 << ")" << endl;
		}
		cout << endl;
	}

	void writeToFile(string outputFile)
	{
		ofstream fout;
		fout.open(outputFile);

		fout << "\nMachine Opcode Table (MOT)\n\n";
		fout << "Sr.No." << setw(10) << "Mnemonic" << setw(10) << "Opcode\n";
		fout << "------------------------------------" << endl;

		vector<Mnemonic>::iterator it;
		int i = 0;

		for (it = table.begin(); it != table.end(); it++)
		{
			fout << i++ << setw(10)
				 << it->instr << setw(10)
				 << "("
				 << it->opcode
				 << ","
				 << it->num
				 << ")" << endl;
		}
		fout << endl;
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

	Expression(string loc, MOT mot)
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
		if (mot.check_if_mnemonic(exp[0]))
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
	}
};

class IntermediateCode
{
public:
	int address;
	string instrType;
	int instrNum;
	string op1Type;
	int op1Num;
	string op2Type;
	int op2Num;

	IntermediateCode()
	{
		address = instrNum = op1Num = op2Num = -1;
		instrType = op1Type = op2Type = "NULL";
	}

	IntermediateCode(string loc)
	{
		address = instrNum = op1Num = op2Num = -1;
		instrType = op1Type = op2Type = "NULL";

		stringstream tokenStream(loc);
		string token;
		vector<string> tokenArray;
		while (tokenStream >> token)
		{
			tokenArray.push_back(token);
		}

		// extract address
		string addrString;

		for (char c : tokenArray[0])
		{
			if (c == '>')
				break;
			addrString += c;
		}
		this->address = stoi(addrString);

		// extract instruction
		string instr;
		string checkLabel = tokenArray[1];
		bool labelFlag = false;
		if (checkLabel[1] == 'S')
		{
			tokenArray.erase(tokenArray.begin() + 1, tokenArray.begin() + 2); // remove label
		}

		instr = tokenArray[1];

		string instrString;
		string instrNumString;
		bool flag = false; // flag to check if instrNum is being read

		for (char c : instr)
		{
			if (c == '(')
				continue; // skip opening bracket
			if (c == ',')
			{
				flag = true;
				this->instrType = instrString;
				continue;
			}
			if (c == ')')
			{ // end of token
				this->instrNum = stoi(instrNumString);
				break;
			}
			if (!flag)
			{ // instruction type
				instrString += c;
			}
			else
			{ // instruction number
				instrNumString += c;
			}
		}

		// extract operands
		if (tokenArray.size() == 3 || tokenArray.size() == 4)
		{
			// only 1 operand or 1st operand
			string op1String;
			string op1NumString;
			flag = false; // flag to check if op1Num is being read

			for (char c : tokenArray[2])
			{
				if (c == '(')
					continue; // skip opening bracket
				if (c == ',')
				{
					flag = true;
					this->op1Type = op1String;
					continue;
				}
				if (c == ')')
				{ // end of token
					this->op1Num = stoi(op1NumString);
					break;
				}
				if (!flag)
				{ // op1 type
					op1String += c;
				}
				else
				{ // op1 number
					op1NumString += c;
				}
			}
		}
		if (tokenArray.size() == 4)
		{
			// 2nd operand
			string op2String;
			string op2NumString;
			flag = false; // flag to check if op2Num is being read

			for (char c : tokenArray[3])
			{
				if (c == '(')
					continue; // skip opening bracket
				if (c == ',')
				{
					flag = true;
					this->op2Type = op2String;
					continue;
				}
				if (c == ')')
				{ // end of token
					this->op2Num = stoi(op2NumString);
					break;
				}
				if (!flag)
				{ // op2 type
					op2String += c;
				}
				else
				{ // op2 number
					op2NumString += c;
				}
			}
		}
	}

	string print()
	{
		string tempStr;

		tempStr += to_string(this->address) + " ";
		tempStr += this->instrType + " " + to_string(this->instrNum) + " ";
		tempStr += this->op1Type + " " + to_string(this->op1Num) + " ";
		tempStr += this->op2Type + " " + to_string(this->op2Num);

		return tempStr;
	}
};

class Assembler
{
	SYMTAB symtab;
	LITTAB littab;
	MOT mot;
	POOLTABLE pooltab;

public:
	void pass1(string inputFile, string outputFile)
	{
		ifstream fin;
		fin.open(inputFile);

		ofstream IC; // intermediate code file
		IC.open(outputFile);

		int LC = 0; // location counter

		while (true)
		{
			// input expression from input file
			string loc;
			getline(fin, loc, '\n');
			cout << "\n> " << loc << endl;
			IC << LC << "> ";

			// Extract tokens
			Expression exp(loc, mot);
			cout << exp.label << "\t"
				 << exp.mnemonic << "\t"
				 << exp.op1 << "\t"
				 << exp.op2 << endl;

			string instrType = mot.get_opcode(exp.mnemonic);
			int instrNum = mot.get_opcode_num(exp.mnemonic);

			if (exp.mnemonic == "END")
			{
				// Process literals
				int index = pooltab.getValue();
				bool firstLiteral = true;

				while (index < littab.getPtr())
				{
					if (!firstLiteral)
					{
						cout << "\n> " << loc << endl;
						IC << LC << "> ";
					}
					// add address of literal in LITTAB
					string literal = littab.getLiteralAtIndex(index);
					littab.add_address(literal, LC);

					// generate IC
					IC << "(" << instrType << "," << instrNum << ") ";
					cout << "(" << instrType << "," << instrNum << ") "; //----

					IC << "(DL,2) ";
					cout << "(DL,2) "; //----

					// obtain value of literal
					IC << "(C,";
					for (int i = 2; i < literal.length() - 1; i++)
					{
						IC << literal[i];
					}
					IC << ")" << endl;

					cout << "(C,"; //----
					for (int i = 2; i < literal.length() - 1; i++)
					{
						cout << literal[i];
					}
					cout << ")" << endl;

					// go to next loc and next literal in LITTAB
					LC++;
					index++;
					firstLiteral = false;
				}

				pooltab.insert(littab.getPtr());

				// Generate IC
				IC << "(" << instrType << "," << instrNum << ") ";
				cout << "(" << instrType << "," << instrNum << ") "; //----

				break;
			}

			if (exp.label != "NULL")
			{
				// Label
				if (symtab.searchIndex(exp.label) == -1)
				{
					symtab.add_symbol(exp.label, LC);
				}

				IC << "(S," << symtab.searchIndex(exp.label) << ") ";
				cout << "(S," << symtab.searchIndex(exp.label) << ") "; //----
			}

			if (exp.mnemonic == "LTORG")
			{
				// process literals
				int index = pooltab.getValue();
				bool firstLiteral = true;

				while (index < littab.getPtr())
				{
					if (!firstLiteral)
					{
						cout << "\n> " << loc << endl;
						IC << LC << "> ";
					}
					// add address of literal in LITTAB
					string literal = littab.getLiteralAtIndex(index);
					littab.add_address(literal, LC);

					// generate IC
					IC << "(" << instrType << "," << instrNum << ") ";
					cout << "(" << instrType << "," << instrNum << ") "; //----

					IC << "(DL,2) ";
					cout << "(DL,2) "; //----

					// obtain value of literal
					IC << "(C,";
					for (int i = 2; i < literal.length() - 1; i++)
					{
						IC << literal[i];
					}
					IC << ")" << endl;

					cout << "(C,"; //----
					for (int i = 2; i < literal.length() - 1; i++)
					{
						cout << literal[i];
					}
					cout << ")" << endl;

					// go to next loc and next literal in LITTAB
					LC++;
					index++;

					firstLiteral = false;
				}
				LC--;
				pooltab.insert(littab.getPtr());
			}

			if (exp.mnemonic == "START")
			{
				// generate IC
				IC << "(" << instrType << "," << instrNum << ") ";
				cout << "(" << instrType << "," << instrNum << ") "; //----

				// set location counter
				if (exp.op1 == "NULL")
				{
					// default
					LC = 0;
					// generate IC
					IC << "(C,0) ";
					cout << "(C,0) "; //----
				}
				else
				{
					LC = stoi(exp.op1);
					// generate IC
					IC << "(C," << exp.op1 << ") ";
					cout << "(C," << exp.op1 << ") "; //----
				}
				IC << endl;
				cout << endl;
				continue;
			}

			if (exp.mnemonic == "ORIGIN")
			{
				// generate IC
				IC << "(" << instrType << "," << instrNum << ") ";
				cout << "(" << instrType << "," << instrNum << ") "; //----

				string operandStream = exp.op1;
				string token;
				vector<string> tokens;

				for (auto ch : operandStream)
				{
					if (ch != '+')
					{
						token += ch;
					}
					else
					{
						tokens.push_back(token);
						token = "";
					}
				}
				tokens.push_back(token);

				for (auto tok : tokens)
				{
					cout << "origin token : " << tok << endl;
					if (symtab.searchIndex(tok) != -1)
					{
						// Fetch address of symbol from the Symbol Table
						LC = symtab.getAddressAtIndex(symtab.searchIndex(tok));
						cout << "LC = " << LC << endl;
					}
					else
					{
						// Fetch value of constant
						LC += stoi(tok);
						cout << "LC = " << LC << endl;
					}
				}

				// generate IC
				if (tokens.size() == 1)
				{
					IC << "(S," << symtab.searchIndex(tokens[0]) << ") ";
					cout << "(S," << symtab.searchIndex(tokens[0]) << ") "; //----
				}
				else
				{
					IC << "((S," << symtab.searchIndex(tokens[0]) << ") ";
					cout << "((S," << symtab.searchIndex(tokens[0]) << ") "; //----

					IC << "+ (C," << tokens[1] << ")) ";
					cout << "+ (C," << tokens[1] << "))"; //----
				}

				IC << endl;
				cout << endl;
				continue;
			}

			if (exp.mnemonic == "EQU")
			{
				if (symtab.searchIndex(exp.label) == -1)
				{
					symtab.add_symbol(exp.label, symtab.getAddressAtIndex(symtab.searchIndex(exp.op1)));
				}
				// no IC, only reflected in SYMTAB
			}

			if (instrType == "DL")
			{
				// IC for symbol handled by Label block -

				// declarative statement
				int size = stoi(exp.op1);
				if (symtab.searchIndex(exp.label) == -1)
				{
					symtab.add_symbol(exp.label, LC);
				}
				else
				{
					symtab.add_address(exp.label, LC);
				}
				if (exp.mnemonic == "DS")
				{
					LC = LC + size - 1;
				}

				// generate IC
				IC << "(" << instrType << "," << instrNum << ") ";
				cout << "(" << instrType << "," << instrNum << ") "; //----

				// operand is a constant
				IC << "(C," << exp.op1 << ") ";
				cout << "(C," << exp.op1 << ") "; //----
			}

			if (instrType == "IS")
			{
				// imperative statement

				// generate IC
				IC << "(IS," << instrNum << ") ";
				cout << "(IS," << instrNum << ") "; //----

				// operand 1
				if (exp.op1 != "NULL")
				{
					if (mot.check_if_mnemonic(exp.op1) && mot.get_opcode(exp.op1) == "RG")
					{
						//  register
						IC << "(RG," << mot.get_opcode_num(exp.op1) << ") ";
						cout << "(RG," << mot.get_opcode_num(exp.op1) << ") "; //----
					}
					else if (mot.check_if_mnemonic(exp.op1) && mot.get_opcode(exp.op1) == "CC")
					{
						// conditional code
						IC << "(CC," << mot.get_opcode_num(exp.op1) << ") ";
						cout << "(CC," << mot.get_opcode_num(exp.op1) << ") "; //----
					}
					else
					{
						// symbol
						if (symtab.searchIndex(exp.op1) == -1)
						{
							symtab.add_symbol(exp.op1);
						}
						IC << "(S," << symtab.searchIndex(exp.op1) << ") ";
						cout << "(S," << symtab.searchIndex(exp.op1) << ") "; //----
					}
				}

				// operand 2
				if (exp.op2 != "NULL")
				{
					if (mot.check_if_mnemonic(exp.op2) && mot.get_opcode(exp.op2) == "RG")
					{
						// register
						IC << "(RG," << mot.get_opcode_num(exp.op2) << ") ";
						cout << "(RG," << mot.get_opcode_num(exp.op2) << ") "; //----
					}
					else if (exp.op2[0] == '=')
					{
						// literal
						if (littab.searchIndex(exp.op2) == -1)
						{
							littab.add_literal(exp.op2);
						}
						IC << "(L," << littab.searchIndex(exp.op2) << ") ";
						cout << "(L," << littab.searchIndex(exp.op2) << ") "; //----
					}
					else
					{
						// symbol
						if (symtab.searchIndex(exp.op2) == -1)
						{
							symtab.add_symbol(exp.op2);
						}
						IC << "(S," << symtab.searchIndex(exp.op2) << ") ";
						cout << "(S," << symtab.searchIndex(exp.op2) << ") "; //----
					}
				}
			}
			IC << endl;
			cout << endl;

			LC++;
		}

		cout << "end of pass 1\n"
			 << endl;
		symtab.print();
		littab.print();
		mot.print();
		pooltab.print();

		fin.close();
		IC.close();
	}

	void pass2(string inputFile, string outputFile)
	{
		ifstream fin;
		fin.open(inputFile);

		ofstream fout; // intermediate code file
		fout.open(outputFile);

		while (!fin.eof())
		{
			// input expression from input file
			string loc;
			getline(fin, loc, '\n');
			if (loc == "")
				continue;

			// Extract tokens
			IntermediateCode ic(loc);
			cout << ic.print() << endl;

			fout << ic.address << "> ";

			if (ic.instrType == "IS")
			{
				// imperative statement
				fout << "(" << ic.instrNum << ") ";
				if (ic.instrNum == 0)
				{
					// STOP
					fout << "(0) (0) ";
				}
				else
				{
					// for other instructions
					// operand 1
					if (ic.op1Type == "RG")
					{
						// register
						fout << "(" << ic.op1Num << ") ";
					}
					else if (ic.op1Type == "S")
					{
						// symbol
						fout << "(0) ";
						int symbolAddress = symtab.getAddressAtIndex(ic.op1Num);
						fout << "(" << symbolAddress << ") ";
					}
					else
					{
						fout << "(0) ";
					}

					// operand 2
					if (ic.op2Type == "RG")
					{
						// register
						fout << "(" << ic.op2Num << ") ";
					}
					else if (ic.op2Type == "S")
					{
						// symbol
						int symbolAddress = symtab.getAddressAtIndex(ic.op2Num);
						fout << "(" << symbolAddress << ") ";
					}
					else if (ic.op2Type == "L")
					{
						// literal
						int literalAddress = littab.getAddressAtIndex(ic.op2Num);
						fout << "(" << literalAddress << ") ";
					}
				}
			}
			else if (ic.instrType == "AD")
			{
				// assembler directive
				if (ic.instrNum == 5)
				{
					// LTORG
					fout << "(0) (0) ";
					fout << "(" << ic.op2Num << ") ";
				}
				// ignore any other AD statement
			}

			// ignore any DL statement

			// go to next line in output file
			fout << endl;
		}
	}

	void databases(string motFile, string symtabFile, string littabFile, string pooltabFile)
	{
		mot.writeToFile(motFile);
		symtab.writeToFile(symtabFile);
		littab.writeToFile(littabFile);
		pooltab.writeToFile(pooltabFile);
	}
};

void testCase1(string inputFile)
{
	ofstream fout;
	fout.open(inputFile);

	while (fout)
	{
		fout << "START 100" << endl;
		fout << "READ N" << endl;
		fout << "MOVER BREG , ='1'" << endl;
		fout << "MOVEM BREG , TERM" << endl;
		fout << "AGAIN MUL BREG , TERM" << endl;
		fout << "MOVER CREG , TERM" << endl;
		fout << "COMP CREG , N" << endl;
		fout << "BC LE , AGAIN" << endl;
		fout << "MOVEM BREG , RESULT" << endl;
		fout << "LTORG" << endl;
		fout << "PRINT RESULT" << endl;
		fout << "STOP" << endl;
		fout << "N DS 1" << endl;
		fout << "RESULT DS 20" << endl;
		fout << "TERM DS 1" << endl;
		fout << "END" << endl;
		break;
	}

	fout.close();
}

void testCase2(string inputFile)
{
	ofstream fout;
	fout.open(inputFile);

	while (fout)
	{
		fout << "START 100" << endl;
		fout << "A DS 3" << endl;
		fout << "L1 MOVER AREG , B" << endl;
		fout << "MOVEM BREG , TERM" << endl;
		fout << "ADD AREG , C" << endl;
		fout << "MOVEM AREG , D" << endl;
		fout << "D EQU A+1" << endl;
		fout << "L2 PRINT D" << endl;
		fout << "ORIGIN 600" << endl;
		fout << "C DC 5" << endl;
		fout << "ORIGIN 700" << endl;
		fout << "STOP" << endl;
		fout << "B DS 19" << endl;
		fout << "END" << endl;
		break;
	}

	fout.close();
}

int main()
{
	Assembler Asmb;

	// Files to be generated
	string inputFile1 = "input1.txt";
	string inputFile2 = "input2.txt";
	string inputFile3 = "input3.txt";

	string outputFile1 = "pass-1-output.txt";
	string outputFile2 = "pass-2-output.txt";

	string motFile = "mot.txt";
	string symtabFile = "symtab.txt";
	string littabFile = "littab.txt";
	string pooltabFile = "pooltab.txt";

	// Test Case 1 --------------

	// testCase1(inputFile);

	// Test Case 2 --------------

	// testCase2(inputFile);

	// Assembler Driver Code
	Asmb.pass1(inputFile2, outputFile1);
	Asmb.pass2(outputFile1, outputFile2);
	Asmb.databases(motFile, symtabFile, littabFile, pooltabFile);

	return 0;
}