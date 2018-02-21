/*
 * ch4 assessments:memprot.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From: Ch 4: Dynamic Memory Allocation
 ****************************************************************
 * ASSESSMENT Qs:
 *
 * Allocate 2 pages of page-aligned memory. 
 * Write test cases to set memory protection as:
 *  first page  to r-x 
 *  second page to r--
 * What happens?
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>       /* for mprotect(2) */

int gPgsz;

int main(int argc, char **argv)
{
	void *ptr = NULL;

	gPgsz = getpagesize();

	/* POSIX wants page-aligned memory for mprotect(2) */
	posix_memalign(&ptr, gPgsz, 2*gPgsz);
	if (!ptr) {
		printf("posix_memalign(for %zu bytes) failed\n", 4*gPgsz);
		exit(1);
	}

	//--- Test case 1: set page 0 to [r-x]
	printf("Attempting to set memory protections of %p to [r-x]...\n", ptr);
	if (mprotect((void *)ptr, gPgsz, PROT_READ|PROT_EXEC) == -1)
		printf(" *** mprotect(r-x) failed\n");
	else
		printf(" [r-x] successful\n");
	/* Find that the above test case fails! Why?
	 * It's really to do with the kernel security modules disabling
	 * it. On Fedora, it's SELinux, on Ubuntu it's usually AppArmor
	 * responsible. So, either disable the kernel LSM's or run on a 
	 * system with no kernel security modules installed.
	 * It should then work.
	 */
	
	//--- Test case 2: set page 1 to [r--]
	printf("Attempting to set memory protections of %p to [r--]...\n", ptr+gPgsz);
	if (mprotect((void *)ptr+gPgsz, gPgsz, PROT_READ) == -1)
		printf(" *** mprotect(r--) failed\n");
	else
		printf(" [r--] successful\n");
	// Succeeds!
	
	free(ptr);
	exit (EXIT_SUCCESS);
}
/* vi: ts=8 */
