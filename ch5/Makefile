# Makefile
# This program is part of the source code released for the book
#  "Hands-On Linux System Programming"
#  (c) Kaiwan N Billimoria
#  Packt Publishers
#
# From: Ch 5
ALL :=  membugs membugs_dbg membugs_dbg_asan membugs_dbg_ub membugs_dbg_msan

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN=${CFLAGS_DBG} -fsanitize=address
CFLAGS_DBG_MSAN=${CFLAGS_DBG} -fsanitize=memory
CFLAGS_DBG_UB=${CFLAGS_DBG} -fsanitize=undefined

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

membugs.o: membugs.c
	${CC} ${CFLAGS} -c membugs.c -o membugs.o
membugs: common.o membugs.o
	${CC} ${CFLAGS} -o membugs membugs.o common.o

membugs_dbg.o: membugs.c
	${CC} ${CFLAGS_DBG} -c membugs.c -o membugs_dbg.o
	${CL} ${CFLAGS_DBG_ASAN} -c membugs.c -o membugs_dbg_asan.o
	${CL} ${CFLAGS_DBG_UB} -c membugs.c -o membugs_dbg_ub.o
	${CL} ${CFLAGS_DBG_MSAN} -c membugs.c -o membugs_dbg_msan.o

membugs_dbg: membugs_dbg.o common_dbg.o
	${CC} ${CFLAGS_DBG} -o membugs_dbg membugs_dbg.o common_dbg.o

#--- Sanitizers (use clang): <foo>_dbg_[asan|ub|msan]
membugs_dbg_asan.o: common_dbg_asan.o
	${CL} ${CFLAGS_DBG_ASAN} -c membugs.c -o membugs_dbg_asan.o common_dbg_asan.o
membugs_dbg_asan: membugs_dbg_asan.o common_dbg_asan.o
	${CL} ${CFLAGS_DBG_ASAN} -o membugs_dbg_asan membugs_dbg_asan.o common_dbg_asan.o

membugs_dbg_ub.o: common_dbg_ub.o
	${CL} ${CFLAGS_DBG_UB} -c membugs.c -o membugs_dbg_ub.o common_dbg_ub.o
membugs_dbg_ub: membugs_dbg_ub.o common_dbg_ub.o
	${CL} ${CFLAGS_DBG_UB} -o membugs_dbg_ub membugs_dbg_ub.o common_dbg_ub.o

membugs_dbg_msan.o: common_dbg_msan.o
	${CL} ${CFLAGS_DBG_MSAN} -c membugs.c -o membugs_dbg_msan.o common_dbg_msan.o
membugs_dbg_msan: membugs_dbg_msan.o common_dbg_msan.o
	${CL} ${CFLAGS_DBG_MSAN} -o membugs_dbg_msan membugs_dbg_msan.o common_dbg_msan.o

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
