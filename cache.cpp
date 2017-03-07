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
 
void cache::history(){
	for (int i = 0; i < numset; ++i){
			sets[i].history(flags[1]);
	}	
 }
