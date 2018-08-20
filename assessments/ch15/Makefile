# Makefile
#----------------------------------------------------------------------
#  ASSUMPTIONS ::
#   1. the convenience files ../common.h and ../common.c
#      are present
#   2. the clang/LLVM compiler is installed
#   3. the indent utility is installed
#
#   WARNING! Do NOT start a source filename with 'core' !
#       (will get Erased when 'make clean' is performed).
#----------------------------------------------------------------------
## Pl check and keep or remove <foo>_dbg_[asan|ub|msan] targets
## as desired.
ALL :=  see_tid see_tid_dbg \
	named_threads named_threads_dbg

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-O2 -Wall -UDEBUG
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra -DDEBUG
CFLAGS_DBG_ASAN=${CFLAGS_DBG} -fsanitize=address
CFLAGS_DBG_MSAN=${CFLAGS_DBG} -fsanitize=memory
CFLAGS_DBG_UB=${CFLAGS_DBG} -fsanitize=undefined

LINKIN=
   # set as required to libraries to link in; f.e.  -lrt

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../../common.c ../../common.h
	${CC} ${CFLAGS} -c ../../common.c -o common.o
common_dbg.o: ../../common.c ../../common.h
	${CC} ${CFLAGS_DBG} -c ../../common.c -o common_dbg.o

#--- Target :: see_tid
see_tid.o: see_tid.c
	${CC} ${CFLAGS} -c see_tid.c -o see_tid.o
see_tid: common.o see_tid.o
	${CC} -o see_tid see_tid.o common.o -lpthread

see_tid_dbg.o: see_tid.c
	${CC} ${CFLAGS_DBG} -c see_tid.c -o see_tid_dbg.o
see_tid_dbg: see_tid_dbg.o common_dbg.o
	${CC} -o see_tid_dbg see_tid_dbg.o common_dbg.o -lpthread

#--- Target :: named_threads
named_threads.o: named_threads.c
	${CC} ${CFLAGS} -c named_threads.c -o named_threads.o
named_threads: common.o named_threads.o
	${CC} -o named_threads named_threads.o common.o -lpthread

named_threads_dbg.o: named_threads.c
	${CC} ${CFLAGS_DBG} -c named_threads.c -o named_threads_dbg.o
named_threads_dbg: named_threads_dbg.o common_dbg.o
	${CC} -o named_threads_dbg named_threads_dbg.o common_dbg.o -lpthread


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
