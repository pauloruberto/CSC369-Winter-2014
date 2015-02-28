# Assignment 1 - Malloc Rodeo 

## Introduction

Your mission is to use the system call <tt>sbrk</tt> to implement your own versions of <tt>malloc</tt> and <tt>free</tt>. The exercise should make you think about memory allocation and deallocation, including defragmentation. (Relocation of virtual addresses in memory is another important memory management concept, but we will tackle that idea in class, later.)

Before you start work, you should complete a set of readings about memory:

## Requirements

<p>Your <tt>mymalloc</tt> and <tt>myfree</tt> functions should operate in the same way as <tt>malloc</tt> and <tt>free</tt> with some exceptions.  They will be expected to operate correctly in a multi-threaded program. (You can assume that <tt>sbrk</tt> is thread safe.) The <tt>free</tt> function does not return any value, and your <tt>myfree</tt> function will return a 0 on success, and -1 on failure.  It will also print an appropriate error message to <tt>stderr</tt>.  The error conditions are trying to free memory that has not been allocated, freeing memory that has already been freed, and passing a bad address (e.g., NULL or other bad pointers) to <tt>myfree</tt>.

You must not use <tt>mmap</tt> or the system <tt>malloc</tt>for this assignment.

## Starter Code

The starter code in your svn repository consists of several files including <tt>mymemory.c</tt> that will contains two memory management functions</a> called <tt>mymalloc</tt> and <tt>myfree</tt> and a <tt>test_malloc.c</tt> that demonstrates how your <tt>mymalloc</tt> and <tt>myfree</tt> functions will be invoked. Note that the test program uses pthreads, so you will need to include the pthread compilation flag. You may modify this test program for testing purposes, but we will use our own test harness, so make sure your <tt>mymemory.c</tt> works with our version of the test harness!  The starter code also includes a <tt>sysmemory.c</tt> that can be used to see how the test_malloc code works.  However, the implementation of <tt>malloc</tt> on CDF does not use <tt>sbrk</tt> and will not immediately reuse freed blocks or do coalescing, so you won't see the same results with <tt>malloc</tt> as we expect with <tt>mymalloc</tt>.

<p>The test program loads "traces" which are text files containing a series of malloc and free operations to perform. There are several example traces included with the starter code..  You will want to create additional traces for testing. In particular, consider various access patterns (mallocing large items, freeing every other malloc, and then mallocing smaller items, for example) that might cause interesting memory usage if your allocator does not allocate space nicely or coalesce it. To help you generate traces, there  is a python script, <tt>genrandom.py</tt> that generates random traces</a>.

## Breaking down the problem

<p>The requirements above should be sufficient to complete the assignment.  To complete it effectively and efficiently, you will want to break it down into tasks that will allow you to incrementally implement and test your program.  These are skills that you should already have as a third year student, but below is a list of steps that correspond to the marking rubric that will help you organize your work. These tasks should be completed in order and you should not expect to get even part marks for a later component if early components do not work.  Also, the very small traces included with the starter code correspond to the steps below.

Note that code quality will be worth 10%. If the graders find your code difficult to read, or poorly organized, you will not get full marks in this section.

### Step 1: <tt>mymalloc</tt> single-threaded implementation (15%)

Implement a basic version of <tt>mymalloc</tt> that works well with a single thread. You should be confident that the trace [1-simple-malloc]() produces correct results before moving to the next step. How can you convince yourself that it produces the correct result?

Details:

*   The <tt>mymalloc_init()</tt> function will be called by the test harness before any
calls to <tt>mymalloc()</tt>.  Your implementation of this function should initializeany data structures that your malloc will need to keep track of allocated and free blocks of memory.  It should also use <tt>sbrk</tt> to reserve an initial chunk of memory for your <tt>mymalloc</tt> implementation to use (this is your heap memory). Your implementation should mark this initial chunk as free for use by future calls to <tt>mymalloc</tt>.
    <li> Your implementation of <tt>mymalloc</tt> should allocate (at least) the requested number of bytes from the free space in your heap. For Step 1, mymalloc() can return NULL if the request cannot be allocated from the current free space.

    <li>You **must not** use <tt>sbrk</tt> as if it were <tt>malloc</tt>.  In other words, you should not be calling <tt>sbrk</tt> on every <tt>mymalloc</tt> call, unless large amounts of memory are requested on each call.  The minimum amount by which <tt>sbrk</tt> should increase the heap is one page, or 4096 bytes.
*   Memory addresses returned by <tt>mymalloc</tt> (and used internally) will be aligned on a 8-byte boundary.  (Every address returned by <tt>mymalloc</tt> can be evenly divided by 8.)
*   Note that you don't need a linked list to keep track of allocated blocks, but you do need to know where the free space begins, and you might as well implement the headers that will keep track of information.

### Step 2: <tt>mymalloc</tt> expanding available heap using <tt>sbrk</tt>(5%) 

Extend your implementation of <tt>mymalloc</tt> so that <tt>sbrk</tt> will be called to expand the heap if there is not enough space in the current heap to allocate the space asked for by <tt>mymalloc</tt>. When Step 2 is complete, <tt>mymalloc</tt> should not return NULL unless <tt>sbrk</tt> returns an error.

### Step 3: <tt>myfree</tt> basic(20%)

Implement a basic version of <tt>myfree</tt>.  You will want to maintain a list of free blocks, so that the list can be traversed to find a block of appropriate size. (This is where the headers from Step 1 come in.) This would be a good time to add the error checking. This is also a good time to think about using helper functions for the list operations.

### Step 4: <tt>mymalloc</tt> reuse of freed blocks(20%)

Implement a search or scan of the free list so that freed blocks may be reused.  You may use a first-fit or best-fit algorithm.

### Step 5: synchronization (10%)

Add the necessary synchronization to allow multiple threads to concurrently allocate and free memory.

### Step 6: coalescing (10%)

Add coalescing of adjacent free blocks. 

### Optimization (10%)

Once you have the rest of the implementation working, it is time to consider optimizing the algorithm.  

Before you start the optimization step, make a copy of your <tt>mymemory.c</tt> file and name it <tt>mymemory_opt.c</tt>.  Do your work for this step in this <tt>mymmemory_opt.c</tt> file.  In other words, all the functionality up to and including coalescing will be implemented in <tt>mymemory.c</tt>, additional optimization will be implemeted in <tt>mymemory_opt.c</tt>.

There are two aspects of optimization that may be in conflict.  The first and most important is speed.  The simple linked list algorithm with reallocation and coalescing can be improved to speed up the time it takes to find a free block. The second step is to consider how to reduce the space overhead required to maintain the allocation metadata and/or to keep the heap as small as possible.

In addition to submitting your code, include in your <tt>mymemory-opt.c</tt> a comment at the top of the file that describes the optimized algorithm you used in one or two paragraphs (no more than 250 words). Your description should include some justification (specific use cases or traces, for example) of the design decisions you made.

As an extra bonus, we will do a speed comparison of the mymemory-opt submissions and I (Karen) will take the winners for a beverage of their choice from a local coffee shop.

**Warning**: If you are testing your program with large amounts of memory, do not run your code for this exercise on <tt>wolf.cdf.utoronto.ca</tt> or another shared server. When you allocate a huge amount of memory, you could decrease performance for other users. You can login to any of the lab machines remotely.  They are named bXXXX-YY.cdf.toronto.edu where XXXX is the room number (e.g. 3175) and YY is the machine number starting from 01 up to the number of machines in the room.
Before running your code, you should use the <tt>w</tt> command to determine who is on the system and what the load on the system is. To be polite, don't slam a system that someone is using.

### Good Work Habits and Submission Checklist

Assignments that are not correctly submitted or do not compile will receive a grade of 0. Therefore, it is in your best interest to verify that your submission is complete, and ensure that your code always compiles.

While you are working on the assignment, compile your code frequently, and commit partial work to the repository after you get each step working. If you are working on your own machine, then after each step, ensure that your code works on CDF.

*   Step one should be downloading the starter code, checking out your repo, and committing the starter code to the repo.  You should do this immediately.  Run <tt>make</tt> so that you can verify that the starter code compiles.
*   At least one day before the assignment is due, make sure that _all_ files are added and committed to the repo.  You want to find out about any issues with your repo at least a full day before the deadline.
*   After you have committed everything to your repo, but before your submission can be considered complete:

        1.  create an empty temporary directory in your cdf account (not in a subdirectory of your repo)
    2.  check out a copy of your repository for this assignment
    3.  run <tt>make</tt> and ensure that you are able to build <tt>test_malloc</tt> without any errors or warnings (This is an excellent way to verify that all files have been committed to the repo.)
    4.  run a few tests to ensure that your code behaves as you expect
    5.  congratulate yourself and enjoy a well-earned break, knowing that your strategy and hard work will pay off

## Submission

 You will submit all the files required to build your program including a <tt>Makefile</tt> that will build a program called <tt>test_malloc</tt> without any errors or warnings.

    