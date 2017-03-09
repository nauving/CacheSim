// File: parser.h
// Parser is a class which handles the opening and parsing of a file containing memory instructions to be used by the
// Cache Simulator. The Parser object will perform error checking on the instruction before packaging it as a Memory
// Instruction object and passing it along so that the Simulator is ensured to receive valid data.
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "meminstr.h"
#include "Tokenizer.h"

using namespace std;

struct traceNode {
	MemInstr * instr;
	traceNode * nextNode;
};

class Parser {
public:
	Parser();		// Default constructor forward declaration
	Parser(string fname);	// Custom filename constructor forward declaration
	void NxtPkg(MemInstr &temp);	// NxtPkg forward declaration
	void Trace();		// Trace forward declaration
	string PrintLine();	// PrintLine forward declaration
	string PrintToken();	// PrintToken forward declaration
	bool IsEof();
private:
	string NextToken();	// NextToken forward declaration
	void NextLine();	// NextLine forward declaration
	int OpenFile();		// OpenFile forward declaration
	Tokenizer tok;			// Tokenizer used to process lines
	string fileName;		// "input.txt" by default
	string line;			// stores the current line from the file
	string token;			// stores the current token from the line
	ifstream dataFile;		// ifstream object to read from file
	traceNode * listHead;	// Pointer to the linked list of traces
	bool eofd;
};
