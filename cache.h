#pragma once

#define numsets = 1024;
#define numlines = 4;


struct
line{
  bool op; // 1 if read 0 if write;
  line * next;	//history of line, 0 if no history
};

class 
set{
  public:
  add(char * toadd); // add an item
  updatelru();
  history(); //shpw t
  evict(); //remove an item 
  private:
  struct line head [numlines];//linked list of lines, being head implies that that item is currently in the cache the rest are line history
  int lru[numlines]; 	//// 0-3, 3 gets evicted on write
  bool valid[numlines]; // 1 if data has been written
  bool dirty[numlines]; // 1 if modified contents not yet written to memory
  int hits;
  int misses;
};

set::updatelru(){
	for (int i = 0; i < numlines; ++i){
		lru[i]+=1; //add one to all LRU bits
	}
}

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
		
		else
				//put in first invalid line
	}
	
 }

class 
cache {
  public:
    read (addr); //read an item from the cache
    write(addr); //write an item to the cache
    check(addr); // see if an item is in the cache
   private:
   set sets[numsets];//set data structure
 };
