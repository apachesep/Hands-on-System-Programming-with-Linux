/*
 * assesments_ch5:uar.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 ****************************************************************
 * Brief Description:
 * UAR: Use After Return
 * and memory leak bugs.
 *
 * 1. FIRST of all, recent compilers detect one of the bugs (the UAR):
$ gcc uar.c -o uar
uar.c: In function ‘bar’:
uar.c:33:8: warning: function returns address of local variable [-Wreturn-local-addr]
  return(theanswer);
        ^
 * 
 * 2. A test run:
$ ./uar 
1. the ans = (null)
2. the ans = THE ANSWER IS 42!
$ 

We can see the UAR bug clearly.
But we CANNOT 'see' the memory leak!

$ valgrind ./uar 
==3884== Memcheck, a memory error detector
==3884== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3884== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3884== Command: ./uar
==3884== 
1. the ans = (null)
2. the ans = THE ANSWER IS 42!
==3884== 
==3884== HEAP SUMMARY:
==3884==     in use at exit: 128 bytes in 1 blocks
==3884==   total heap usage: 2 allocs, 1 frees, 1,152 bytes allocated
==3884== 
==3884== LEAK SUMMARY:
==3884==    definitely lost: 128 bytes in 1 blocks
[...]
$ 

With valgrind it's revealed of course..
(Also try it with ASAN).
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "../../common.h"

static char * bar2(void)
{
	char *theanswer;
	theanswer = malloc(128);
	strncpy(theanswer, "THE ANSWER IS 42!", 127);
	return(theanswer);
}
static char * bar(void)
{
	char theanswer[128];
	strncpy(theanswer, "THE ANSWER IS 42!", 127);
	return(theanswer);
}
static void foo(void)
{
	printf("1. the ans = %s\n", bar());
	printf("2. the ans = %s\n", bar2());
}

int main(int argc, char **argv)
{
	int opt=0, cond=0;

	foo();
	exit (EXIT_SUCCESS);
}
/* vi: ts=8 */
