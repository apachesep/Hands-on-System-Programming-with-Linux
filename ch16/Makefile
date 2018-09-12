# Makefile : for ch16
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
ALL :=  mutex1 mutex1_dbg \
	bankacc bankacc_dbg \
	facto facto_dbg

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-O2 -Wall -UDEBUG
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra -DDEBUG
CFLAGS_DBG_ASAN=${CFLAGS_DBG} -fsanitize=address
CFLAGS_DBG_MSAN=${CFLAGS_DBG} -fsanitize=memory
CFLAGS_DBG_UB=${CFLAGS_DBG} -fsanitize=undefined

# user will need to explicitly set libraries to link in as required; f.e. -lrt

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

#--- Target :: mutex1
mutex1.o: mutex1.c
	${CC} ${CFLAGS} -c mutex1.c -o mutex1.o
mutex1: common.o mutex1.o
	${CC} -o mutex1 mutex1.o common.o -lpthread

mutex1_dbg.o: mutex1.c
	${CC} ${CFLAGS_DBG} -c mutex1.c -o mutex1_dbg.o
mutex1_dbg: mutex1_dbg.o common_dbg.o
	${CC} -o mutex1_dbg mutex1_dbg.o common_dbg.o -lpthread

#--- Target :: bankacc
bankacc.o: bankacc.c
	${CC} ${CFLAGS} -c bankacc.c -o bankacc.o
bankacc: common.o bankacc.o
	${CC} -o bankacc bankacc.o common.o -lpthread

bankacc_dbg.o: bankacc.c
	${CC} ${CFLAGS_DBG} -c bankacc.c -o bankacc_dbg.o
bankacc_dbg: bankacc_dbg.o common_dbg.o
	${CC} -o bankacc_dbg bankacc_dbg.o common_dbg.o -lpthread

 #--- Sanitizers for bankacc :: (use clang): <foo>_dbg_[asan|ub|msan]
bankacc_dbg_asan.o: bankacc.c
	${CL} ${CFLAGS_DBG_ASAN} -c bankacc.c -o bankacc_dbg_asan.o
bankacc_dbg_asan: bankacc_dbg_asan.o common_dbg_asan.o
	${CL} ${CFLAGS_DBG_ASAN} -o bankacc_dbg_asan bankacc_dbg_asan.o common_dbg_asan.o -lpthread

bankacc_dbg_ub.o: bankacc.c
	${CL} ${CFLAGS_DBG_UB} -c bankacc.c -o bankacc_dbg_ub.o
bankacc_dbg_ub: bankacc_dbg_ub.o common_dbg_ub.o
	${CL} ${CFLAGS_DBG_UB} -o bankacc_dbg_ub bankacc_dbg_ub.o common_dbg_ub.o -lpthread

bankacc_dbg_msan.o: bankacc.c
	${CL} ${CFLAGS_DBG_MSAN} -c bankacc.c -o bankacc_dbg_msan.o
bankacc_dbg_msan: bankacc_dbg_msan.o common_dbg_msan.o
	${CL} ${CFLAGS_DBG_MSAN} -o bankacc_dbg_msan bankacc_dbg_msan.o common_dbg_msan.o -lpthread

#--- Target :: facto
facto.o: facto.c
	${CC} ${CFLAGS} -c facto.c -o facto.o
facto: common.o facto.o
	${CC} -o facto facto.o common.o -lpthread

facto_dbg.o: facto.c
	${CC} ${CFLAGS_DBG} -c facto.c -o facto_dbg.o
facto_dbg: facto_dbg.o common_dbg.o
	${CC} -o facto_dbg facto_dbg.o common_dbg.o -lpthread


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~
