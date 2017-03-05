#include "parser.h"

Parser::Parser() {
	fileName = "input.txt";
	OpenFile();
}

Parser::Parser(string name) {
	fileName = name;
	OpenFile();
}

/*MemInstr Parser::NxtPkg()
{
	// this function puts together a new package and ships it off to the cache sim
}*/

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
	// this function reads the next line from the file
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
	return NextToken();
}