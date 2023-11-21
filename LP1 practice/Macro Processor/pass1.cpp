#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <map>

using namespace std;

string mntFile = "macro_name_table.txt";
string mdtFile = "macro_definition_table.txt";
string kpdtabFile = "KPD_table.txt";
string pntabFile = "PN_table.txt";
string aptabFile = "AP_table.txt";

vector<string> OpcodeList = {"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT", "START", "END", "ORIGIN", "EQU", "LTORG", "DS", "DC"};
vector<string> RegisterList = {"AREG", "BREG", "CREG"};
vector<string> ConditionalList = {"EQ", "LT", "GT", "LE", "GE", "NE"};

bool checkOpcode(string key)
{
	for (string s : OpcodeList)
	{
		if (key == s)
		{
			return true;
		}
	}
	return false;
}

bool checkRegister(string key)
{
	for (string s : RegisterList)
	{
		if (key == s)
		{
			return true;
		}
	}
	return false;
}

bool checkConditional(string key)
{
	for (string s : ConditionalList)
	{
		if (key == s)
		{
			return true;
		}
	}
	return false;
}

class MNT_Entry
{
public:
	string MacroName;
	int PP;
	int KP;
	int MDTP;
	int KPDTP;

	MNT_Entry()
	{
		MacroName = "";
		PP = KP = MDTP = KPDTP = 0;
	}
};

void writeMNTfile(vector<MNT_Entry> MNT)
{
	ofstream fout;
	fout.open(mntFile);

	fout << "Macro Name Table\n\n";
	fout << "Name\t #PP\t #KP\t MDTP\t KPDTP\n";
	fout << "-----------------------------------------------------\n";

	for (MNT_Entry entry : MNT)
	{
		fout << entry.MacroName << "\t\t"
			 << entry.PP << "\t\t"
			 << entry.KP << "\t\t"
			 << entry.MDTP << "\t\t"
			 << entry.KPDTP << endl;
	}

	fout.close();
}

void writePNTABfile(vector<string> PNTAB)
{
	ofstream fout;
	fout.open(pntabFile);

	int i = 0;

	fout << "Parameter Name Table\n";
	fout << "----------------------\n";

	for (string entry : PNTAB)
	{
		fout << i++ << "\t" << entry << endl;
	}

	fout.close();
}

void writeAPTABfile(vector<string> APTAB)
{
	ofstream fout;
	fout.open(aptabFile);

	int i = 0;

	fout << "Actual Parameter Table\n";
	fout << "------------------------\n";

	for (string entry : APTAB)
	{
		fout << i++ << "\t" << entry << endl;
	}

	fout.close();
}

void writeMDTfile(vector<string> MDT)
{
	ofstream fout;
	fout.open(mdtFile);

	fout << "Macro Definition Table\n";
	fout << "------------------------\n";

	for (string entry : MDT)
	{
		fout << entry << endl;
	}

	fout.close();
}

void writeKPDTABfile(map<string, string> KPDTAB)
{
	ofstream fout;
	fout.open(kpdtabFile);

	int i = 0;

	fout << "Keyword Parameter Default Table\n\n";
	fout << "\tParameter\t Default Value\n";
	fout << "-----------------------------------------------------\n";

	for (pair<string, string> entry : KPDTAB)
	{
		fout << i++ << "\t" << entry.first << "\t\t\t\t" << entry.second << endl;
	}

	fout.close();
}

void macro_pass_1(string inputFile)
{
	vector<string> PNTAB;
	vector<MNT_Entry> MNT;
	map<string, string> KPDTAB;
	vector<string> APTAB;
	vector<string> MDT;

	int MacroCount = 0;

	int MNTptr = -1;
	int MDTptr = 0;
	int KPDTptr = 0;
	vector<int> PNTABptrs;
	int currPNTABptr = 0;

	ifstream fin;
	fin.open(inputFile);

	string loc;
	string MDT_entry;

	while (true)
	{
		getline(fin, loc, '\n');
		cout << "=> " << loc << endl;

		if (loc == "END")
		{
			break;
		}

		else if (loc == "MACRO")
		{
			// go to next line
			getline(fin, loc, '\n');
			cout << "=> " << loc << endl;

			MNT.push_back(MNT_Entry());
			MNTptr++;

			stringstream ss(loc);
			string token;

			// process macro name
			ss >> token;
			MNT[MNTptr].MacroName = token;

			// Set MDT pointer
			MNT[MNTptr].MDTP = MDTptr;
			MDTptr++;

			// Set KPDT pointer
			MNT[MNTptr].KPDTP = KPDTptr;

			// process parameters
			PNTABptrs.push_back(currPNTABptr);
			while (ss >> token)
			{
				if (token != ",")
				{
					string Pname;
					string Pvalue;
					bool valueFlag = false;

					for (auto ch : token)
					{
						if (ch == '&')
							continue;

						else if (ch == '=')
						{
							valueFlag = true;
							continue;
						}

						else if (valueFlag)
						{
							Pvalue += ch;
						}

						else
						{
							Pname += ch;
						}
					}
					if (valueFlag)
					{
						// keyword parameter
						MNT[MNTptr].KP++;
						if (!Pvalue.empty())
						{
							// default value
							KPDTAB.insert(pair<string, string>(Pname, Pvalue));
							KPDTptr++;
						}
					}
					else
					{
						// positional parameter
						MNT[MNTptr].PP++;
					}

					PNTAB.push_back(Pname);
					currPNTABptr++;
				}
			}

			// model statements
			while (true)
			{
				MDT_entry += to_string(MDTptr - 1) + "\t";
				// go to next line
				getline(fin, loc, '\n');
				cout << "=> " << loc << endl;

				if (loc == "MEND")
				{
					MDT.push_back(to_string(MDTptr - 1) + "\tMEND");
					MacroCount++;
					break;
				}

				stringstream ss(loc);
				string token;

				ss >> token;

				if (checkOpcode(token))
				{
					// mnemonic
					MDT_entry += token + " ";
				}

				// operands
				while (ss >> token)
				{
					if (token == ",")
					{
						MDT_entry += ", ";
					}
					if (token[0] == '&')
					{
						// parameter
						token = token.substr(1, token.size());
						int idx = PNTABptrs[MacroCount];
						for (int i = idx; i < PNTAB.size(); i++)
						{
							if (PNTAB[i] == token)
							{
								MDT_entry += "(P," + to_string(idx) + ") ";
								break;
							}
							idx++;
						}
					}
				}
				MDT.push_back(MDT_entry);
				MDT_entry.erase();
				MDTptr++;
			}
		}

		else
		{
			// assembly statement
			// check for macro call to fill APTAB
			stringstream ss(loc);
			string token;
			ss >> token;

			if (!checkOpcode(token))
			{
				// not mnemonic, check macro name table
				for (MNT_Entry entry : MNT)
				{
					if (token == entry.MacroName)
					{
						while (ss >> token)
						{
							if (token != ",")
								APTAB.push_back(token);
						}
					}
				}
			}
		}
	}

	// write to files
	writeMNTfile(MNT);
	writePNTABfile(PNTAB);
	writeKPDTABfile(KPDTAB);
	writeAPTABfile(APTAB);
	writeMDTfile(MDT);

	fin.close();
}

int main()
{
	string inputFile = "input.txt";
	macro_pass_1(inputFile);

	return 0;
}