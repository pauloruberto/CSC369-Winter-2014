#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h> 
#include <pthread.h>
#include <string.h>

//Booleans for specific debug modes
#define DEBUG_MYMALLOC 0
#define DEBUG_MYFREE 0

#define PAGE 4096 //minimum size for sbrk(), 4kb
#define ALIGNMENT 8 //for aligning on 8-byte boundary

//TODO   fix for test case 7-longrandom
//sometimes will seg fault and I don't know why

//Struct for the free list and free list nodes
//Nodes used in the free list, isFree is 1 if the mem chunk is free
typedef struct __node {
  bool isFree; //1 if mem chunk is free, 0 if in use
  unsigned int size; //length of the memory chunk includes nodeSize
  struct __node *next; //next node
  struct __node *prev; //previous node
} node;

//Global vars
node *freelist_head;
static pthread_mutex_t __LOCK = PTHREAD_MUTEX_INITIALIZER;
static size_t nodeSize;

//Prints all the content and information about the freelist, only used in debug
void printHeap() {
  fprintf(stderr, "~~~~~~~~~~~~~~~~~~~~~~ HEAP ~~~~~~~~~~~~~~~~~~~~~\n");
  fprintf(stderr, "freelist_head address: %p\n", freelist_head);
  node *memchunk = NULL;  
  int count = 1;
  for(memchunk = freelist_head; memchunk != NULL; memchunk = memchunk->next) {
    fprintf(stderr, "\tNODE %d :\n", count++);
    fprintf(stderr, "\t\taddress: %p\n", memchunk);
    if(memchunk->isFree == 0)
      fprintf(stderr, "\t\tdata address: %p\n", (char *)memchunk + nodeSize);
    else
      fprintf(stderr, "\t\tdata address: N/A\n");      
    fprintf(stderr, "\t\tsize: %d\n", (int) memchunk->size);
    fprintf(stderr, "\t\tprev: %p\n", memchunk->prev);
    fprintf(stderr, "\t\tnext: %p\n", memchunk->next);
    fprintf(stderr, "\t\tisFree: %d\n", (int) memchunk->isFree); 
  }
  fprintf(stderr, "~~~~~~~~~~~~~~~~~~~ END OF HEAP ~~~~~~~~~~~~~~~~~~\n\n");
}

//Fetches a new page from the OS of size PAGE (4096)
//Returns a node ptr to the start of the new page
void *getNewPage() {
  void *start = (void *) sbrk(PAGE);
  if (start == ((void *) -1)) {
    perror("sbrk"); //OS is screwing you of your right for memory!!!
    exit(1);
  }

  #if DEBUG_MYMALLOC
  fprintf(stderr, "GETTING NEW PAGE AT %p\n", start);
  #endif

  return start;
}

//takes a free memchunk and splits into two nodes
//RETURNS: the value of the address of the not free node after the header
void *splitAndUse(node *memchunk, unsigned int size) {
  
  #if DEBUG_MYMALLOC
  fprintf(stderr, "In splitAndUse for memchunk:%p for size: %d\n", memchunk, size);
  #endif

  //typecasting memchunk to a char ptr in order to increment it byte by byte
  //then typecasting it back to node ptr because of compiler warnings
  node *new_node = (node *) ((char *) memchunk + nodeSize + size); //address of free block, points to start of new header
  size_t old_size = memchunk->size;
  node *old_next = memchunk->next;

  memchunk->isFree = 0;
  memchunk->size = nodeSize + size; //header and data
  memchunk->next = new_node;
  //memchunk->prev = memchunk->prev //unchanged

  new_node->isFree = 1;
  new_node->prev = memchunk; //the in use block
  new_node->next = old_next; //keep the chain connected
  new_node->size = old_size - memchunk->size; //calculate remaining free space, INCLUDES THE HEADER

  return (char *)memchunk + nodeSize; //address of requested malloc space
}

//Coalesce memchunk and memchunk->next iff they are both free
void coalesce(node *memchunk) {
  //assert both are free in order to coalesce
  if(memchunk->isFree != 1 || memchunk->next->isFree != 1) {
    return;
  }

  memchunk->size += memchunk->next->size; //note that size includes nodeSize
  memchunk->next->prev = memchunk;
  memchunk->next = memchunk->next->next; //after updating prev because might point to NULL

  #if DEBUG_MYFREE
  fprintf(stderr, "Finished coalescing\n");
  printHeap();
  #endif  
}


/* mymalloc_init: initialize any data structures that your malloc needs in
  order to keep track of allocated and free blocks of
  memory.  Get an initial chunk of memory for the heap from
  the OS using sbrk() and mark it as free so that it can  be
  used in future calls to mymalloc()
*/

int mymalloc_init() {
  freelist_head = (node *) getNewPage();
  nodeSize = sizeof(node);

  freelist_head->size = PAGE;
  freelist_head->isFree = 1;
  freelist_head->prev = NULL;
  freelist_head->next = NULL;
  
  #if DEBUG_MYMALLOC
  fprintf(stderr, "INITIALIZING\n");
  printHeap();
  #endif  

  return 0; // non-zero return value indicates an error
}

/* mymalloc: allocates memory on the heap of the requested size. The block
of memory returned should always be padded so that it begins
and ends on a word boundary.
unsigned int size: the number of bytes to allocate.
retval: a pointer to the block of memory allocated or NULL if the 
memory could not be allocated. 
(NOTE: the system also sets errno, but we are not the system, 
so you are not required to do so.)
*/
void *mymalloc(unsigned int size) {
  if (size <= 0) //basic error check
  	return NULL;

  pthread_mutex_lock(&__LOCK);

  //we don't have a heap yet? this is just for error checking
  if (freelist_head == NULL) {
    freelist_head = getNewPage();
  }

  size += 8 - (size + nodeSize) % ALIGNMENT; //for 8-byte alignment

  node *memchunk;  

  for(memchunk = freelist_head; memchunk != NULL; memchunk = memchunk->next) {
    //if there is a free memchunk that is big enough to hold size + node
    if (memchunk->size >= size + 2*sizeof(node) && memchunk->isFree == 1) {
      break;
    }

    if (memchunk->next == NULL) {
      memchunk->next = (node *) getNewPage();
      memchunk->next->next = NULL;
      memchunk->next->prev = memchunk;
      memchunk->next->size = PAGE;
      memchunk->next->isFree = 1;

      memchunk = memchunk->next;  
      break;
    }
  }

  void *ptr; //address for memory for requested malloc'd size
  ptr = splitAndUse(memchunk, size);
  memset(ptr, '\0', size); //get rid of garbage/left over data

  #if DEBUG_MYMALLOC
  fprintf(stderr, "FINISHED MALLOC:\n");
  printHeap();
  #endif 

  pthread_mutex_unlock(&__LOCK);
  return ptr;
} //end mymalloc


/* myfree: unallocates memory that has been allocated with mymalloc.
     void *ptr: pointer to the first byte of a block of memory allocated by 
                mymalloc.
     retval: 0 if the memory was successfully freed and 1 otherwise.
             (NOTE: the system version of free returns no error.)
*/
unsigned int myfree(void *ptr) {
  //basic error checking
  if (ptr == NULL)
    return 1;

  pthread_mutex_lock(&__LOCK);
  //Need to access the node information of this memchunk, pointer arithmetic similar to splitAndUse
  node *header = (node *) ((char *)ptr - nodeSize);

  #if DEBUG_MYFREE  
  fprintf(stderr, "header is at %p for ptr address at %p\n", header, ptr);
  #endif

  //Error check: if the block is already free
  if(header->isFree == 1) {
    pthread_mutex_unlock(&__LOCK);
    return 1;
  }

  header->isFree = 1; //make this memchunk available for future use
  
  //previous memchunk could be free, likewise for next memchunk
  if(header->prev != NULL) {
    if(header->prev->isFree == 1) {

      #if DEBUG_MYFREE
      fprintf(stderr, "Coalescing %p and %p\n", header->prev, header);
      #endif

      coalesce(header->prev);
      header = header->prev; //because coalesce() merged this to the prev node
    }
  }

  if(header->next != NULL) {
    if(header->next->isFree == 1) {

      #if DEBUG_MYFREE
      fprintf(stderr, "Coalescing %p and %p\n", header, header->next);
      #endif
      
      coalesce(header);
    }
  }

  #if DEBUG_MYFREE
  fprintf(stderr, "FININSHED FREE:\n");
  printHeap();
  #endif  

  pthread_mutex_unlock(&__LOCK);
  return 0;
}

