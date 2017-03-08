// File: parser.h
// Parser is a class which handles the opening and parsing of a file containing memory instructions to be used by the
// Cache Simulator. The Parser object will perform error checking on the instruction before packaging it as a Memory
// Instruction object and passing it along so that the Simulator is ensured to receive valid data.
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "MemInstr.h"
#include "Tokenizer.h"

using namespace std;

class Parser {
public:
	Parser::Parser();		// Default constructor forward declaration
	Parser::Parser(string fname);	// Custom filename constructor forward declaration
	MemInstr * Parser::NxtPkg();	// NxtPkg forward declaration
	string Parser::PrintLine();	// PrintLine forward declaration
	string Parser::PrintToken();	// PrintToken forward declaration
	bool Parser::IsEof();
private:
	//Parser::~Parser();			// Deconstructor forward declaration
	string Parser::NextToken();	// NextToken forward declaration
	void Parser::NextLine();	// NextLine forward declaration
	int Parser::OpenFile();		// OpenFile forward declaration
	Tokenizer tok;			// Tokenizer used to process lines
	string fileName;		// "input.txt" by default
	string line;			// stores the current line from the file
	string token;			// stores the current token from the line
	ifstream dataFile;		// ifstream object to read from file
	bool eofd;
};
