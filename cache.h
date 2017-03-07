#pragma once
#include "meminstr.h"

#define numsets = 1024;
#define numlines = 4;


class 
set{
	public:
		add(struct node * toadd, int hit, int d); // add an item
		read(struct node * toread, int hit, int d);
		updatelru();
		history(); //show line history
		init();//initialize the set
	private:
		struct node head [numlines];//linked list of lines, being head implies that that item is currently in the cache the rest are line history
		int lru[numlines]; 	//// 0-3, 3 gets evicted on write
		bool valid[numlines]; // 1 if data has been written
		bool dirty[numlines]; // 1 if modified contents not yet written to memory
};

set::history(){
		node * tmp;
		for (int i = 0; i < numlines; ++i){
			tmp  = head[i]
			while(tmp){
				//print stuff in the line
				tmp->data.print();
				tmp = tmp -> next; //traverse list
			}
		}	
}

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

 set::add(stuct node * toadd, int hit, int d){
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
		d = 1;
	toadd->next = head[tmp]; //add head to list
	head[tmp] = toadd; //make heat point at new data;
	lru[tmp] = -1;  //lets updatelru() work right
	dirty[tmp] = 1; //write implies data is modified
	updatelru(-1); //passing -1 implies no hit
	hit = 0;
	return;
 }
 
 set::read(struct node * toread, int hit, int d){
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
		d = 1;
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
		read (Meminstr * addr); //read an item from the cache
		write(MemInstr * addr); //write an item to the cache
		print();
		history();
		dump(); //called if -d command is 
	private:
		hash(struct node * addr, int set); //
		set sets[numsets];//set data structure
		int hits[2];  //hits[0] read hits hits[1] write hits
		int misses[2];//misses[0] read hits misses[1] write misses
		int dirty_evicts; //how many times a modified line was written out
		bool flags[2]; //flags[0] = 1 means trace is flags[1] means dump
 };
 
 cache::read(Meminstr * addr){
	int hit = 0;
	int setnum = 0;
	int dirt = 0;
	
	node * tmp = new node;
	tmp->data = addr;
	tmp->next = 0;
	tmp->flag = flags[1];
	
	hash(addr, setnum);//figure out what set the data should be sough in
	sets[setnum].read(tmp, hit, dirt);
	if(dirt)
		++dirty_evicts
	if(hit)
		++hits[0];
	else
		++missees[0];
 }
 
 cache::write(MemInstr* addr){
	int hit = 0;
	int setnum = 0;
	int dirt = 0;; //used to tell if a modified line was evicted
	
	node * tmp = new node;
	tmp->data = addr;
	tmp->next = 0;
	tmp->flag = flags[1];
	
	hash(addr, setnum);//figure out which set the data will be added to
	sets[setnum].add(tmp, hit, dirt);
	if(dirt)
		++dirty_evicts
	if(hit)
		++hits[1];
	else
		++missees[1];
 }
 
 cache::print(){ // give info on hits and misses
	int tmp1 hits[0] + misses[0]; //total reads
	int tmp2 hits[1] + misses[1]; //total writes
	
	printf("There were %d Cache stores", tmp2);
	printf("There were %d Cache loads", tmp1);
	tmp2 = tmp2 + tmp1; //total mem accesses
	printf("There were %d total memory refrences",tmp2);
	
	printf("There were %d Cache read hits", hits[0]);
	printf("There were %d Cache write hits", hits[1]);
	tmp1=hits[0]+hits[1]; //total hits
	printf("There were %d total Cache hits", tmp1);
	
	printf("There were %d Cache read misses", misses[0]);
	printf("There were %d Cache write misses", misses[1]);
	tmp1 = misses[0]+misses[1]; //total misses
	printf("There were %d total Cache misses", tmp1);
	tmp1 = misses[0] + misses[1]
	printf("There were %d stream ins",tmp1); //i think that this happens when there is a miss
	printf("There were %d stream outs",dirty_evicts);// happens on eviction of line w dirty bit set to 1

	tmp1 = (50 * misses) + hits;
	printf("Exectution took %d cycles",tmp);//print total cycles w cahce
	tmp2 = (50 * misses) + (50 * hits);
	printf("Without the cache execution would have taken %d Cycles", tmp2);//print how many cycles w/o cache
	tmp2 = tmp2 - tmp1;
	printf("Having the Cache Saved %d Cycles",tmp2);//print cycles saved by cache
 }
 
 cache::history(){
	for (int i = 0; i < numset; ++i){
			sets[i].history();
	}	
 }
