/*
 * feature_test_macros.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 ****************************************************************
 * Brief Description:
 *
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "../common.h"

int main(int argc, char **argv)
{
	printf(
	"=========== SImple Feature Test Macros ===========\n"
	"_POSIX_C_SOURCE = %ld\n"
	,_POSIX_C_SOURCE
	);

#ifdef __USE_POSIX199309
	printf("__USE_POSIX199309 is defined\n");
#else
	printf("__USE_POSIX199309 is undefined\n");
#endif

	exit (EXIT_SUCCESS);
}

/* vi: ts=8 */
