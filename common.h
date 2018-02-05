/*
 * common.h
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
#ifndef __HOLSP_COMMON_H__
#define __HOLSP_COMMON_H__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

int handle_err(int fatal, const char *fmt, ...);

#endif
