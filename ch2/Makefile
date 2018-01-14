# Makefile
# This program is part of the source code released for the book
#  "Linux System Programming"
#  (c) Kaiwan N Billimoria
#  Packt Publishers
#
# From: Ch 2
ALL := mem_app1buggy mem_app1buggy_dbg rlimits_show rlimits_show_dbg rlimit_primes rlimit_primes_dbg

CC=gcc
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS=-Wall

all: ${ALL}
CB_FILES := *.[ch]

mem_app1buggy: mem_app1buggy.c
	${CC} ${CFLAGS} mem_app1buggy.c -o mem_app1buggy
mem_app1buggy_dbg: mem_app1buggy.c
	${CC} ${CFLAGS_DBG} mem_app1buggy.c -o mem_app1buggy_dbg

rlimits_show: rlimits_show.c
	${CC} ${CFLAGS} rlimits_show.c -o rlimits_show
rlimits_show_dbg: rlimits_show.c
	${CC} ${CFLAGS_DBG} rlimits_show.c -o rlimits_show_dbg

rlimit_primes: rlimit_primes.c
	${CC} ${CFLAGS} rlimit_primes.c -o rlimit_primes
rlimit_primes_dbg: rlimit_primes.c
	${CC} ${CFLAGS_DBG} rlimit_primes.c -o rlimit_primes_dbg

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* *.o
