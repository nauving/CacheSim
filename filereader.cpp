#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
using namespace std;

int main(int argc, char* argv[]) {
	Parser ptest("file.txt");
	MemInstr m;
	int x = 0;
	do {
		x++;
		m = ptest.NxtPkg();
		if (m.IsValid()) {
			cout << "*****************************\nAt dump " << x << ": " << m.Dump() << '\n';
		}
		cout << "\nLine is: " << ptest.PrintLine() << '\n' << "Token is: " << ptest.PrintToken() << "\n\n";
	} while ((m.IsValid()) && (x <= 14));
	cin >> x;
	return 0;
}