/*
 * ch8:fork3.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  Ch 8 : Process Execution and Creation
 ****************************************************************
 * Brief Description:
 * A very quick and simple demo of the fork(2) system call.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "../../common.h"

int main(int argc, char **argv)
{
	if (fork() == -1)
		FATAL("fork failed!\n");

	printf("PID %d: Hello, fork.\n", getpid());
	exit(EXIT_SUCCESS);
}

/* vi: ts=8 */
