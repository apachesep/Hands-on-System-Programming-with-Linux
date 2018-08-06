# Makefile : ch14
#----------------------------------------------------------------------
## Pl check and keep or remove <foo>_dbg_[asan|ub|msan] targets
## as desired.
ALL :=  streamio1 streamio1_dbg #streamio1_dbg_asan streamio1_dbg_ub streamio1_dbg_msan

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

#--- Target :: streamio1
streamio1.o: streamio1.c
	${CC} ${CFLAGS} -c streamio1.c -o streamio1.o
streamio1: common.o streamio1.o
	${CC} -o streamio1 streamio1.o common.o ${LINKIN}

streamio1_dbg.o: streamio1.c
	${CC} ${CFLAGS_DBG} -c streamio1.c -o streamio1_dbg.o
streamio1_dbg: streamio1_dbg.o common_dbg.o
	${CC} -o streamio1_dbg streamio1_dbg.o common_dbg.o ${LINKIN}

 #--- Sanitizers for streamio1 :: (use clang): <foo>_dbg_[asan|ub|msan]
streamio1_dbg_asan.o: streamio1.c
	${CL} ${CFLAGS_DBG_ASAN} -c streamio1.c -o streamio1_dbg_asan.o
streamio1_dbg_asan: streamio1_dbg_asan.o common_dbg_asan.o
	${CL} ${CFLAGS_DBG_ASAN} -o streamio1_dbg_asan streamio1_dbg_asan.o common_dbg_asan.o ${LINKIN}

streamio1_dbg_ub.o: streamio1.c
	${CL} ${CFLAGS_DBG_UB} -c streamio1.c -o streamio1_dbg_ub.o
streamio1_dbg_ub: streamio1_dbg_ub.o common_dbg_ub.o
	${CL} ${CFLAGS_DBG_UB} -o streamio1_dbg_ub streamio1_dbg_ub.o common_dbg_ub.o ${LINKIN}

streamio1_dbg_msan.o: streamio1.c
	${CL} ${CFLAGS_DBG_MSAN} -c streamio1.c -o streamio1_dbg_msan.o
streamio1_dbg_msan: streamio1_dbg_msan.o common_dbg_msan.o
	${CL} ${CFLAGS_DBG_MSAN} -o streamio1_dbg_msan streamio1_dbg_msan.o common_dbg_msan.o ${LINKIN}


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
