#!/bin/bash
# run_fork_r6_of.sh : simple wrapper over fork_r6_of
FILE=tst
rm -f fork_r6_of
make fork_r6_of_dbg || exit 1
./fork_r6_of_dbg ${FILE}
# valgrind ./fork_r6_of_dbg tst
#   -to check with valgrind
ls -l ${FILE}
echo "Examine the file '${FILE}'"
