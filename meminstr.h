// File: meminstr.h
// MemInstr is a class that defines the Memory Instruction objects which are created by the Parser as it reads an input
// file. Each token (e.g. "-d") or token pair (e.g. "w 0xffff") is packaged into a MemInstr object and passed from the Parser to the Cache
// Simulator.

#pragma once

#include <string>

using namespace std;

enum CmdType { d, t, v, n };	// Simulator Commands
								// "-d" : Dump
								// "-t" : Trace
								// "-v" : Version

enum Mode { READ, WRITE, NONE };

class MemInstr {
public:
	MemInstr();                             // Default constructor forward declaration
	MemInstr(string token1, string token2); // 2 token constructor forward declaration
	MemInstr(string command);               // 1 token constructor forward declaration
	string MemInstr::Dump();		// Dump forward declaration. This function is only used for debug.
	bool IsValid() { return valid; }	// TRUE when the data in the MemInstr package is valid
	CmdType MemInstr::GetCmd();		// GetCmd forward declaration
	Mode MemInstr::GetMode();		// GetMode forward declaration
	long MemInstr::LAddr();			// Long int version of getAddress forward declaration
	string MemInstr::SAddr();		// String version of getAddress forward declaration
private:
	int SetCmd(string command);  // SetCmd forward declaration
	int SetMode(string mode);    // SetMode forward declaration
	int SetAddr(string address);    // SetAddr forward declaration
	CmdType cmd;        // n if not a command, otherwise one of the three types
	Mode mode;          // NONE if not a RW input, else READ or WRITE
	long addr;          // NULL if not the address for a RW input, otherwise an int
	string strAddr;		// Contains the string version of the address
	bool valid;			// TRUE if the memory instruction has been packaged successfully with valid data,
						// FALSE if not packaged successfully or packaged without valid data
};

struct node{
	MemInstr * data;
	node * next;
	int flag;
}
