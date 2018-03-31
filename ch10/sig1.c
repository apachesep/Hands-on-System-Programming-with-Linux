/*
 * ch_:sig1.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  Ch 10 : Signalling
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
	int i=1;

	while(1) {
		printf("Looping, iteration #%02d ...\n", i++);
		sleep(1);
	}
	
	exit (EXIT_SUCCESS);
}

/* vi: ts=8 */
