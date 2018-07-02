# Makefile : for ch13
ALL :=  alarm1 alarm1_dbg \
	alarm2_rep alarm2_rep_dbg \
	intv_clksimple intv_clksimple_dbg

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall -UDEBUG
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

#--- Target :: alarm1
alarm1.o: alarm1.c
	${CC} ${CFLAGS} -c alarm1.c -o alarm1.o
alarm1: common.o alarm1.o
	${CC} -o alarm1 alarm1.o common.o ${LINKIN}

alarm1_dbg.o: alarm1.c
	${CC} ${CFLAGS_DBG} -c alarm1.c -o alarm1_dbg.o
alarm1_dbg: alarm1_dbg.o common_dbg.o
	${CC} -o alarm1_dbg alarm1_dbg.o common_dbg.o ${LINKIN}

#--- Target :: alarm2_rep
alarm2_rep.o: alarm2_rep.c
	${CC} ${CFLAGS} -c alarm2_rep.c -o alarm2_rep.o
alarm2_rep: common.o alarm2_rep.o
	${CC} -o alarm2_rep alarm2_rep.o common.o ${LINKIN}

alarm2_rep_dbg.o: alarm2_rep.c
	${CC} ${CFLAGS_DBG} -c alarm2_rep.c -o alarm2_rep_dbg.o
alarm2_rep_dbg: alarm2_rep_dbg.o common_dbg.o
	${CC} -o alarm2_rep_dbg alarm2_rep_dbg.o common_dbg.o ${LINKIN}

#--- Target :: intv_clksimple
intv_clksimple.o: intv_clksimple.c
	${CC} ${CFLAGS} -c intv_clksimple.c -o intv_clksimple.o
intv_clksimple: common.o intv_clksimple.o
	${CC} -o intv_clksimple intv_clksimple.o common.o ${LINKIN}

intv_clksimple_dbg.o: intv_clksimple.c
	${CC} ${CFLAGS_DBG} -c intv_clksimple.c -o intv_clksimple_dbg.o
intv_clksimple_dbg: intv_clksimple_dbg.o common_dbg.o
	${CC} -o intv_clksimple_dbg intv_clksimple_dbg.o common_dbg.o ${LINKIN}


# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
  rm -vf ${ALL} core* vgcore* *.o *~
