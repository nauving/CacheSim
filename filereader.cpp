#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
using namespace std;

int main(int argc, char* argv[]) {
	Parser ptest("file.txt");
	string s;

	for (int i = 0; i <= 7; i++) {
		s = ptest.PrintLine();
		cout << s << '\n';
		s = ptest.PrintToken();
		cout << s << '\n';
	}
	cin >> s;
	return 0;
}