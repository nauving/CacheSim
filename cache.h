#pragma once
#include "meminstr.h"
#include "set.h"
#include "parser.h"

#define numsets = 1024;

class cache {
  public:
		read (Meminstr * addr); //read an item from the cache
		write(MemInstr * addr); //write an item to the cache
		print();
		history(int f); //if f = 1 the hist op is a dump debug command
		unpack(Parser p);
	private:
		hash(struct node * addr, int set); //
		set sets[numsets];//set data structure
		int hits[2];  //hits[0] read hits hits[1] write hits
		int misses[2];//misses[0] read hits misses[1] write misses
		int dirty_evicts; //how many times a modified line was written out
		bool flags[2]; //flags[0] = 1 means trace is flags[1] means dump
 };
