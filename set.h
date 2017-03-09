#pragma once
#include "meminstr.h"

#define numlines 4

struct node{
	MemInstr data;
	int lru; //for dump command
	int tag; //for dump command
	int dirty; //valid left out because its only valid if there is data to print
	int hit;
	node * next; //dirty replaced by somthing implies a stream out.
	int flag;   //first operation implies a stream in
};

class set{
	public:
		set();		// set constructor forward declaration
		void add(struct node * toadd, int &hit, int &d, int f);    // add an item
		void read(struct node * toread, int &hit, int &d, int f);
		void updatelru(int val);
		void sethistory();    //show line history
	private:
		struct node * head [numlines];  //linked list of lines, being head implies that that item is currently in the cache the rest are line history
		int lru[numlines];            // 0-3, 3 gets evicted on write
		bool valid[numlines];         // 1 if data has been written
		bool dirty[numlines];         // 1 if modified contents not yet written to memory
};
