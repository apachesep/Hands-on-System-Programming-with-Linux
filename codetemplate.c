/*
 * ch_:<name>.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  Ch 2 : Virtual Memory
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

/*---------------- Globals, Macros ----------------------------*/


/*---------------- Typedef's, constants, etc ------------------*/


/*---------------- Functions ----------------------------------*/


int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s \n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	exit (EXIT_SUCCESS);
}
/* vi: ts=8 */
