# Makefile : ch15/
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
ALL :=  pthreads1 pthreads1_dbg \
	pthreads2 pthreads2_dbg \
	pthreads3 pthreads3_dbg \
	cr8_so_many_threads cr8_so_many_threads_dbg

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

common.o: ../common.c ../common.h
	${CC} ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	${CC} ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

 #--- Sanitizers (use clang): common_dbg_*
common_dbg_asan.o: ../common.c ../common.h
	${CL} ${CFLAGS_DBG_ASAN} -c ../common.c -o common_dbg_asan.o
common_dbg_ub.o: ../common.c ../common.h
	${CL} ${CFLAGS_DBG_UB} -c ../common.c -o common_dbg_ub.o
common_dbg_msan.o: ../common.c ../common.h
	${CL} ${CFLAGS_DBG_MSAN} -c ../common.c -o common_dbg_msan.o

#--- Target :: pthreads1
pthreads1.o: pthreads1.c
	${CC} ${CFLAGS} -c pthreads1.c -o pthreads1.o
pthreads1: common.o pthreads1.o
	${CC} -o pthreads1 pthreads1.o common.o -lpthread

pthreads1_dbg.o: pthreads1.c
	${CC} ${CFLAGS_DBG} -c pthreads1.c -o pthreads1_dbg.o
pthreads1_dbg: pthreads1_dbg.o common_dbg.o
	${CC} -o pthreads1_dbg pthreads1_dbg.o common_dbg.o -lpthread

 #--- Sanitizers for pthreads1 :: (use clang): <foo>_dbg_[asan|ub|msan]
pthreads1_dbg_asan.o: pthreads1.c
	${CL} ${CFLAGS_DBG_ASAN} -c pthreads1.c -o pthreads1_dbg_asan.o
pthreads1_dbg_asan: pthreads1_dbg_asan.o common_dbg_asan.o
	${CL} ${CFLAGS_DBG_ASAN} -o pthreads1_dbg_asan pthreads1_dbg_asan.o common_dbg_asan.o -lpthread

pthreads1_dbg_ub.o: pthreads1.c
	${CL} ${CFLAGS_DBG_UB} -c pthreads1.c -o pthreads1_dbg_ub.o
pthreads1_dbg_ub: pthreads1_dbg_ub.o common_dbg_ub.o
	${CL} ${CFLAGS_DBG_UB} -o pthreads1_dbg_ub pthreads1_dbg_ub.o common_dbg_ub.o -lpthread

pthreads1_dbg_msan.o: pthreads1.c
	${CL} ${CFLAGS_DBG_MSAN} -c pthreads1.c -o pthreads1_dbg_msan.o
pthreads1_dbg_msan: pthreads1_dbg_msan.o common_dbg_msan.o
	${CL} ${CFLAGS_DBG_MSAN} -o pthreads1_dbg_msan pthreads1_dbg_msan.o common_dbg_msan.o -lpthread

#--- Target :: pthreads2
pthreads2.o: pthreads2.c
	${CC} ${CFLAGS} -c pthreads2.c -o pthreads2.o
pthreads2: common.o pthreads2.o
	${CC} -o pthreads2 pthreads2.o common.o -lpthread

pthreads2_dbg.o: pthreads2.c
	${CC} ${CFLAGS_DBG} -c pthreads2.c -o pthreads2_dbg.o
pthreads2_dbg: pthreads2_dbg.o common_dbg.o
	${CC} -o pthreads2_dbg pthreads2_dbg.o common_dbg.o -lpthread

#--- Target :: pthreads3
pthreads3.o: pthreads3.c
	${CC} ${CFLAGS} -c pthreads3.c -o pthreads3.o
pthreads3: common.o pthreads3.o
	${CC} -o pthreads3 pthreads3.o common.o -lpthread

pthreads3_dbg.o: pthreads3.c
	${CC} ${CFLAGS_DBG} -c pthreads3.c -o pthreads3_dbg.o
pthreads3_dbg: pthreads3_dbg.o common_dbg.o
	${CC} -o pthreads3_dbg pthreads3_dbg.o common_dbg.o -lpthread

#--- Target :: cr8_so_many_threads
cr8_so_many_threads.o: cr8_so_many_threads.c
	${CC} ${CFLAGS} -c cr8_so_many_threads.c -o cr8_so_many_threads.o
cr8_so_many_threads: common.o cr8_so_many_threads.o
	${CC} -o cr8_so_many_threads cr8_so_many_threads.o common.o -lpthread

cr8_so_many_threads_dbg.o: cr8_so_many_threads.c
	${CC} ${CFLAGS_DBG} -c cr8_so_many_threads.c -o cr8_so_many_threads_dbg.o
cr8_so_many_threads_dbg: cr8_so_many_threads_dbg.o common_dbg.o
	${CC} -o cr8_so_many_threads_dbg cr8_so_many_threads_dbg.o common_dbg.o -lpthread


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
