# Makefile : ch12/sigwt
#
#  ASSUMPTIONS ::
#   1. the convenience files ../common.h and ../common.c
#      are present
#   2. the clang/LLVM compiler is installed.
#----------------------------------------------------------------------
## Pl check and keep or remove <foo>_dbg_[asan|ub|msan] targets
## as desired.
ALL :=  sigwt sigwt_dbg #sigwt_dbg_asan sigwt_dbg_ub sigwt_dbg_msan

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall -UDEBUG
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra -DDEBUG
CFLAGS_DBG_ASAN=${CFLAGS_DBG} -fsanitize=address
CFLAGS_DBG_MSAN=${CFLAGS_DBG} -fsanitize=memory
CFLAGS_DBG_UB=${CFLAGS_DBG} -fsanitize=undefined

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../../common.c ../../common.h
	${CC} ${CFLAGS} -c ../../common.c -o common.o
common_dbg.o: ../../common.c ../../common.h
	${CC} ${CFLAGS_DBG} -c ../../common.c -o common_dbg.o

#--- Sanitizers (use clang): common_dbg_*
common_dbg_asan.o: ../../common.c ../../common.h
	${CL} ${CFLAGS_DBG_ASAN} -c ../../common.c -o common_dbg_asan.o
common_dbg_ub.o: ../../common.c ../../common.h
	${CL} ${CFLAGS_DBG_UB} -c ../../common.c -o common_dbg_ub.o
common_dbg_msan.o: ../../common.c ../../common.h
	${CL} ${CFLAGS_DBG_MSAN} -c ../../common.c -o common_dbg_msan.o

sigwt.o: sigwt.c
	${CC} ${CFLAGS} -c sigwt.c -o sigwt.o
sigwt: common.o sigwt.o
	${CC} ${CFLAGS} -o sigwt sigwt.o common.o

sigwt_dbg.o: sigwt.c
	${CC} ${CFLAGS_DBG} -c sigwt.c -o sigwt_dbg.o
sigwt_dbg: sigwt_dbg.o common_dbg.o
	${CC} ${CFLAGS_DBG} -o sigwt_dbg sigwt_dbg.o common_dbg.o

#--- Sanitizers (use clang): <foo>_dbg_[asan|ub|msan]
sigwt_dbg_asan.o: sigwt.c
	${CL} ${CFLAGS_DBG_ASAN} -c sigwt.c -o sigwt_dbg_asan.o
sigwt_dbg_asan: sigwt_dbg_asan.o common_dbg_asan.o
	${CL} ${CFLAGS_DBG_ASAN} -o sigwt_dbg_asan sigwt_dbg_asan.o common_dbg_asan.o

sigwt_dbg_ub.o: sigwt.c
	${CL} ${CFLAGS_DBG_UB} -c sigwt.c -o sigwt_dbg_ub.o
sigwt_dbg_ub: sigwt_dbg_ub.o common_dbg_ub.o
	${CL} ${CFLAGS_DBG_UB} -o sigwt_dbg_ub sigwt_dbg_ub.o common_dbg_ub.o

sigwt_dbg_msan.o: sigwt.c
	${CL} ${CFLAGS_DBG_MSAN} -c sigwt.c -o sigwt_dbg_msan.o
sigwt_dbg_msan: sigwt_dbg_msan.o common_dbg_msan.o
	${CL} ${CFLAGS_DBG_MSAN} -o sigwt_dbg_msan sigwt_dbg_msan.o common_dbg_msan.o

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
