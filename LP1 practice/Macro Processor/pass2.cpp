//============================================================================
// Name        : macroprocessor_pass1.cpp
// Author      : 31458
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class MNTvalues {
	int PP;
	int KP;
	int MDTP;
	int KPDTP;

public:
	MNTvalues() {
		PP = 0;
		KP = 0;
		MDTP = 0;
		KPDTP = 0;
	}

	friend class MacroProcessor;
};

class MacroProcessor {
	unordered_map<string, MNTvalues> MNT;
	vector<pair<string, string>> KPDTAB;
	vector<vector<string>> MDT;
    vector<string> PNTAB;
    vector<pair<string, string>> APTAB;
	fstream file;
    fstream macro_name_table;
    fstream keyword_parameter_table;
    fstream macro_definition_table;
    fstream parameter_table;
    fstream actual_parameter_table;
    fstream output;
    vector<string> words;
    string line;
    MNTvalues m;

public:
	MacroProcessor() {
		file.open("macro_input.txt", ios::in);
		if (!file.is_open()) {
			cout<<"Error opening file"<<endl;
		}

        macro_name_table.open("macro_name_table.txt", ios::in);
		if (macro_name_table.is_open()) {
			while (!macro_name_table.eof()) {
				getline(macro_name_table, line);
				string w = "";
				for (int i = 0;i < int(line.size()); i++) {
					if (line[i] != ' ') {
						w += line[i];
					} else {
						words.push_back(w);
						w = "";
					}
				}
				words.push_back(w);
				MNT[words[0]].KP = stoi(words[1]);
				MNT[words[0]].PP = stoi(words[2]);
				MNT[words[0]].KPDTP = stoi(words[3]);
				MNT[words[0]].MDTP = stoi(words[4]);
				words.clear();
			}
		} else {
			cout<<"Error opening file"<<endl;
		}
		macro_name_table.close();

        keyword_parameter_table.open("keyword_parameter_table.txt", ios::in);
        if (keyword_parameter_table.is_open()) {
        	while (!keyword_parameter_table.eof()) {
        		getline(keyword_parameter_table, line);
        		string w = "";
        		for (int i = 0;i < int(line.size()); i++) {
        			if (line[i] != ' ') {
        				w += line[i];
        			} else {
        				words.push_back(w);
        				w = "";
        			}
        		}
        		words.push_back(w);
        		KPDTAB.push_back({words[0], words[1]});
        		words.clear();
        	}
        } else {
        	cout<<"Error opening file"<<endl;
        }
        keyword_parameter_table.close();

        macro_definition_table.open("macro_definition_table.txt", ios::in);
        if (macro_definition_table.is_open()) {
        	while (!macro_definition_table.eof()) {
        		getline(macro_definition_table, line);
        		string w = "";
        		for (int i = 0;i < int(line.size()); i++) {
        			if (line[i] != ' ') {
        				w += line[i];
        			} else {
        				words.push_back(w);
        				w = "";
        			}
        		}
        		words.push_back(w);
        		MDT.push_back(words);
        		words.clear();
        	}
        } else {
        	cout<<"Error opening file"<<endl;
        }
        macro_definition_table.close();

        parameter_table.open("parameter_table.txt", ios::in);
        if (parameter_table.is_open()) {
        	while (!parameter_table.eof()) {
        		getline(parameter_table, line);
        		string w = "";
        		for (int i = 0;i < int(line.size()); i++) {
        			if (line[i] != ' ') {
        				w += line[i];
        			} else {
        				words.push_back(w);
        				w = "";
        			}
        		}
        		words.push_back(w);
        		PNTAB.push_back(words[0]);
        		words.clear();
        	}
        } else {
        	cout<<"Error opening file"<<endl;
        }
        parameter_table.close();

        actual_parameter_table.open("actual_parameter_table.txt", ios::out);
        if (!actual_parameter_table.is_open()) {
        	cout<<"Error opening file"<<endl;
        }

        output.open("output.txt", ios::out);
        if (!output.is_open()) {
        	cout<<"Error opening file"<<endl;
        }
	}

	void displayAPTAB(string name, int reference) {
		for (int i = 1; i <= MNT[name].PP; i++) {
			APTAB.push_back({PNTAB[reference + i], words[i]});
			actual_parameter_table<<PNTAB[reference + i]<<" "<<words[i]<<endl;
		}
		for (int i = MNT[name].KPDTP - 1; i < MNT[name].KP + MNT[name].KPDTP - 1; i++) {
			if (KPDTAB[i].second != "") {
				APTAB.push_back({KPDTAB[i].first, KPDTAB[i].second});
				actual_parameter_table<<KPDTAB[i].first<<" "<<KPDTAB[i].second<<endl;
			} else {
				for (int j = 1; j < words.size(); j++) {
					if (words[j] == KPDTAB[i].first) {
						APTAB.push_back({KPDTAB[i].first, words[j + 2]});
						actual_parameter_table<<KPDTAB[i].first<<" "<<words[j + 2]<<endl;
						break;
					}
				}
			}
		}
	}

	void expandMacro(string name, int reference, bool insideMacro) {
		for (int i = MNT[name].MDTP - 1; i < MDT.size(); i++) {
			for (int j = 0; j < MDT[i].size() - 1; j++) {
				if (MDT[i][j] == "MEND") {
					insideMacro = false;
					break;
				} else {
					if (MDT[i][j].at(0) == '(') {
						int index = reference + int(MDT[i][j].at(3) - '0');
						output<<" "<<APTAB[index].second;
					} else if (j == 0){
						output<<MDT[i][j];
					} else {
						output<<" "<<MDT[i][j];
					}
				}
			}
			if (!insideMacro) {
				break;
			}
			output<<endl;
		}
	}

	void passTwo() {
		string name;
		bool insideMacro = false;
		bool insideStart = false;
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, line);
				string w = "";
				for (int i = 0;i < int(line.size()); i++) {
					if (line[i] != ' ') {
						w += line[i];
					} else {
						words.push_back(w);
						w = "";
					}
				}
				words.push_back(w);
				if (words[0] == "START") {
					insideStart = true;
					for (auto x: words) {
						output<<x<<" ";
					}
					output<<endl;
				} else if (words[0] == "END") {
					insideStart = false;
					output<<words[0]<<endl;
				} else if (MNT.find(words[0]) != MNT.end() && insideStart) {
					insideMacro = true;
					name = words[0];
					APTAB.push_back({name, ""});
					actual_parameter_table<<name<<endl;
                    int reference = 0;
                    for (int i = 0; i < PNTAB.size(); i++) {
                        if (PNTAB[i] == name) {
                            reference = i;
                            break;
                        }
                    }
					displayAPTAB(name, reference);
                    expandMacro(name, reference, insideMacro);
				} else if (insideStart && !insideMacro) {
					for (auto x: words) {
						output<<x<<" ";
					}
					output<<endl;
                }
				words.clear();
			}
		} else {
			cout<<"Error opening file"<<endl;
		}
		file.close();
	}
};

int main() {
	MacroProcessor m;
	m.passTwo();
	return 0;
}