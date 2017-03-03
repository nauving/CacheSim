// File: parser.cpp
// Parser is a class which handles the opening and parsing of a file containing data to be used by the
// Cache Simulator. The Parser object will perform error checking on the data before passing it along
// so that the Simulator is ensured to be receiving valid data.
#pragma once

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Parser {
  public:
    Parser(string fname);       // Constructor forward declaration
    string Parser::GetNext();   // GetNext forward declaration
  private:
    
    
};

Parser::Parser(string FileName){
}


