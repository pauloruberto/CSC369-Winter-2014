#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"
#include <limits.h>
//#include "sim.h"

extern int memsize;

extern int debug;

extern struct frame *coremap;

extern pgdir_entry_t *pgdir;

extern char *tracefile;
#define MAXLINE 256 //from sim.h

FILE *fp;
int num_lines; //number of lines read (to get offset in fp)
int *next_used;


/*
Returns the how many lines away the earliest occurence of the vaddr 
in coremap[frame] in the next memsize lines of the tracefile FILE *fp
*/
int earliest_occurrence(int frame) {
	int count = 0;
	char buf[MAXLINE];
	char type; //thrown away not needed for this implementation
	addr_t vaddr = 0;
	pgtbl_entry_t *p; //holds the PTE for the vaddr


	//loop until you get a match with coremap[frame].pte and the vaddr's PTE
	//and return how many "commands" away its next reference is or return
	//max int value if it is never referenced again
	while(fgets(buf, MAXLINE, fp) != NULL) {
		count++;

	// Get the vaddr from the next line in FILE *fp
		if(buf[0] != '=') {
			sscanf(buf, "%c %lx", &type, &vaddr);
			if(debug)  {
				printf("%c %lx\n", type, vaddr);
			}
			//access_mem(type, vaddr); DON'T WANT THIS
		} else {
			continue; // assuming the readline isn't a trace command (?)
		}

	// Lets get the PTE associated with this vaddr
		unsigned idx = PGDIR_INDEX(vaddr); // get index into page directory
		// Use top-level page directory to get pointer to 2nd-level page table
		//(void)idx; // To keep compiler happy - remove when you have a real use.
			//if ((pgdir[idx].pde & PG_VALID) == 0) // it has not been initilized
			//	pgdir[idx] = init_second_level(); // set all the PTE's in the PDE to 0
			//PDE SHOULD ALREADY BE ALLOC'D
		// Use vaddr to get index into 2nd-level page table and initialize 'p'
		pgtbl_entry_t *page_tables = (pgtbl_entry_t *) (pgdir[idx].pde & PAGE_MASK);
		idx = PGTBL_INDEX(vaddr); //now idx points to a PTE when used with a page table
		p = &page_tables[idx];

	// The next _count_ trace command's PTE is the same as this coremap[frame]'s PTE
		if(p == coremap[frame].pte)
			return count;

	} // end while

	// If it gets here the page is NEVER called again
	return INT_MAX; //INT_MAX is defined in limits.h
}


/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {
	// Loop through every pte in the frames
	int i;
	int max = INT_MIN; //from limits.h
	int victim_frame; // the pte's frame that is going to be evicted

	for(i = 0; i < memsize; i++) { // loop through all frames
		// Find the earliest moment the i'th frame's pte's vaddr is referenced
		// in the tracefile
		next_used[i] = earliest_occurrence(i); 
		if(next_used[i] > max) { // if the i'th frame's PTE is furthest away
			max = next_used[i];
			victim_frame = i;
		}
	}

	return victim_frame;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {
	char buf[MAXLINE];
	fgets(buf, MAXLINE, fp);  //just to increment the file pointer
	//now fp points to the same location as tfp in sim.c
	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
	// Use an array to keep track of the next time a page will be needed
	// e.g. A[i], i is the frame (just like in coremap)
		//A[i] = next time coremap[i].pte is used 
	next_used = malloc(memsize * sizeof(int));
	
	//we know tracefile != NULL since we already opened it in sim.c
	if((fp = fopen(tracefile, "r")) == NULL) {
			perror("Error opening tracefile:");
			exit(1);
	}
	return;
}

