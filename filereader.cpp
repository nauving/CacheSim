#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "cache.h"
using namespace std;

int main(char argc, int argv[]){
	Parser parse = Parser("file.txt");
	cache c = cache();
	int on = 1;
	int x = 0;
	while(on){
		x++;
		on = c.unpack(&parse);
		cout << "\nvalue of on is: " << on << " THANKS HAVE A NICE DAY";
	}
	cout << "\nEnd!";
	c.history();
}

/*
int main(int argc, char* argv[]) {
	Parser ptest("file.txt");
	MemInstr m;
	int x = 0;
	do {
		x++;
		m = ptest.NxtPkg();
		if (m.IsValid() && !ptest.IsEof()) {
			cout << "*****************************\nAt dump " << x << ": " << m.Dump() << '\n';
		}
		cout << "\nLine is: " << ptest.PrintLine() << '\n' << "Token is: " << ptest.PrintToken() << "\n\n";
	} while ((m.IsValid()) && (!ptest.IsEof()));
	return 0;
}
*/
