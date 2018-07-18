/*
 * common.c
 * 
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  'Common' code.
 ****************************************************************
 * Brief Description:
 * This is the 'common' code that gets compiled into all binary
 * executables.
 */
#define _GNU_SOURCE
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*---------------- Globals, Macros ----------------------------*/

/*---------------- Typedef's, constants, etc ------------------*/

/*---------------- Functions ----------------------------------*/

/*
 * Signaling: Prints (to stdout) all signal integer values that are
 * currently in the Blocked (masked) state.
 */
void show_blocked_signals(void)
{
	sigset_t oldset;
	int i, none=1;

	/* sigprocmask: 
	 * int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
	 * if 'set' is NULL, the 'how' is ignored, but the
	 * 'oldset' sigmask value is populated; thus we can query the
	 * signal mask without altering it.
	 */
	sigemptyset(&oldset);
	if (sigprocmask(SIG_UNBLOCK, 0, &oldset) < 0)
		FATAL("sigprocmask -query- failed\n");
	printf("[SigBlk: ");
	for (i=1; i<=64; i++) {
		if (sigismember(&oldset, i)) {
			none=0;
			printf("%d ", i);
		}
	}
	printf("%s\n", none ? "-none-]" : "]");
	fflush(stdout);
}

int handle_err(int fatal, const char *fmt, ...)
{
#define ERRSTRMAX 512
	char *err_str;
	va_list argp;

	err_str = malloc(ERRSTRMAX);
	if (err_str == NULL)
		return -1;

	va_start(argp, fmt);
	vsnprintf(err_str, ERRSTRMAX-1, fmt, argp);
	va_end(argp);

	fprintf(stderr, "%s", err_str);
	if (errno)
		perror("kernel says");

	free(err_str);
	if (!fatal)
		return 0;
	exit(fatal);
}
/* vi: ts=8 */
