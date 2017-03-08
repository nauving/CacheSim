#include <stdio.h>
#include "cache.h"

using namespace std;

int cache::unpack(Parser * p){
	MemInstr temp = MemInstr();
	p->NxtPkg(temp);
	if (p->IsEof()) {
		return 0;
	}
	else if (temp.IsEnd()) {
		return 0;
	}
	else if (temp.IsValid()) {
		CmdType c = temp.GetCmd();
		if (c != n) {
			if (c == t) {
				flags[0] = true;
				return 1;
			} else if (c == v) {
				//DO PRINTVERSION()
				return 0;
			} else if (c == d) {
				flags[1] = true;
				return 1;
			} //end if
		} else {
			long l;
			Mode m = temp.GetMode();
			if (m == READ) {
				 l = temp.LAddr();
				 read(temp);
				return 1;
			} else if (m == WRITE) {
				l = temp.LAddr();
				write(temp);
				return 1;
			}
		}
	}
	return 0;
}

void cache::read(MemInstr &addr){
	int hit = 0;
	int setnum = 0;
	int dirt = 0;
	
	node * tmp = new node;
	tmp->data = &addr;
	cout << tmp->data->Dump();
	tmp->next = 0;
	tmp->flag = flags[1];
	
	setnum = hash(tmp);//figure out what set the data should be sough in
	sets[setnum].read(tmp, hit, dirt);
	if (dirt)
		++dirty_evicts;
	if (hit)
			++hits[0];
	else
		++misses[0];
 }
 
int cache::hash(node * addr) {
	return (addr->data->LAddr() % numsets);
}

 void cache::write(MemInstr &addr){
	int hit = 0;
	int setnum = 0;
	int dirt = 0;; //used to tell if a modified line was evicted
	
	node * tmp = new node;
	tmp->data = &addr;
	cout << tmp->data->Dump();
	tmp->next = 0;
	tmp->flag = flags[1];
	
	setnum = hash(tmp);//figure out which set the data will be added to
	sets[setnum].add(tmp, hit, dirt);
	if (dirt)
		++dirty_evicts;
	if(hit)
		++hits[1];
	else
		++misses[1];
 }
 
 void cache::print(){ // give info on hits and misses
	int tmp1 = hits[0] + misses[0]; //total reads
	int tmp2 = hits[1] + misses[1]; //total writes
	
	printf("\nThere were %d Cache stores", tmp2);
	printf("\nThere were %d Cache loads", tmp1);
	tmp2 = tmp2 + tmp1; //total mem accesses
	printf("\nThere were %d total memory refrences",tmp2);
	
	printf("\nThere were %d Cache read hits", hits[0]);
	printf("\nThere were %d Cache write hits", hits[1]);
	tmp1=hits[0]+hits[1]; //total hits
	printf("\nThere were %d total Cache hits", tmp1);
	
	printf("\nThere were %d Cache read misses", misses[0]);
	printf("\nThere were %d Cache write misses", misses[1]);
	tmp1 = misses[0]+misses[1]; //total misses
	printf("\nThere were %d total Cache misses", tmp1);
	tmp1 = misses[0] + misses[1];
	printf("\nThere were %d stream ins",tmp1); //i think that this happens when there is a miss
	printf("\nThere were %d stream outs",dirty_evicts);// happens on eviction of line w dirty bit set to 1

	tmp1 = (50 * tmp1) + hits[0] + hits[1];
	printf("\nExectution took %d cycles", tmp1);//print total cycles w cahce
	tmp2 = (50 * (misses[0] + misses[1])) + (50 * (hits[0] + hits[1]));
	printf("\nWithout the cache execution would have taken %d Cycles", tmp2);//print how many cycles w/o cache
	tmp2 = tmp2 - tmp1;
	printf("\nHaving the Cache Saved %d Cycles",tmp2);//print cycles saved by cache
 }
 
void cache::history(){
	for (int i = 0; i < numsets; ++i) {
			sets[i].history(flags[1]);
	}	
 }
