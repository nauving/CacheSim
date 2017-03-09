#include "parser.h"

Parser::Parser() {
	fileName = "input.txt";
	OpenFile();
	eofd = false;
	listHead = 0;
}

Parser::Parser(string name) {
	fileName = name;
	OpenFile();
	eofd = false;
	listHead = 0;
}

void Parser::NxtPkg(MemInstr &temp)
{
	MemInstr * m;
	if (!eofd) {
		string str = NextToken();
		string tok1;
		if (str.length() > 2) {
			NxtPkg(temp);
			return;
		}
		else if (str.length() == 2) {
			if (str.substr(0, 1) == "-") {
				if ((str.substr(1, 1) == "d") || (str.substr(1, 1) == "D") || (str.substr(1, 1) == "v") || (str.substr(1, 1) == "V") || (str.substr(1, 1) == "t") || (str.substr(1, 1) == "T")) {
					tok1 = str;
					}
				else {
					NxtPkg(temp);
					return;
				}
			}
			m = new MemInstr(tok1);
			m->SetEnd(false);
			m->SetValid();
			m->CopyInstr(temp);
			delete m;
			return;
		}
		else if (str.length() == 1) {
			if ((str == "r") || (str == "R") || (str == "w") || (str == "W")) {
				tok1 = str;
				string tok2;
				do {
					str = NextToken();
				} while ((str.substr(0, 2) != "0x") && (str.length() < 3));
				tok2 = str;
				m = new MemInstr(tok1, tok2);
				m->CopyInstr(temp);
				traceNode * newnode = new traceNode;
				newnode->instr = m;
				newnode->nextNode = listHead;
				listHead = newnode;
				return;
			} else {
				NxtPkg(temp);
				return;
			}
		} else {
			NxtPkg(temp);
			return;
		}
	} else {
		m = new MemInstr();
		m->SetEnd(true);
		m->SetValid();
		m->CopyInstr(temp);
		delete m;
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

void Parser::Trace() {
	traceNode * tptr = listHead;
	int x = 0;
	cout << "\nInput commands were:\n";
	while (tptr) {
		cout << "\t" << tptr->instr->Dump();
		if (!(++x % 3)) {
			cout << "\n";
		}
		tptr = tptr->nextNode;
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
