#!/bin/bash
# run_fork_r6_of

rm -f fork_r6_of
make fork_r6_of_dbg || exit 1
valgrind ./fork_r6_of_dbg tst
ls -l tst
echo "Examine the file 'tst'"
