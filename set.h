#pragma once
#include "meminstr.h"

#define numlines = 4;

struct node{
	MemInstr * data;
	int lru; //for dump command
	int tag; //for dump command
	int dirty; //valid left out because its only valid if there is data to print
	int hit;
	node * next; //dirty replaced by somthing implies a stream out.
	int flag;   //first operation implies a stream in
}

class set{
	public:
		set::add(struct node * toadd, int hit, int d);    // add an item
		set::read(struct node * toread, int hit, int d);
		set::updatelru();
		set::history(int f);    //show line history
		set();                  //initialize the set
	private:
		struct node head [numlines];  //linked list of lines, being head implies that that item is currently in the cache the rest are line history
		int lru[numlines];            // 0-3, 3 gets evicted on write
		bool valid[numlines];         // 1 if data has been written
		bool dirty[numlines];         // 1 if modified contents not yet written to memory
};
