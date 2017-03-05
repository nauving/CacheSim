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
	Parser();				// Default constructor forward declaration
	Parser(string fname);	// Custom filename constructor forward declaration
	MemInstr NxtPkg();		// NxtPkg forward declaration
private:
	string Parser::NextToken();	// NextToken forward declaration
	string Parser::NextLine();	// NextLine forward declaration
	int Parser::OpenFile();		// OpenFile forward declaration
	string fileName;			// "input.txt" by default
	string line;				// current line
	ifstream dataFile;			// ifstream object to read from file
};
