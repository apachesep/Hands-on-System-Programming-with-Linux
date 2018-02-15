/*
 * ch_:memprot.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  Ch  : Dynamic Memory
 ****************************************************************
 * Brief Description:
 *
 *
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>       /* for mprotect(2) */
#include "../common.h"

/*---------------- Globals, Macros ----------------------------*/
int gPgsz;

/*---------------- Typedef's, constants, etc ------------------*/
typedef unsigned long long u64;

/*---------------- Functions ----------------------------------*/
static void test_mem(void *ptr, int write_on_ro_mem)
{
	int byte = random() % gPgsz;
	char *start_off = (char *)ptr + byte;

	printf("\n%s():\n", __FUNCTION__);

	/* Page 0 : rw [default] mem protection */
	*start_off = 'a';
	printf("page 0 @ 0x%016llx: read: 0x%x\n", (u64)start_off, *start_off);

	/* Page 1 : ro mem protection */
	start_off = (char *)ptr + gPgsz + byte;
	printf("page 1 @ 0x%016llx: read: 0x%x\n", (u64)start_off, *start_off);
	if (write_on_ro_mem == 1) {
		printf("page 1 @ 0x%016llx: attempting write now ...\n", (u64)start_off);
		*start_off = 'a'; /* should segfault! */
	}

	/* Page 2 : mprotect(PROT_WRITE|PROT_EXEC) fails, so no point testing it */

	/* Page 3 : 'NONE' mem protection */
	start_off = (char *)ptr + 3*gPgsz + byte;
	printf("page 3 @ 0x%016llx: attempting read now ...\n", (u64)start_off);
	printf(" read: 0x%x\n", *start_off); /* should segfault! */
	*start_off = 'a'; 
}

static void protect_mem(void *ptr)
{
	int i;
	u64 start_off=0;
	char str_prots[][128] = {"PROT_READ|PROT_WRITE", "PROT_READ",
				"PROT_READ|PROT_WRITE|PROT_EXEC", "PROT_NONE"};
	int prots[4] = {PROT_READ|PROT_WRITE, PROT_READ,
			PROT_READ|PROT_WRITE|PROT_EXEC, PROT_NONE};

	printf("%s():\n", __FUNCTION__);
	for (i=0; i<4; i++) {
		start_off = (u64)ptr+(i*gPgsz);
		printf("page %d: protections: %20s: range [0x%016llx, 0x%016llx]\n",
			i, str_prots[i], start_off, start_off+gPgsz-1);

		if (mprotect((void *)start_off, gPgsz, prots[i]) == -1)
			WARN("mprotect(%s) failed\n", str_prots[i]);
	}
}

int main(int argc, char **argv)
{
	void *ptr = NULL;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s test-write-to-ro-mem [0|1]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	gPgsz = getpagesize();

	/* POSIX wants page-aligned memory for mprotect(2) */
	posix_memalign(&ptr, gPgsz, 4*gPgsz);
	if (!ptr)
		FATAL("posix_memalign(for %zu bytes) failed\n", 4*gPgsz);

	protect_mem(ptr);
	test_mem(ptr, atoi(argv[1]));
	
	free(ptr);
	exit (EXIT_SUCCESS);
}

/* vi: ts=8 */
