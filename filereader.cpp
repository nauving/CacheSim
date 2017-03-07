#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "cache.h"
using namespace std;

/*int main(argc, argv[]){
	string str;
	cout << "Please enter the name of the file that contains the inputs: ";
	cin >> str;
	Parser parse(str);
	cache c();
	int on = 1;
	while(on){
		on = c.unpack(parse);
	}
}*/


int main(int argc, char* argv[]) {
	Parser ptest("file.txt");
	MemInstr m;
	int x = 0;
	do {
		x++;
		m = ptest.NxtPkg();
		if (m.IsValid() && !p.IsEof()) {
			cout << "*****************************\nAt dump " << x << ": " << m.Dump() << '\n';
		}
		cout << "\nLine is: " << ptest.PrintLine() << '\n' << "Token is: " << ptest.PrintToken() << "\n\n";
	} while ((m.IsValid()) && (!p.IsEof());
	cin >> x;
	return 0;
}

