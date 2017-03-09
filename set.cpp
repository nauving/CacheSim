#include "set.h"

set::set() {
	for (int i = 0; i < numlines; ++i) {
		head[i] = 0;
		dirty[i] = 0;
		lru[i] = 0;
		valid[i] = 0;
	}
}

void set::sethistory(int x){
	if (valid[0]) {
		cout << "set[" << x << "]:";
	}
	struct node * tmp;
	for (int i = 0; i < numlines; ++i){
		tmp = head[i];
		//show if r/w
		while(tmp){
			if (tmp->flag) {
				cout << "\n\ntmp->hit: " << tmp->hit;//hit or miss
				cout << "\ntmp->tag: " << tmp->tag;//tag
				cout << "\ntmp->dirty: " << tmp->dirty;//dirty
				//print stuff in the line
				cout << "\ntmp->data.SAddr: " << tmp->data.SAddr();
			}
			tmp = tmp->next; //traverse list
		}
	}	
}


void set::updatelru(int val){ //val is the lru of an item in a hit
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

 void set::add(struct node * toadd, int &hit, int &d, int f){
	int tmp = 0;
	for(int i = 0; i < numlines; ++i){
		if (valid[i]){ //line has good data

			if(toadd->data.LAddr() == head[i]->data.LAddr()){ //if there is a cache hit
				dirty[i] = 1;
				hit = 1;
				updatelru(lru[i]);
				lru[i] = 0;
				if(f)
					toadd->next = head[i];				//make head next item in list
				head[i] = toadd;
				head[i]->hit = 1;
				return;
			}
			if (lru[i] == 3) { //item has LRU of 3 and is valid
				tmp = i; //is the item being replace dirty?
			}
		}	
		else{
			dirty[i] = 1;
			valid[i] = 1; //now has valid data
			head[i] = toadd; //head is current item in cache
			head[i]->next = 0;//linked list fun
			return;
		}
	}
	//cout << dirty[tmp];
	//getting here implies that there was no hit
	if (dirty[tmp]) {//track cycles for write to main mem
		d = 1;
	}
	head[tmp]->lru = lru[tmp];
	head[tmp]->dirty = dirty[tmp];
	if(f)
		toadd->next = head[tmp]; //add head to list
	head[tmp] = toadd; //make heat point at new data;
	lru[tmp] = -1;  //lets updatelru() work right
	dirty[tmp] = 1; //write implies data is modified
	updatelru(-1); //passing -1 implies no hit
	hit = 0;
	head[tmp]->hit = 0;
	return;
 }
 
 void set::read(struct node * toread, int &hit, int &d, int f){
	int tmp = 0;
	for(int i = 0; i < numlines; ++i){
		if (valid[i]){ //line has good data
			if(toread->data.LAddr() == head[i]->data.LAddr()){ //if there is a cache hit
				hit = 1;
				updatelru(lru[i]);
				lru[i] = 0;
				if(f)
					toread->next = head[i]; //make head next item in list if -d
				head[i] = toread;
				head[i]->hit = hit;
				return;
			}
			if (lru[i] == 3) //item has LRU of 3 and is valid			
				tmp = i;
		}	
		else{
			valid[i] = 1; //now has valid data
			head[i] = toread; //head is current item in cache
			head[i]->next = 0;//linked list fun
			return;
		}
	}
	//getting here implies that there was no hit 
	if(dirty[tmp])//track cycles for write to main mem
		d = 1;
	if(f)
		toread->next = head[tmp]; //add head to list if -d
	head[tmp] = toread; //make heat point at new data;
	lru[tmp] = -1;  //lets updatelru() work right
	dirty[tmp] = 0; //write implies data is modified
	updatelru(-1); //passing -1 implies no hit
	hit = 0;
	head[tmp]->hit = 0;
	return;
 }

