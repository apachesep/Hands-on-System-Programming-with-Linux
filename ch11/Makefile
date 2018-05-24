# Makefile
# ch11 : Signalling
ALL := sig1 sig2 zombies_clear_linux26 defer_or_not altstack \
	handle_segv sleeping_beauty rtsigs_waiter

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

defer_or_not_rtsigs: common.o defer_or_not_rtsigs.o
	${CC} ${CFLAGS} -o defer_or_not_rtsigs defer_or_not_rtsigs.c common.o

altstack: common.o altstack.o
	${CC} ${CFLAGS} -o altstack altstack.c common.o

handle_segv: common.o handle_segv.o
	${CC} ${CFLAGS} -o handle_segv handle_segv.c common.o
handle_segv_dbg.o: handle_segv.c
	${CC} ${CFLAGS_DBG} -c handle_segv.c -o handle_segv_dbg.o
handle_segv_dbg: handle_segv_dbg.o common_dbg.o
	${CC} -o handle_segv_dbg handle_segv_dbg.o common_dbg.o
	${CL} ${CFLAGS_DBG_ASAN} -o handle_segv_asan handle_segv_dbg.o common_dbg.o

sleeping_beauty: common.o sleeping_beauty.o
	${CC} ${CFLAGS} -o sleeping_beauty sleeping_beauty.c common.o

rtsigs_waiter: common.o rtsigs_waiter.o
	${CC} ${CFLAGS} -o rtsigs_waiter rtsigs_waiter.c common.o


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
