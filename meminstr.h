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
    boolean IsValid() {return invalid};
  private:
    void SetCmd(string command);  // SetCmd forward declaration
    void SetMode(string mode);    // SetMode forward declaration
    void SetAddr(int address);
    CmdType cmd;        // NULL if not a command, otherwise one of the three types
    Mode m;             // NULL if not a RW input, else READ or WRITE
    int addr;           // NULL if not the address for a RW input, otherwise an int
    boolean valid;
};

MemInstr::MemInstr(){
  cmd = NULL;
  m = NULL;
  addr = NULL;
  valid = FALSE;
}

MemInstr::MemInstr(string token1, string token2){
  cmd = NULL;
  mode = SetMode(token1);
  addr = SetAddr(token2);
}

MemInstr::MemInstr(string command){
  SetCmd(command);
  valid = TRUE;
}

void MemInstr::SetCmd(string command){
  if (command == "-d"){
    cmd = d;
    valid = TRUE;
  }else if (command == "-t"){
    cmd = t;
    valid = TRUE;
  }else if (command == "-v"){
    cmd = v;
    valid = TRUE;
  }else{
    valid = FALSE;
  }
}

void MemInstr::SetMode(string mode){
}

void MemInstr::SetAddr(int address){
}
