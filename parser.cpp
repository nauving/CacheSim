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
	// this 
}

string Parser::NextToken() {
	// this function reads the next token from the line
}

string Parser::NextLine() {
	// this function reads the next line from the file
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
