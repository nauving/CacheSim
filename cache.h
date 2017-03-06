#pragma once
#include "meminstr.h"

#define numsets = 1024;
#define numlines = 4;


class 
set{
	public:
		add(char * toadd); // add an item
		updatelru();
		history(); //show line history
	private:
		struct node head [numlines];//linked list of lines, being head implies that that item is currently in the cache the rest are line history
		int lru[numlines]; 	//// 0-3, 3 gets evicted on write
		bool valid[numlines]; // 1 if data has been written
		bool dirty[numlines]; // 1 if modified contents not yet written to memory
};

set::updatelru(){
	for (int i = 0; i < numlines; ++i){
		lru[i]+=1; 	//add one to all LRU bits.	
}					//new lines init to lru 0, doesnt matter if unused lines are updated

 set::add(void * toadd){
	new line = toadd;
	int leastrecent = -1; //se to negative bc 0 is a used index
	//check valid
	for(int i = 0; i < numlines; ++i){
		if (valid[i]){ //line has good data
			if (lru[i] == 3){
				//is the item being replace dirty?
				// if line op = read no need to update dirty
				//if write need to update 
				toadd->next = head[i]; //add head to list
				head[i] = toadd; //make heat point at new data;
				lru[i] = -1; //lets updatelru() work right
				updatelru();
				return 0;
			}	
		}	
		else{
			valid[i] = 1; //now has valid data
			head[i] = toadd; //head is current item in cache
			head->next = 0;//linked list fun
		}
	}
	
 }

class 
cache {
  public:
		read (addr); //read an item from the cache
		write(addr); //write an item to the cache
	private:
		set sets[numsets];//set data structure
		int hits;
		int misses;
 };
 
 cache::read(addr){
	//need to move data being passed in to a line
	 
 }
 
 cache::write(addr){
	//need to move data being passed in to a line
	 
 }
