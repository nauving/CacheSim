// STILL NEED TO IMPLEMENT EOF DETECTION

#include "parser.h"

Parser::Parser() {
	fileName = "input.txt";
	OpenFile();
}

Parser::Parser(string name) {
	fileName = name;
	OpenFile();
}

MemInstr Parser::NxtPkg()
{
	// this function puts together a new package to be returned to the cache sim
	string str = NextToken();
	string tok1;
	if (str.length() > 2) {
		return NxtPkg();
	} else if (str.length() == 2) {
		if (str.substr(0, 1) == "-") {
			if ((str.substr(1, 1) == "d") || (str.substr(1, 1) == "D") || (str.substr(1, 1) == "v") || (str.substr(1, 1) == "V") || (str.substr(1, 1) == "t") || (str.substr(1, 1) == "T")) {
				tok1 = str;
			}
			else {
				return NxtPkg();
			}
		}
		cout << "*****************************\nCreating MemInstr(" << tok1 << ")\n";
		return MemInstr(tok1);
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
			} while ((str.substr(0, 2) != "0x") && (str.length() >= 3));
			tok2 = str;
			cout << "*****************************\nCreating MemInstr(" << tok1 << ", " << tok2 << ")\n";
			return MemInstr(tok1, tok2);
		}
		else {
			return NxtPkg();
		}
	}
	else {
		return NxtPkg();
	}
}

string Parser::NextToken() {
	// this function reads the next token from the line
	if ((token = tok.next()) != "") {
		return token;
	}
	else {
		NextLine();
		return NextToken();
	}
}

void Parser::NextLine() {
	// this function reads the next line from the file into the line variable
	getline(dataFile, line);
	tok.set(line);
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
