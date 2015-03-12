#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int start; //global start

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict() {
	//want to return the start
	int frame = start;
	//increment index (the start of the FIFO queue)
	start++;
	//corner case: if now at end of queue is the end, the actual start is at the
	//front of the queue since allocate_frame() replaces the page
	//e.g. queue: 1,2,3.  remove 1 -> 4,2,3  remove 2 -> 4,5,3  remove 3 ->4,5,6
	//always want to remove the "minimum of the queue"
	if (start == memsize) { //if past end of queue (recall queue starts at 0)
		start = 0; //note that memsize is constant
	}

	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {
	//not needed
	return;
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {
	start = 0; //initialize the 'queue'
	//pages are allocated in order so this kind of like an index
}
