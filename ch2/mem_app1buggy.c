/*
 * ch2:mem_app1buggy.c
 *
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Linux System Programming"
 *  (c) Kaiwan N Billimoria
 *  Packt Publishers
 *
 * From:
 *  Ch 2 : Virtual Memory
 ****************************************************************
 * Brief Description:
 *
 * A simple demo to show that on Linux - a full-fledged Virtual
 * Memory enabled OS - even a buggy app will _NOT_ cause system
 * failure; rather, the buggy process will be killed by the kernel!
 * OTOH, if we had run this or a similar program in a flat purely 
 * physical address space based OS, this seemingly trivial bug can 
 * wreak havoc, bringing the entire system down.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../common.h"

int main(int argc, char **argv)
{
	void *ptr = NULL;
	void *dest, *src = "abcdef0123456789";
	void *arbit_addr = (void *)0xffffffffff601000;
	int n = strlen(src);

	ptr = malloc(256 * 1024);
	if (!ptr)
		handle_err(EXIT_FAILURE, "%s:%s:%d: malloc failed\n",
				__FILE__, __FUNCTION__, __LINE__);

	if (argc == 1)
		dest = ptr;	/* correct */
	else
		dest = arbit_addr;	/* bug! */
	memcpy(dest, src, n);

	free(ptr);
	exit(0);
}
