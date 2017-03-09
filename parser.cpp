#include "parser.h"

Parser::Parser() {
	fileName = "input.txt";
	OpenFile();
	eofd = false;
}

Parser::Parser(string name) {
	fileName = name;
	OpenFile();
	eofd = false;
}

void Parser::NxtPkg(MemInstr &temp)
{
	MemInstr m;
	if (!eofd) {
		string str = NextToken();
		string tok1;
		if (str.length() > 2) {
			NxtPkg(temp);
		}
		else if (str.length() == 2) {
			if (str.substr(0, 1) == "-") {
				if ((str.substr(1, 1) == "d") || (str.substr(1, 1) == "D") || (str.substr(1, 1) == "v") || (str.substr(1, 1) == "V") || (str.substr(1, 1) == "t") || (str.substr(1, 1) == "T")) {
					tok1 = str;
					}
				else {
					NxtPkg(temp);
				}
			}
			//cout << "*****************************\nCreating MemInstr(" << tok1 << ")\n";
			m = MemInstr(tok1);
			m.SetEnd(false);
			m.SetValid();
			m.CopyInstr(temp);
			return;
		}
		else if (str.length() == 1) {
			if ((str == "r") || (str == "R") || (str == "w") || (str == "W")) {
				//cout << "\nFound a read/write command!" << endl;
				tok1 = str;
				//cout << "\nCurrent token is: " << PrintToken() << endl;
				string tok2;
				do {
					//cout << "\nI'm in the do/while loop to find a valid hex value" << endl;
					str = NextToken();
				} while ((str.substr(0, 2) != "0x") && (str.length() < 3));
				tok2 = str;
				//cout << "*****************************\nCreating MemInstr(" << tok1 << ", " << tok2 << ")\n";
				m = MemInstr(tok1, tok2);
				m.CopyInstr(temp);
				traceNode newnode = new traceNode;
				MemInstr nodeInstr = new MemInstr;
				m.CopyInstr(nodeInstr);
				newnode.instr = nodeInstr;
				newnode.nextNode = listHead->nextNode;
				listHead = newnode;
				return;
			} else {
				NxtPkg(temp);
			}
		} else {
			NxtPkg(temp);
			return;
		}
	} else {
		m = MemInstr();
		m.SetEnd(true);
		m.SetValid();
		m.CopyInstr(temp);
		return;
	}
}

string Parser::NextToken() {
	// this function reads the next token from the line
	if ((token = tok.next()) != "") {
		return token;
	}
	else {
		if (!eofd) {
			NextLine();
			return NextToken();
		}
		else {
			return token;
		}
	}
}

void Parser::NextLine() {
	// this function reads the next line from the file into the line variable
	if (getline(dataFile, line)) {
		tok.set(line);
	} else {
		eofd = true;
	}
}

int Parser::OpenFile() {
	if (!dataFile) { // make sure the file is good
		return 0;
	}
	else {
		dataFile.open(fileName);
		return 1;
	}
}

string Parser::PrintLine() {
	return line;
}

string Parser::PrintToken() {
	return token;
}

bool Parser::IsEof(){
	return eofd;
}
