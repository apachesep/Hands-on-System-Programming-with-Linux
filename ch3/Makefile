# Makefile
# This program is part of the source code released for the book
#  "Hands-On Linux System Programming"
#  (c) Kaiwan N Billimoria
#  Packt Publishers
#
# From: Ch 3
ALL := show_curbrk show_curbrk_dbg malloc_brk_test malloc_brk_test_dbg \
	membugs membugs_dbg membugs_dbg_asan membugs_dbg_ub 

CC=gcc
CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN=${CFLAGS_DBG} -fsanitize=address
CFLAGS_DBG_UB=${CFLAGS_DBG} -fsanitize=undefined

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../common.c ../common.h
	${CC} ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	${CC} ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

show_curbrk: common.o show_curbrk.o
	${CC} ${CFLAGS} -o $@ $^
show_curbrk_dbg.o: show_curbrk.c
	${CC} ${CFLAGS_DBG} -c show_curbrk.c -o show_curbrk_dbg.o
show_curbrk_dbg: show_curbrk_dbg.o common_dbg.o
	${CC} -o show_curbrk_dbg show_curbrk_dbg.o common_dbg.o

malloc_brk_test: malloc_brk_test.o common.o
	${CC} ${CFLAGS} -o $@ $^
malloc_brk_test_dbg.o: malloc_brk_test.c
	${CC} ${CFLAGS_DBG} -c malloc_brk_test.c -o malloc_brk_test_dbg.o
malloc_brk_test_dbg: malloc_brk_test_dbg.o common_dbg.o
	${CC} -o malloc_brk_test_dbg malloc_brk_test_dbg.o common_dbg.o

membugs: membugs.o common.o
	${CC} ${CFLAGS} -o $@ $^
membugs_dbg.o: membugs.c
	${CC} ${CFLAGS_DBG} -c membugs.c -o membugs_dbg.o
	${CC} ${CFLAGS_DBG_ASAN} -c membugs.c -o membugs_dbg_asan.o
	${CC} ${CFLAGS_DBG_UB} -c membugs.c -o membugs_dbg_ub.o
membugs_dbg: membugs_dbg.o common_dbg.o
	${CC} -o membugs_dbg membugs_dbg.o common_dbg.o
	${CC} ${CFLAGS_DBG_ASAN} -o membugs_dbg_asan membugs_dbg_asan.o common_dbg.o
	${CC} ${CFLAGS_DBG_UB} -o membugs_dbg_ub membugs_dbg_ub.o common_dbg.o

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* *.o *~
