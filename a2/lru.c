#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <limits.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

pgtbl_entry_t *lru_pte; //points to the LRU pte
unsigned long max_timestamp; //keeps track of the latest timestamp

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	//need to set a new LRU
		//search every single pte refer to allocate frame
	pgtbl_entry_t *old_lru_pte = lru_pte; // keep track of old minimum
	pgtbl_entry_t *current; // so I don't have to keep indexing coremap[]

	int i;
	int frame; // the return value; index of coremap[], whose pte == old_lru_pte 
	unsigned long min = ULONG_MAX; //for finding a new LRU, ULONG_MAX is from limits.h

	//recall that coremap[i] (i is the PFN) gives you a struct frame

	for(i = 0; i < memsize; i++) {
		// look for a valid timestamp that is the minimum and NOT old_lru_pte
		// 3 if statements to make it easy to read
		current = coremap[i].pte;
		if(current->frame & PG_VALID) //page needs to be in memory
			if(current != old_lru_pte)
				if(current->timestamp < min) {
					min = current->timestamp;
					lru_pte = current; // the new minimum
				}

		// now have to find the frame that corresponds to the LRU pte
		if(current == old_lru_pte)
			frame = i;
	}

	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	if (lru_pte == NULL) //initialize if its the first time
		lru_pte = p;
	p->timestamp = max_timestamp; //assign the timestamp to this pte
	max_timestamp++; //increment timestamp

	if(max_timestamp == ULONG_MAX) { // gotta be vary of overflows!
		perror("may overflow with max_timestamp in lru");
		exit(1);
	}

	return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	lru_pte = NULL;
	max_timestamp = 0;
}
