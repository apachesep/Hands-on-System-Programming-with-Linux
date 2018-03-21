/*
 * ch8:predcs_name.c
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
 * A demo of using the execl(3) API; this is the first of two
 * programs. 
 * In this program, we pass a name (provided by the user)
 * to the second program - the successor - by passing it as the
 * 'argv[0]' value to the successor. However, we find that this
 * does not actually change the name of the successor process; the
 * right way to do so is to use the prctl(2) with the PR_SET_NAME
 * parameter, (or via the pthread_setname_np(3) Pthreads API) within
 * the successor itself.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "../common.h"

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "Usage: %s {successor_name} [do-it-right]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	/* Have us, the predecessor, exec the successor! 
	 * Notice how we "cleverly" pass argv[1] as the successor's
	 * argv[0] and argv[1]; hence, the thinking is, it will receive
	 * this name as "it's" name (here, we're proved wrong though)
	 * and it's first parameter (that works). 
	 * So, to right the wrong, lets use this logic:
	 * if the user passes us 2 params, we'll pass them along to
	 * the successor; if the successor detects 3 params, it
	 * uses the 'correct' approach to naming. See the successor
	 * code for more...
	 */
	if (argc == 2) { /* the wrong way */
		if (execl("./successor_setnm", argv[1], argv[1],
					(char *)0) == -1)
			FATAL("execl \"successor_setnm\" 1 failed\n");
	} else if (argc == 3) { /* the right way */
		if (execl("./successor_setnm", argv[2], argv[1],
					argv[2], (char *)0) == -1)
			FATAL("execl \"successor_setnm\" 2 failed\n");
	}
	exit (EXIT_SUCCESS);
}

/* vi: ts=8 */
