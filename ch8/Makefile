# Makefile
# This program is part of the source code released for the book
#  "Hands-On Linux System Programming"
#  (c) Kaiwan N Billimoria
#  Packt Publishers
#
# From: Ch 8
ALL :=  execl_eg execl_eg_dbg execl_eg_asan execl_eg_msan execl_eg_ub

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN=${CFLAGS_DBG} -fsanitize=address
CFLAGS_DBG_UB=${CFLAGS_DBG} -fsanitize=undefined

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../common.c ../common.h
	${CC} ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	${CC} ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

execl_eg: common.o execl_eg.o
	${CC} ${CFLAGS} -o execl_eg execl_eg.c common.o
execl_eg_dbg.o: execl_eg.c
	${CC} ${CFLAGS_DBG} -c execl_eg.c -o execl_eg_dbg.o
execl_eg_dbg: execl_eg_dbg.o common_dbg.o
	${CL} -o execl_eg_dbg execl_eg_dbg.o common_dbg.o
	${CL} ${CFLAGS_DBG_ASAN} -o execl_eg_asan execl_eg_dbg.o common_dbg.o
	${CL} ${CFLAGS_DBG_UB} -o execl_eg_ub execl_eg_dbg.o common_dbg.o
	${CL} ${CFLAGS_DBG_MSAN} -o execl_eg_msan execl_eg_dbg.o common_dbg.o


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
