# Makefile, ch 6
CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN= -fsanitize=address
CFLAGS_DBG_UB= -fsanitize=undefined

ALL := query_creds query_creds_dbg \
	savedset_demo savedset_demo_dbg

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../common.c ../common.h
	${CC} ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	${CC} ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

query_creds: common.o query_creds.o
	${CC} ${CFLAGS} -o query_creds query_creds.c common.o
query_creds_dbg.o: query_creds.c
	${CC} ${CFLAGS_DBG} -c query_creds.c -o query_creds_dbg.o
query_creds_dbg: query_creds_dbg.o common_dbg.o
	${CC} -o query_creds_dbg query_creds_dbg.o common_dbg.o

savedset_demo: common.o savedset_demo.o
	${CC} ${CFLAGS} -o savedset_demo savedset_demo.c common.o
savedset_demo_dbg.o: savedset_demo.c
	${CC} ${CFLAGS_DBG} -c savedset_demo.c -o savedset_demo_dbg.o
savedset_demo_dbg: savedset_demo_dbg.o common_dbg.o
	${CC} -o savedset_demo_dbg savedset_demo_dbg.o common_dbg.o

# indent- "beautifies" C code into the "Linux kernel style"\.
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
