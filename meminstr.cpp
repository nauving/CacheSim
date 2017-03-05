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
	if (command == "-d") {
		cmd = d;
		return 1;
	}
	else if (command == "-t") {
		cmd = t;
		return 1;
	}
	else if (command == "-v") {
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
	addr = stol(address);
	return 1;
}
