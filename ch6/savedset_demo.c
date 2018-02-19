/*
 * ch_:savedset_demo.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  Ch 6 : Process Credentials
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
#define SHOW_CREDS() do {		\
  printf("RUID=%d EUID=%d\n"	\
         "RGID=%d EGID=%d\n",	\
		getuid(), geteuid(),    \
		getgid(), getegid());   \
} while (0)

/*---------------- Typedef's, constants, etc ------------------*/


/*---------------- Functions ----------------------------------*/

int main(int argc, char **argv)
{
	uid_t savedsetuid;

	printf("1. At Startup:\n");
	SHOW_CREDS();
	if (0 != geteuid())
		FATAL("Not a setuid-root executable,"
			" aborting now ...\n"
			"[TIP: do: sudo chown root %s ;"
			" sudo chmod u+s %s\n"
			" and rerun].\n"
			, argv[0], argv[0], argv[0]);
	printf(" Ok, we're effectively running as root! (EUID==0)\n");

	/* Save the EUID, in effect the "saved set UID", so that
	 * we can switch back anf forth
	 */
	savedsetuid = geteuid();

	printf("2. Becoming my original self!\n");
	if (seteuid(getuid()) == -1)
		FATAL("setuid() failed!\n");
	SHOW_CREDS();

	printf("3. Switching back to privileged state now...\n");
	if (seteuid(savedsetuid) == -1)
		FATAL("seteuid() failed!\n");
	SHOW_CREDS();

	exit (EXIT_SUCCESS);
}

/* vi: ts=8 */
