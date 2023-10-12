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
 (intermediate code file and symbol table) should be input for Pass-I.

------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class SYMTAB {
	int size;
	int ptr;
	pair<string, int>* table;

public:
	SYMTAB(){
		size = 20;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	SYMTAB(int s){
		size = s;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	void add_symbol(string sym){
		table[ptr] = pair<string,int> (sym, -1);
		ptr++;
	}

	void add_symbol(string sym, int addr){
		table[ptr] = pair<string,int> (sym, addr);
		ptr++;
	}

	void add_address(string sym, int addr){
		for(int i=0; i<size; ++i){
			if(table[i].first == sym) {
				table[i].second = addr;
				break;
			}
		}
	}

	int getPtr(){
		return ptr;
	}

	string getSymbolAtIndex(int index){
		return table[index].first;
	}

	int getAddressAtIndex(int index){
		return table[index].second;
	}

	int searchIndex(string key){
		for(int i=0; i<size; i++){
			if(table[i].first == key){
				return i;
			}
		}
		return -1;
	}

	void print(){
		cout << "\nSYMBOL TABLE" << endl;
		cout << "\nSr.No.\tSymbol\tAddress\n";
		for(int i=0; i<size; ++i){
			cout <<	i << "\t"
					<< table[i].first << "\t"
					<< table[i].second << endl;
		}
		cout << endl;
	}
};

class LITTAB {
	int size;
	int ptr;
	pair<string, int>* table;

public:
	LITTAB(){
		size = 20;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	LITTAB(int s){
		size = s;
		ptr = 0;
		table = new pair<string, int>[size];
	}

	void add_literal(string lit){
		table[ptr] = pair<string,int> (lit, -1);
		ptr++;
	}

	void add_address(string lit, int addr){
		for(int i=0; i<size; ++i){
			if(table[i].first == lit) {
				table[i].second = addr;
				break;
			}
		}
	}

	int getPtr(){
		return ptr;
	}

	string getLiteralAtIndex(int index){
		return table[index].first;
	}

	int getAddressAtIndex(int index){
		return table[index].second;
	}

	int searchIndex(string key){
		for(int i=0; i<size; i++){
			if(table[i].first == key){
				return i;
			}
		}
		return -1;
	}

	void print(){
		cout << "\nLITERAL TABLE" << endl;
		cout << "\nSr.No.\tLiteral\tAddress\n";
		for(int i=0; i<size; ++i){
			cout <<	i << "\t"
					<< table[i].first << "\t"
					<< table[i].second << endl;
		}
		cout << endl;
	}
};

class POOLTABLE {
	int size;
	int* table;
	int ptr;

public:
	POOLTABLE(){
		size = 20;
		ptr = 0;
		table = new int[size];
		for(int i=0; i<size; i++){
			table[i] = 0;
		}
	}

	POOLTABLE(int n){
		size = n;
		ptr = 0;
		table = new int[size];
		for(int i=0; i<size; i++){
			table[i] = 0;
		}
	}

	void incPointer(){
		ptr++;
	}

	void insert(int entry){
		ptr++;
		table[ptr] = entry;
	}

	int getValue(){
		return table[ptr];
	}

	void print(){
		cout << "\nPOOLTABLE\n";
		for(int i=0; i<size; ++i){
			cout <<	i << "\t" << table[i] << endl;
		}
		cout << endl;
	}
};

class Mnemonic {
public:
	string instr;
	string opcode;
	int num;

	Mnemonic(){
		instr = opcode = " ";
		num = -1;
	}

	Mnemonic(string i, string o, int n){
		instr = i;
		opcode = o;
		num = n;
	}
};

class MOT {
	vector<Mnemonic> table;

public:
	MOT(){
		// Imperative Statements

		table.push_back(Mnemonic("STOP", "IS", 0));

		table.push_back(Mnemonic("ADD", "IS", 1));
		table.push_back(Mnemonic("SUB", "IS", 2));
		table.push_back(Mnemonic("MUL", "IS", 3));

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

	string get_opcode(string key){
		vector<Mnemonic> :: iterator it;
		for(it = table.begin(); it != table.end(); it++){
			if(it->instr == key){
				return it->opcode;
			}
		}
		return "NULL";
	}

	int get_opcode_num(string key){
		vector<Mnemonic> :: iterator it;
		for(it = table.begin(); it != table.end(); it++){
			if(it->instr == key){
				return it->num;
			}
		}
		return -1;
	}

	bool check_if_mnemonic(string key){
		vector<Mnemonic> :: iterator it;
		for(it = table.begin(); it != table.end(); it++){
			if(it->instr == key){
				return true;
			}
		}
		return false;
	}

	void print(){
		cout << "\nMachine Opcode Table (MOT)\n";
		cout << "Sr.No.\tMnemonic\tOpcode\n";

		vector<Mnemonic> :: iterator it;
		int i=0;

		for(it = table.begin(); it != table.end(); it++){
			cout <<	i++ << "\t"
					<< it->instr << "\t\t"
					<< "("
					<< it->opcode
					<< ","
					<< it->num
					<< ")" << endl;
		}
		cout << endl;
	}
};

class Expression {
public:
	string label;
	string mnemonic;
	string op1;
	string op2;

	Expression(){
		label = mnemonic = op1 = op2 = "NULL";
	}

	Expression(string loc, MOT mot){
		label = mnemonic = op1 = op2 = "NULL";
		string token;
		stringstream tokenstream(loc);
		vector<string> exp;

		while(tokenstream >> token){
			exp.push_back(token);
		}

		// check for label
		if(mot.check_if_mnemonic(exp[0])){
			// not a label
			mnemonic = exp[0];
			// check for number of operands
			if(exp.size() == 2){
				op1 = exp[1];
			}
			else if(exp.size() == 4){
				op1 = exp[1];	// 2nd is comma(,)
				op2 = exp[3];
			}
		}
		else{
			label = exp[0];
			mnemonic = exp[1];
			// check for number of operands
			if(exp.size() == 3){
				op1 = exp[2];
			}
			else if(exp.size() == 5){
				op1 = exp[2];	// 3rd is comma(,)
				op2 = exp[4];
			}
		}
	}
};

class Assembler {
public:
	void pass1(string inputFile, string outputFile){
		ifstream fin;
		fin.open(inputFile);

		ofstream IC;	//intermediate code file
		IC.open(outputFile);

		SYMTAB symtab;
		LITTAB littab;
		MOT mot;
		POOLTABLE pooltab;
		int LC=0;

		//
		symtab.print();
		littab.print();
		mot.print();
		pooltab.print();
		//

		while(true){
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

			if(exp.mnemonic == "END"){
				//Process literals
				int index = pooltab.getValue();

				while(index < littab.getPtr()){
					//add address of literal in LITTAB
					string literal = littab.getLiteralAtIndex(index);
					littab.add_address(literal, LC);

					//generate IC
					IC << "(" << instrType << "," << instrNum << ") ";
					cout << "(" << instrType << "," << instrNum << ") ";		//----

					IC << "(DL,2) ";
					cout << "(DL,2) ";		//----

					//obtain value of literal
					IC << "(C,"; 
					for(int i=2; i<literal.length()-1; i++){
						IC << literal[i];
					}

					cout << "(C,";		//----
					for(int i=2; i<literal.length()-1; i++){
						cout << literal[i];
					}
					
					//go to next loc and next literal in LITTAB
					LC++;
					index++;
				}

				pooltab.insert(littab.getPtr());

				//Generate IC
				IC << "(" << instrType << "," << instrNum << ") ";
				cout << "(" << instrType << "," << instrNum << ") ";		//----

				break;
			}

			if(exp.label != "NULL"){
				// Label
				if(symtab.searchIndex(exp.label) == -1){
					symtab.add_symbol(exp.label, LC);
				}

				IC << "(S," << symtab.searchIndex(exp.label) << ") ";
				cout << "(S," << symtab.searchIndex(exp.label) << ") ";		//----
			}

			if(exp.mnemonic == "LTORG"){
				// process literals
				int index = pooltab.getValue();

				while(index < littab.getPtr()){
					//add address of literal in LITTAB
					string literal = littab.getLiteralAtIndex(index);
					littab.add_address(literal, LC);

					//generate IC
					IC << "(" << instrType << "," << instrNum << ") ";
					cout << "(" << instrType << "," << instrNum << ") ";		//----

					IC << "(DL,2) ";
					cout << "(DL,2) ";		//----

					//obtain value of literal
					IC << "(C,"; 
					for(int i=2; i<literal.length()-1; i++){
						IC << literal[i];
					}
					IC << ")";

					cout << "(C,";		//----
					for(int i=2; i<literal.length()-1; i++){
						cout << literal[i];
					}
					cout << ")";
					
					//go to next loc and next literal in LITTAB
					LC++;
					index++;
				}
				LC--;
				pooltab.insert(littab.getPtr());
			}

			if (exp.mnemonic == "START" || exp.mnemonic == "ORIGIN"){
				//generate IC
				IC << "(" << instrType << "," << instrNum << ") ";
				cout << "(" << instrType << "," << instrNum << ") ";		//----

				// set location counter
				if(exp.op1 == "NULL"){
					// default
					LC = 0;
					//generate IC
					IC << "(C,0) ";
					cout << "(C,0) ";		//----
				}
				else{
					LC = stoi(exp.op1);
					//generate IC
					IC << "(C," << exp.op1 << ") ";
					cout << "(C," << exp.op1 << ") ";		//----
				}
				IC << endl;
				cout << endl;
				continue;
			}

			if (exp.mnemonic == "EQU"){
				if(symtab.searchIndex(exp.label) == -1){
					symtab.add_symbol(exp.label, stoi(exp.op1));
				}
				// no IC, only reflected in SYMTAB
			}

			if(instrType == "DL"){
				// IC for symbol handled by Label block -

				// declarative statement
				if(exp.mnemonic == "DS"){
					int size = stoi(exp.op1);
					if(symtab.searchIndex(exp.label) == -1){
						symtab.add_symbol(exp.label, LC);
					}
					else{
						symtab.add_address(exp.label, LC);
					}
					LC = LC + size - 1;
				}
				else{
					LC = LC + 1;
				}

				//generate IC
				IC << "(" << instrType << "," << instrNum << ") ";
				cout << "(" << instrType << "," << instrNum << ") ";	//----

				//operand is a constant
				IC << "(C," << exp.op1 << ") ";
				cout << "(C," << exp.op1 << ") ";	//----
			}

			if(instrType == "IS"){
				// imperative statement

				// generate IC
				IC << "(IS," << instrNum << ") ";
				cout << "(IS," << instrNum << ") ";		//----

				// operand 1
				if(exp.op1 != "NULL"){
					if(mot.check_if_mnemonic(exp.op1) && mot.get_opcode(exp.op1) == "RG"){
						//  register
						IC << "(RG," << mot.get_opcode_num(exp.op1) << ") ";
						cout << "(RG," << mot.get_opcode_num(exp.op1) << ") ";		//----
					}
					else if(mot.check_if_mnemonic(exp.op1) && mot.get_opcode(exp.op1) == "CC"){
						// conditional code
						IC << "(CC," << mot.get_opcode_num(exp.op1) << ") ";
						cout << "(CC," << mot.get_opcode_num(exp.op1) << ") ";		//----
					}
					else{
						// symbol
						if(symtab.searchIndex(exp.op1) == -1){
							symtab.add_symbol(exp.op1);
						}
						IC << "(S," << symtab.searchIndex(exp.op1) << ") ";
						cout << "(S," << symtab.searchIndex(exp.op1) << ") ";		//----
					}
				}

				// operand 2
				if(exp.op2 != "NULL"){
					if(mot.check_if_mnemonic(exp.op2) && mot.get_opcode(exp.op2) == "RG"){
						// register
						IC << "(RG," << mot.get_opcode_num(exp.op2) << ") ";
						cout << "(RG," << mot.get_opcode_num(exp.op2) << ") ";		//----
					}
					else if(exp.op2[0] == '='){
						// literal
						if(littab.searchIndex(exp.op2) == -1){
							littab.add_literal(exp.op2);
						}
						IC << "(L," << littab.searchIndex(exp.op2) << ") ";
						cout << "(L," << littab.searchIndex(exp.op2) << ") ";		//----
					}
					else{
						// symbol
						if(symtab.searchIndex(exp.op2) == -1){
							symtab.add_symbol(exp.op2);
						}
						IC << "(S," << symtab.searchIndex(exp.op2) << ") ";
						cout << "(S," << symtab.searchIndex(exp.op2) << ") ";		//----
					}
				}
			}
			IC << endl;
			cout << endl;

			LC++;
		}

		cout << "end of pass 1\n" << endl;
		symtab.print();
		littab.print();
		mot.print();
		pooltab.print();

		fin.close();
		IC.close();
	}
};


int main(){
	Assembler Asmb;

	// Test Case 1 --------------

	ofstream fout;
	fout.open("input.txt");

	while(fout){
		fout << "START 500" << endl;
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

	// --------------

	string input = "input.txt";
	string output = "output.txt";

	Asmb.pass1(input, output);

	return 0;
}