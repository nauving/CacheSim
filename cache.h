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
  line * hist; //history of line
};

class 
set{
  public:
  private:
  line lines [numlines];//line data structure
  //lru
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
