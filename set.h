#pragma once
#include "meminstr.h"

#define numlines = 4;

class 
Set{
	public:
		Set::add(struct node * toadd, int hit, int d);    // add an item
		Set::read(struct node * toread, int hit, int d);
		Set::updatelru();
		Set::history(int f);    //show line history
		Set();                  //initialize the set
	private:
		struct node head [numlines];  //linked list of lines, being head implies that that item is currently in the cache the rest are line history
		int lru[numlines];            // 0-3, 3 gets evicted on write
		bool valid[numlines];         // 1 if data has been written
		bool dirty[numlines];         // 1 if modified contents not yet written to memory
};
