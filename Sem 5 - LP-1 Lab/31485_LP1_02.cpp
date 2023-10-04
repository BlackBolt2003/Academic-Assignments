/*
 * 31485_LP1_02.cpp
 * Author: ASHWIN TARAS (31485)
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

	int getIndex(){
		return ptr;
	}

	string getSymbolAtIndex(int index){
		return table[index].first;
	}

	int getAddressAtIndex(int index){
		return table[index].second;
	}

	void print(){
		cout << "\nSYMBOL TABLE" << endl;
		cout << "\nSr.No.\tSymbol\tAddress\n";
		for(int i=0; i<size; ++i){
			cout <<	i << "\t"
					<< table[i].first << "\t"
					<< table[i].second << endl;
		}
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

	int getIndex(){
		return ptr;
	}

	string getLiteralAtIndex(int index){
		return table[index].first;
	}

	int getAddressAtIndex(int index){
		return table[index].second;
	}

	void print(){
		cout << "\nLITERAL TABLE" << endl;
		cout << "\nSr.No.\tLiteral\tAddress\n";
		for(int i=0; i<size; ++i){
			cout <<	i << "\t"
					<< table[i].first << "\t"
					<< table[i].second << endl;
		}
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
		table[0] = 0;
	}

	POOLTABLE(int n){
		size = n;
		ptr = 0;
		table = new int[size];
		table[0] = 0;
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
	}
};

class MOT {
	int size;
	map<string, pair<string, int>> table;

public:
	MOT(){
		size = 20;

		// Imperative Statements

		table["STOP"] = pair<string, int>("IS", 0);

		table["ADD"] = pair<string, int>("IS", 1);
		table["SUB"] = pair<string, int>("IS", 2);
		table["MUL"] = pair<string, int>("IS", 3);

		table["MOVER"] = pair<string, int>("IS", 4);
		table["MOVEM"] = pair<string, int>("IS", 5);

		table["COMP"] = pair<string, int>("IS", 6);
		table["BC"] = pair<string, int>("IS", 7);
		table["DIV"] = pair<string, int>("IS", 8);

		table["READ"] = pair<string, int>("IS", 9);
		table["PRINT"] = pair<string, int>("IS", 10);

		// Assembler Directives

		table["START"] = pair<string, int>("AD", 1);
		table["STOP"] = pair<string, int>("AD", 2);

		table["ORIGIN"] = pair<string, int>("AD", 3);
		table["EQU"] = pair<string, int>("AD", 4);
		table["LTORG"] = pair<string, int>("AD", 5);

		// Registers

		table["AREG"] = pair<string, int>("RG", 1);
		table["BREG"] = pair<string, int>("RG", 2);
		table["CREG"] = pair<string, int>("RG", 3);

		// Conditional Code

		table["EQ"] = pair<string, int>("CC", 1);
		table["LT"] = pair<string, int>("CC", 2);
		table["GT"] = pair<string, int>("CC", 3);

		table["LE"] = pair<string, int>("CC", 4);
		table["GE"] = pair<string, int>("CC", 5);
		table["NE"] = pair<string, int>("CC", 6);

		// Declaration Statement

		table["DS"] = pair<string, int>("DL", 1);
		table["DC"] = pair<string, int>("DL", 2);

	}

	pair<string, int> get_opcode(string mnemonic){
		return table[mnemonic];
	}

	void print(){
		map<string, pair<string, int>> :: iterator it;
		int i=0;
		cout << "\nMachine Opcode Table (MOT)\n";
		cout << "Sr.No.\tMnemonic\tOpcode\n";
		for(it = table.begin(); it != table.end(); it++){
			cout <<	i++ << "\t"
					<< it->first << "\t\t"
					<< "("
					<< it->second.first
					<< ","
					<< it->second.second
					<< ")" << endl;
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

		while(!fin.eof()){
			string token;
			fin >> token;
			cout << token << endl;

			pair<string, int> opcode = mot.get_opcode(token);
			string instrType = opcode.first;
			int instrNum = opcode.second;

			if(token == "START" || token == "ORIGIN") {
				cout << instrType << " - " << instrNum << endl;

				// write opcode to file
				IC << "("
						<< instrType
						<< ","
						<< instrNum
						<< ") ";

				// obtain starting address
				fin >> token;
				cout << "starting address = " << token << endl;
				int start_addr = stoi(token);
				LC = start_addr;

				// write opcode to file
				IC << "(C," << start_addr << ")" << endl;
			}

			else if(token == "LTORG"){
				cout << instrType << " - " << instrNum << endl;
				// process literals
				int i = pooltab.getValue();
				cout << "pooltable entry = " << i << endl;
				while(littab.getAddressAtIndex(i) == -1){
					string lit = littab.getLiteralAtIndex(i);
					cout << "littab entry = " << lit << endl;
					littab.add_address(lit, LC);
					cout << "(DL,01)(C," << lit[2] << ") ";
					IC << "(DL,01)(C," << lit[2] << ") ";
					// update LC
					LC++;
					i++;
				}
				// update POOLTABLE
				pooltab.insert(i);
			}

			else if(instrType == "IS"){
				cout << instrType << " - " << instrNum << endl;

				// write opcode to file
				IC << "("
						<< instrType
						<< ","
						<< instrNum
						<< ") ";

				// take next operand
				fin >> token;
				cout << token << endl;

				pair<string, int> opcode = mot.get_opcode(token);
				string instrType = opcode.first;
				int instrNum = opcode.second;

				if (instrType == "RG"){
					cout << "register" << endl;
					cout << "(RG," << instrNum << ")";
					IC << "(RG," << instrNum << ")";
				}

				fin >> token;
				cout << token << endl;

				opcode = mot.get_opcode(token);
				instrType = opcode.first;
				instrNum = opcode.second;

				if (token == "N"){
					// label or symbol
					cout << "symbol" << endl;
					symtab.add_symbol(token);
					symtab.add_address(token, LC);
					IC << "(S," << symtab.getIndex() << ")\n";

				}

				fin >> token;
				cout << token << endl;

				opcode = mot.get_opcode(token);
				instrType = opcode.first;
				instrNum = opcode.second;

				if (token == "='1'"){
					cout << "literal" << endl;
					littab.add_literal(token);
					littab.add_address(token, LC);
					cout << "(L," << littab.getIndex() << ") ";
					IC << "(L," << littab.getIndex() << ")\n";
				}

				LC++;
			}
			else if (instrType == "AD" || instrType == "RG" || instrType == "CC" || instrType == "DL"){

			}

			else if (token == "='1'"){
				cout << "literal" << endl;
				littab.add_literal(token);
				littab.add_address(token, LC);
				LC++;
			}

			else if(token == "END"){
				// perform LTORG processing
				// generate IC (ad, 02)
				// go to pass 2
				break;
			}

			else if (token == "N"){
				// label or symbol
				cout << "symbol" << endl;
				symtab.add_symbol(token);
				symtab.add_address(token, LC);
				IC << "(S," << symtab.getIndex() << ")\n";

			}

		}

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

	// --------------

	ofstream fout;
	fout.open("input.txt");

	while(fout){
		fout << "START 500" << endl;
		fout << "READ N" << endl;
		fout << "MOVER BREG , ='1'" << endl;
		fout << "MOVEM BREG , TERM" << endl;
		fout << "MUL BREG , TERM" << endl;
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

