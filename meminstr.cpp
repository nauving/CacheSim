#include "meminstr.h"

MemInstr::MemInstr() {
	cmd = n;
	mode = NONE;
	addr = NULL;
	valid = false;
}

MemInstr::MemInstr(string token1, string token2) {
	cmd = n;
	if (SetMode(token1) && SetAddr(token2)) {
		valid = true;
	}
}

MemInstr::MemInstr(string command) {
	if (SetCmd(command)) {
		valid = true;
	}
}

int MemInstr::SetCmd(string command) {
	if ((command == "-d") || (command == "-D")) {
		cmd = d;
		return 1;
	}
	else if ((command == "-t") || (command == "-T")) {
		cmd = t;
		return 1;
	}
	else if ((command == "-v") || (command == "-V")) {
		cmd = v;
		return 1;
	}
	else {
		cmd = n;
		return 0;
	}
}

int MemInstr::SetMode(string s) {
	if (s == "r" || s == "R") {
		mode = READ;
		return 1;
	}
	else if (s == "w" || s == "W") {
		mode = WRITE;
		return 1;
	}
	else {
		mode = NONE;
		return 0;
	}
}

int MemInstr::SetAddr(string address) {
	strAddr = address;
	addr = stol(address);
	return 1;
}

string MemInstr::Dump() {
	string s = "";
	if (cmd == d) { s = "Command is '-d'"; }
	if (cmd == t) { s = "Command is '-t'"; }
	if (cmd == v) { s = "Command is '-v'"; }
	if (cmd == n) {
		s = "Mode is ";
		if (mode == READ) {
			s += "READ";
		} else if (mode == WRITE) {
			s += "WRITE";
		} else if (mode == NONE) {
			s += "NONE";
		}
		s += " and address is " + strAddr;
	}
	return s;
}

long MemInstr::LAddr(){
	return addr;
}

string MemInstr::SAddr(){
	return strAddr;
}
