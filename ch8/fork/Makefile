# Makefile
#  ch8 / fork

ALL := fork1 fork2 fork3 fork4 fork5 \
	fork4_prnum

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN= -fsanitize=address
CFLAGS_DBG_UB= -fsanitize=undefined

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../../common.c ../../common.h
	${CC} ${CFLAGS} -c ../../common.c -o common.o
common_dbg.o: ../../common.c ../../common.h
	${CC} ${CFLAGS_DBG} -c ../../common.c -o common_dbg.o


fork1: common.o fork1.o
	${CC} ${CFLAGS} -o fork1 fork1.c common.o
fork2: common.o fork2.o
	${CC} ${CFLAGS} -o fork2 fork2.c common.o
fork3: common.o fork3.o
	${CC} ${CFLAGS} -o fork3 fork3.c common.o
fork4: common.o fork4.o
	${CC} ${CFLAGS} -o fork4 fork4.c common.o
fork4_prnum: common.o fork4_prnum.o
	${CC} ${CFLAGS} -o fork4_prnum fork4_prnum.c common.o
fork5: common.o fork5.o
	${CC} ${CFLAGS} -o fork5 fork5.c common.o


# indent- "beautifies" C code into the "Linux kernel style"\.
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
