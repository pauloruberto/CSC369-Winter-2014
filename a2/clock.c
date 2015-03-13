#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int i; //initialize "head" of clock

// if timestamp == 0, PTE hasn't been used; if 1 has been used	

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	pgtbl_entry_t *current; //so don't have to keep indexing coremap[]
	
	// clock head's frame is always at frame 0
	while(1) {
		current = coremap[i].pte;
		if((current->frame & PG_REF) == 0)
			break; //return the PFN (i.e. index in the coremap) (line 44)
		
		// now set it to not used since it has been checked
		current->frame &= ~PG_REF;
		i++;

		// need to move to start of coremap if next iteration is >= memsize
		// because we may have starting somewhere in the middle of coremap
		// and because we want to loop "circularly" until we find an unused PTE
		if(i + 1 >= memsize) 
			i = 0;
	}

	return i;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	p->frame |= PG_REF;
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {	
	i = 0; // for some reason need to initialize and reference it to work
	// refer to fifo.c
}
