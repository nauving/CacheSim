// File: meminstr.h
// MemInstr is a class that defines the Memory Instruction objects which are created by the Parser as it reads an input
// file. Each token (e.g. "-d") or token pair (e.g. "w 0xffff") is packaged into a MemInstr object and passed from the Parser to the Cache
// Simulator.

#pragma once

#include <string>

using namespace std;

enum CmdType {d, t, v};   // Simulator Commands
                          // "-d" : Dump
                          // "-t" : Trace
                          // "-v" : Version

enum Mode {READ, WRITE};

class MemInstr {
  public:
    MemInstr();                             // Default constructor forward declaration
    MemInstr(string token1, string token2); // 2 token constructor forward declaration
    MemInstr(string command);               // 1 token constructor forward declaration
    string MemInstr::RawData();             // RawData forward declaration
    boolean IsValid() {return invalid};     // IsValid returns TRUE when the data in the MemInstr package is valid
  private:
    void SetCmd(string command);  // SetCmd forward declaration
    void SetMode(string mode);    // SetMode forward declaration
    void SetAddr(int address);    // SetAddr forward declaration
    CmdType cmd;        // NULL if not a command, otherwise one of the three types
    Mode mode;             // NULL if not a RW input, else READ or WRITE
    long addr;           // NULL if not the address for a RW input, otherwise an int
    boolean valid;      // TRUE if the memory instruction has been packaged successfully with valid data,
                        // FALSE if not packaged successfully or packaged without valid data
};

MemInstr::MemInstr(){
  cmd = NULL;
  mode = NULL;
  addr = NULL;
  valid = FALSE;
}

MemInstr::MemInstr(string token1, string token2){
  cmd = NULL;
  if (SetMode(token1) && SetAddr(token2)){
    valid = TRUE;
  }
}

MemInstr::MemInstr(string command){
  if (SetCmd(command)){
    valid = TRUE;
  }
}

int MemInstr::SetCmd(string command){
  if (command == "-d"){
    cmd = d;
    return 1;
  }else if (command == "-t"){
    cmd = t;
    return 1;
  }else if (command == "-v"){
    cmd = v;
    return 1;
  }else{
    cmd = NULL;
    return 0;
  }
}

int MemInstr::SetMode(string s){
  if (s == "r" || s == "R"){
    mode = READ;
    return 1;
  }else if (s == "w" || s == "W"){
    mode = WRITE;
    return 1;
  }else{
    mode = NULL;
    return 0;
  }
}

int MemInstr::SetAddr(string address){
  addr = stol(address);
  return 1;
}
