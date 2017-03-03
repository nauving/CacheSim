#pragma once

#define numsets = 1024;
#define numlines = 4;
#define lrusize = 2;

class 
line{
  public:
  //show line history
  //add an item
  private:
  //address (without leading 0x)
  //operation (r/w)
  int lru; 
  line * hist; //history of line
};

class 
set{
  public:
  add(); // add an item
  evict(); //remove an item 
  private:
  line lines [numlines];//line data structure
  int lru[lrusize]; //for updating LRU bits one just modified = 0, ++all others
};

class 
cache {
  public:
    read (addr); //read an item from the cache
    write(addr); //write an item to the cache
    check(addr); // see if an item is in the cache
   private:
   set sets[numsets];//set data structure
 };
