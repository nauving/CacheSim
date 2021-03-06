#include "meminstr.h"

MemInstr::MemInstr() {
	cmd = n;
	mode = NONE;
	addr = NULL;
	valid = false;
	end = false;
}

MemInstr::MemInstr(string token1, string token2) {
	cmd = n;
	end = false;
	if (SetMode(token1) && SetAddr(token2)) {
		valid = true;
	}
}

MemInstr::MemInstr(string command) {
	end = false;
	if (SetCmd(command)) {
		valid = true;
	}
}

int MemInstr::SetValid() {
	valid = true;
	return 1;
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
	addr = stol(address.substr(2, (address.length()-2)), nullptr, 16);
	return 1;
}

int MemInstr::SetEnd(bool n) {
	end = n;
	return 1;
}

string MemInstr::Dump() {
	string s = "";
	if (cmd == d) { s = "Command is '-d'"; }
	if (cmd == t) { s = "Command is '-t'"; }
	if (cmd == v) { s = "Command is '-v'"; }
	if (cmd == n) {
		if (mode == READ) {
			s += "r";
		} else if (mode == WRITE) {
			s += "w";
		} else if (mode == NONE) {
			s += "w";
		}
		s += " " + strAddr;
	}
	return s;
}

long MemInstr::LAddr(){
	return addr;
}

string MemInstr::SAddr(){
	return strAddr;
}

CmdType MemInstr::GetCmd(){
	return cmd;
}

Mode MemInstr::GetMode(){
	return mode;
}

void MemInstr::CopyInstr(MemInstr &target) {
	target.cmd = this->cmd;
	target.mode = this->mode;
	target.addr = this->addr;
	target.strAddr = this->strAddr;
	target.valid = this->valid;
	target.end = this->end;
}