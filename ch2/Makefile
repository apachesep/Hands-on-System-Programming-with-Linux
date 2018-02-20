# Makefile
# This program is part of the source code released for the book
#  "Hands-On Linux System Programming"
#  (c) Kaiwan N Billimoria
#  Packt Publishers
#
# From: Ch 2
ALL :=  mem_app1buggy mem_app1buggy_dbg

CC=gcc
CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../common.c ../common.h
	gcc -Wall -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	gcc -g -ggdb -gdwarf-4 -O0 -Wall -Wextra -c ../common.c -o common_dbg.o

mem_app1buggy: common.o mem_app1buggy.o
	gcc -Wall -o mem_app1buggy mem_app1buggy.c common.o
mem_app1buggy_dbg.o: mem_app1buggy.c
	gcc -g -ggdb -gdwarf-4 -O0 -Wall -Wextra -c mem_app1buggy.c -o mem_app1buggy_dbg.o
mem_app1buggy_dbg: mem_app1buggy_dbg.o common_dbg.o
	gcc -o mem_app1buggy_dbg mem_app1buggy_dbg.o common_dbg.o

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
