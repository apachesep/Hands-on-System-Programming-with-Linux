# Makefile
# ch10
ALL := sig1 sig2 zombies_clear_linux26 defer_or_not altstack

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN= -fsanitize=address
CFLAGS_DBG_MSAN= -fsanitize=memory -fPIE -pie
CFLAGS_DBG_UB= -fsanitize=undefined

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../common.c ../common.h
	${CC} ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	${CC} ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

sig1: common.o sig1.o
	${CC} ${CFLAGS} -o sig1 sig1.c common.o
sig2: common.o sig2.o
	${CC} ${CFLAGS} -o sig2 sig2.c common.o

zombies_clear_linux26: common.o zombies_clear_linux26.o
	${CC} ${CFLAGS} -o zombies_clear_linux26 zombies_clear_linux26.c common.o

defer_or_not: common.o defer_or_not.o
	${CC} ${CFLAGS} -o defer_or_not defer_or_not.c common.o

altstack: common.o altstack.o
	${CC} ${CFLAGS} -o altstack altstack.c common.o


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
