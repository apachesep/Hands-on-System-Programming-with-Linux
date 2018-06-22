# Makefile
# This program is part of the source code released for the book
#  "Hands-On Linux System Programming"
#  (c) Kaiwan N Billimoria
#  Packt Publishers
#
# From: Ch 2
ALL :=  mem_app1buggy mem_app1buggy_dbg stacker stacker_dbg

CC=gcc
CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../common.c ../common.h
	gcc ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	gcc ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

mem_app1buggy: common.o mem_app1buggy.o
	gcc ${CFLAGS} -o mem_app1buggy mem_app1buggy.c common.o
mem_app1buggy_dbg.o: mem_app1buggy.c
	gcc ${CFLAGS_DBG} -c mem_app1buggy.c -o mem_app1buggy_dbg.o
mem_app1buggy_dbg: mem_app1buggy_dbg.o common_dbg.o
	gcc -o mem_app1buggy_dbg mem_app1buggy_dbg.o common_dbg.o

stacker: common.o stacker.o
	${CC} ${CFLAGS} -o stacker stacker.c common.o
stacker_dbg.o: stacker.c
	${CC} ${CFLAGS_DBG} -c stacker.c -o stacker_dbg.o
stacker_dbg: stacker_dbg.o common_dbg.o
	${CC} -o stacker_dbg stacker_dbg.o common_dbg.o

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
