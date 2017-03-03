// File: parser.cpp
// Parser is a class which handles the opening and parsing of a file containing memory instructions to be used by the
// Cache Simulator. The Parser object will perform error checking on the instruction before packaging it as a Memory
// Instruction object and passing it along so that the Simulator is ensured to receive valid data.
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "MemInstr.h"

using namespace std;

class Parser {
  public:
    Parser(string fname);       // Default constructor forward declaration
    string Parser::GetNext();   // GetNext forward declaration
  private:
    string fileName;
    ifstream dataFile;
    boolean isOpen = FALSE;
    Parser::open();
};

Parser::Parser(){    // Default constructor
  fileName = "input.txt";
  dataFile(fileName);
}

Parser::Parser(string name){
  fileName = name;
  dataFile(fileName);
}

MemoryCommand Parser::GetNext(){
  if (!isOpen){
    openFile();
  }
  // start reading in lines from file and tokenize
    
}

int Parser::openFile(){
  if (!dataFile){ // make sure the file is good
    return 0;
  } else {
    dataFile.open(fileName);
    isOpen = TRUE;
    return 1;
  }
}
