Exercise 11 - Virtual Addresses
Due: Friday, Feb 20 @ 10:00 p.m.

Introduction

The purpose of this exercise is to give your some exposure to memory access patterns, and some practice examing how a program uses memory.

Exercise files:

Makefile
heaploop.c
matmul.c
runit
refstring.py
You are given two simple programs: heaploop.c and matmul.c. The only purpose of these programs is so that we have something to trace. The provided Makefile will compile these two programs and make traces will call the shell script runit that will run each program using valgrind to produce a memory reference trace. The output of valgrind is filtered using a python program refstring.py to remove the valgrind comments, and the memory references that load the program and clean up after it has finished executing. This allows us to focus on the memory references that are part of the algorithm.

Your task is to read the programs to get a picture of how they are using memory, run the programs to produce the traces, and write a short program in the language of your choice to analyze the trace output.

The resulting trace files have the following format:

    0x7ff0008e8,S
    0x400590,I
    0x601020,L
    0x400596,I
    0x7ff0008e0,S
    0x4fdf720,M
Each comma-separated line begin with a memory address in hexadecimal, and the character in the second field determines the type of access: I - instruction, S - store, L - load, M - modify. S, L, and M accesses are all data accesses.

Your analysis program will translate each memory reference into a page number assuming pages are 4096 bytes. It will output a table of each unique instruction pages with a count of the number of accesses for each page, and a table of unique data pages with a count of the number of accesses for each page.

For example, the above snippet might produce the following:

    Instructions
    0x400,2
    
    Data:
    0x7ff000,2
    0x601,1
    0x4fdf,1
What to submit:

The program you wrote to produce the table
A text files called readme.txt containing the following information about each program:
The number of instruction pages (I)
The number of data pages (S, L, M)
Identify which pages are accessed the most and explain briefly which variable or code from the program might be stored in these pages.
Note: The intent is that you should be able to do this exercise in about an hour or so. You do not need to write more than a few sentences.

If you want to think about this topic further, I would encourage you to look at the memory reference trace more to see if you can spot patterns.

Marking Scheme:

submitted analysis program 25%
submitted accurate page counts 50%
explanation of the variables or code that is accessed most frequently 25%