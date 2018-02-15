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

#define NON_FATAL    0
int handle_err(int fatal, const char *fmt, ...);

#define WARN(warnmsg, args...) do {                   \
	handle_err(NON_FATAL, "!WARNING! %s:%s:%d: " warnmsg, \
	   __FILE__, __FUNCTION__, __LINE__, ##args); \
} while(0)
#define FATAL(errmsg, args...) do {                   \
	handle_err(EXIT_FAILURE, "FATAL:%s:%s:%d: " errmsg, \
	   __FILE__, __FUNCTION__, __LINE__, ##args); \
} while(0)

#endif
