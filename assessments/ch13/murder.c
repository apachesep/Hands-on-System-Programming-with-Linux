/*
 * Assesment Solution
 * ch12:murder.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  Ch 12 : Signalling 2
 ****************************************************************
 * Question/Exercise:
 * 2. Write a program 'murder' (quite dramatic, no) whose job is to loop
 * over all processes alive and try and abruptly kill them via SIGKILL.
 * Also, run it both with and without root privileges (PLEASE, save any
 * work before running, and, even better, use a "test" virtual machine).
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include "../../common.h"

static int verbose=1;

static unsigned long int get_pid_max(void)
{
	FILE *fp;
	char res[16];

	fp = popen("cat /proc/sys/kernel/pid_max", "r");
	if (!fp) {
		pclose(fp);
		return 0;
	}
	if ((fgets(res, 16, fp) == NULL)) {
		pclose(fp);
		return 0;
	}
	pclose(fp);

	return strtoul(res, 0, 10);
}

int main(int argc, char **argv)
{
	pid_t i;
	unsigned long int pid_max = get_pid_max();

	if (!pid_max)
		pid_max = 32768; // :-)

	printf("!WARNING! This naughty process named %s intends to\n"
		"KILL (that too, SIGKILL) off processes in PID range {1, %lu} !!\n\n"
		"Press [Enter] to continue, ^C to abort now ...\n",
			argv[0], pid_max);
	fgetc(stdin);

	if (verbose)
		system("ps -e");

	printf("Fair Warning given, proceeding to murder ...\n");
	for (i=1; i<pid_max; i++) {
		if (kill (i, 0) < 0)
			continue;
		if (verbose)
			printf(" SIGKILL -> %6d : ", i);
		if (kill (i, SIGKILL) < 0)
			printf(" [FAILED]\n");
		else {
			if (verbose)
				printf(" [OK]\n");
		}
	}
	
	exit(EXIT_SUCCESS);
}
/* vi: ts=8 */
