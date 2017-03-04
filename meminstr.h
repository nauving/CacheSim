// File: meminstr.cpp
// MemInstr is a class that defines the Memory Instruction objects which are created by the Parser as it reads an input
// file. Each token (e.g. "-d") or token pair (e.g. "w 0xffff") is packaged into a MemInstr object and passed from the Parser to the Cache
// Simulator.

#pragma once

#include <string>

using namespace std;

enum InstrType {cmd, rw, BLAH};

class MemInstr {
  public:
    MemInstr(); // Default constructor forward declaration
    MemInstr(string token1, string token2); // 2 token constructor forward declaration
    MemInstr(string command);  // 1 token constructor forward declaration
    string MemInstr::RawData(); // RawData forward declaration
    int MemInstr::IntData();  // IntData forward declaration
    
  private:
    
};

MemInstr::MemInstr(){
}

MemInstr::MemInstr(CmdType cmd){
}

MemInstr::MemInstr(string token1, string token2){
}
