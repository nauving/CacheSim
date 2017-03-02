# CacheSim
PSU Winter 2017 ECE 486 Cache Simulator Project

MODULES AS FOLLOWS

PARSING MODULE
CACHE MODULE
  -figure out what the memory location is, read or write
  -write -> write to cache
  read: see if in cache, if not grab from memory
  -update LRU bits
  
  if need be replace an item via eviciton based on LRU bits
  also update dirty and valid bits
  tracking hits/misses
  tracking expended cycles
IO MODULE
