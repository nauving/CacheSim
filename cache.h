#pragma once
#include "meminstr.h"

#define numsets = 1024;
#define numlines = 4;


class 
set{
	public:
		add(struct node * toadd, int hit); // add an item
		read(struct node * toread, int hit);
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

 set::add(stuct node * toadd, int hit){
	int tmp;
	for(int i = 0; i < numlines; ++i){
		if (valid[i]){ //line has good data

			if(toadd->data.Laddr() = head[i]->data.Laddr()){ //if there is a cache hit
				hit = 1; 
				updatelru(lru[i]);
				lru[i] = 0;
				toadd->next =head[i]; //make head next item in list
				head[i] = toadd;
				return;
			}
			if (lru[i] == 3) //item has LRU of 3 and is valid			
				tmp = i; //is the item being replace dirty?
		}	
		else{
			valid[i] = 1; //now has valid data
			head[i] = toadd; //head is current item in cache
			head->next = 0;//linked list fun
			return;
		}
	}
	//getting here implies that there was no hit 
	if(dirty[tmp])//track cycles for write to main mem	
	toadd->next = head[tmp]; //add head to list
	head[tmp] = toadd; //make heat point at new data;
	lru[tmp] = -1;  //lets updatelru() work right
	dirty[tmp] = 1; //write implies data is modified
	updatelru(-1); //passing -1 implies no hit
	hit = 0;
	return;
 }
 
 set::read(struct node * toread, int hit){
	int tmp;
	for(int i = 0; i < numlines; ++i){
		if (valid[i]){ //line has good data

			if(toread->data.Laddr() = head[i]->data.Laddr()){ //if there is a cache hit
				hit = 1; 
				updatelru(lru[i]);
				lru[i] = 0;
				toread->next =head[i]; //make head next item in list
				head[i] = toread;
				return;
			}
			if (lru[i] == 3) //item has LRU of 3 and is valid			
				tmp = i;
		}	
		else{
			valid[i] = 1; //now has valid data
			head[i] = toadd; //head is current item in cache
			head->next = 0;//linked list fun
			return;
		}
	}
	//getting here implies that there was no hit 
	if(dirty[tmp])//track cycles for write to main mem	
	toread->next = head[tmp]; //add head to list
	head[tmp] = toread; //make heat point at new data;
	lru[tmp] = -1;  //lets updatelru() work right
	dirty[tmp] = 0; //write implies data is modified
	updatelru(-1); //passing -1 implies no hit
	hit = 0;
	return;
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
	int hit = 0;
	int setnum;
	hash(addr, setnum);//figure out what set the data should be sough in
	sets[setnum].read(addr, hit);
	if(hit)
		++hits;
	else
		++missees;
 }
 
 cache::write(struct node * addr){
	int hit = 0;
	int setnum;
	hash(addr, setnum);//figure out which set the data will be added to
	sets[setnum].add(addr, hit);
	if(hit)
		++hits;
	else
		++missees;
 }
