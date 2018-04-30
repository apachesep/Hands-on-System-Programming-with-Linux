# Makefile

ALL := uar uar_dbg uar_asan uar_msan uar_ub   

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN= -fsanitize=address
CFLAGS_DBG_UB= -fsanitize=undefined
CFLAGS_DBG_MSAN= -fsanitize=memory -fPIE -pie

all: ${ALL}
CB_FILES := *.[ch]


common.o: ../../common.c ../../common.h
	${CC} ${CFLAGS} -c ../../common.c -o common.o
common_dbg.o: ../../common.c ../../common.h
	${CC} ${CFLAGS_DBG} -c ../../common.c -o common_dbg.o


uar: common.o uar.o
	${CC} ${CFLAGS} -o uar uar.c common.o
uar_dbg.o: uar.c
	${CC} ${CFLAGS_DBG} -c uar.c -o uar_dbg.o
uar_dbg: uar_dbg.o common_dbg.o
	${CC} -o uar_dbg uar_dbg.o common_dbg.o
	${CL} ${CFLAGS_DBG_ASAN} -o uar_asan uar_dbg.o common_dbg.o
	${CL} ${CFLAGS_DBG_UB} -o uar_ub uar_dbg.o common_dbg.o
	${CL} ${CFLAGS_DBG_MSAN} -o uar_msan uar_dbg.o common_dbg.o

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
