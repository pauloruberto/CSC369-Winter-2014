#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

// if timestamp == 2 it means it is the "start of the clock" and unusued
// if timestamp == 3 it means start of the clock and used
// if 0, hasn't been used; if 1 has been used	

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	int i;
	int head_frame; //frame that holds "head" of the clock
	pgtbl_entry_t *current; //so don't have to keep indexing coremap[]

	// first find "head" of the clock, important for approximating LRU
	for(i = 0; i < memsize; i++) {
		current = coremap[i].pte;
		if(current->timestamp == 2 || current->timestamp == 3) {
			head_frame = i;
			break;
		}
	}
	
	for(i = head_frame; i < memsize; i++) {
		current = coremap[i].pte;
		if(current->timestamp == 0 || current->timestamp == 2)
			return i; //return the PFN (i.e. index in the coremap)
		
		// now set it to not used since it has been checked
		if(current->timestamp == 3)
			current->timestamp = 2;
		else // if(current->timestamp == 1), remove a redundant if statement
			current->timestamp = 0;

		// need to move to start of coremap if next iteration is >= memsize
		// because we may have starting somewhere in the middle of coremap
		// and because we want to loop "infinitely" until we find an unused PTE
		if(i + 1 >= memsize)
			i = 0;
	}

	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	if (p->timestamp == 2)
		p->timestamp = 3; // shows that the "head" of clock is in use 
	else
		p->timestamp = 1; // show that it is in use
	
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {	
	int i;
	int start = 0; 

	for(i = 0; i < memsize; i++) {
		if(start == 0) // initialize the "head" of the clock as unused
			coremap[i].pte->timestamp = 2;
		else
			coremap[i].pte->timestamp = 0
	}
}
