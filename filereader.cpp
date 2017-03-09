#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "cache.h"
#include "meminstr.h"
using namespace std;

int main(int argc, char * argv[]){
	Parser parse = Parser("file.txt");
	cache c = cache();
	int on = 1;
	int x = 0;
	while(on){
		x++;
		on = c.unpack(&parse);
	}
	if (!c.getVersion()) {
		c.cTrace(parse);
		c.history();
		c.print();
	}
	else {
		cout << "Cache Simulator v0.9\n";
	}
}
