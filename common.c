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
 *  This is the 'common' code that gets dynamically linked into
 *  all binary executables.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "common.h"

/*---------------- Globals, Macros ----------------------------*/

/*---------------- Typedef's, constants, etc ------------------*/

/*---------------- Functions ----------------------------------*/

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
		perror("perror says");

	free(err_str);
	if (!fatal)
		return 0;
	exit(fatal);
}
/* vi: ts=8 */
