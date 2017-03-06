#pragma once
#include "meminstr.h"

#define numsets = 1024;
#define numlines = 4;


class 
set{
	public:
		add(struct node * toadd); // add an item
		updatelru();
		history(); //show line history
		init();//initialize the set
	private:
		struct node head [numlines];//linked list of lines, being head implies that that item is currently in the cache the rest are line history
		int lru[numlines]; 	//// 0-3, 3 gets evicted on write
		bool valid[numlines]; // 1 if data has been written
		bool dirty[numlines]; // 1 if modified contents not yet written to memory
};

set::init(){
	for (int i = 0; i < numlines; ++i){
		lru[i] = 0;
		valid[i] = 0;
		dirty[i] = 0;
	}
}

set::updatelru(int val){ //val is the lru of an item in a hit
	if (val == -1){
		for (int i = 0; i < numlines; ++i){
			lru[i]+=1; 	//add one to all
		}	
	}
	else{ //there was a hit
		for (int i = 0; i < numlines; ++i){
			if (lru[i] < val)
				lru[i]+=1; 	//add one to lrus less than the item that was a hit	
		}	
	}
}					//new lines init to lru 0, doesnt matter if unused lines are updated

 set::add(stuct node * toadd){
	new line = toadd;
	for(int i = 0; i < numlines; ++i){
		if (valid[i]){ //line has good data
			
			if(){ //if there is a cache hit
				
			}
			
			if (lru[i] == 3){
				//is the item being replace dirty?
				toadd->next = head[i]; //add head to list
				head[i] = toadd; //make heat point at new data;
				lru[i] = -1;  //lets updatelru() work right
				dirty[i] = 1; //write implies data is modified
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
		read (struct node * addr); //read an item from the cache
		write(struct node * addr); //write an item to the cache
		print();
		history();
	private:
		hash(struct node * addr, int set); //
		set sets[numsets];//set data structure
		int hits;  //counts cache hits
		int misses;//counts cache misses
 };
 
 cache::read(struct node * addr){
	int setnum;
	hash(addr, setnum);//figure out what set the data should be sough in
	sets[setnum].add(addr)
	//if hits
	//if miss
	 
 }
 
 cache::write(struct node * addr){
	int setnum;
	hash(addr, setnum);//figure out which set the data will be added to
	//if hit
	//if miss
 }
