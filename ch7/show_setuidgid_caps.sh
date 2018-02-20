#!/bin/bash
# ch7:show_setuidgid_caps.sh
# 
#***************************************************************
# This program is part of the source code released for the book
#  "Hands-on System Programming with Linux"
#  (c) Author: Kaiwan N Billimoria
#  Publisher:  Packt
#
# From:
#  Ch 7 : Process Credentials
#****************************************************************
# Brief Description:
# Based on user choice, this bash script scans the system for all
# installed :
# 1. traditional setuid-root and setgid programs
# 2. modern POSIX capabilities-embedded programs.
name=$(basename $0)
SEP="------------------------------------------------------------------"
declare -a gDirArr=('/bin' '/usr/bin' '/sbin' '/usr/sbin' '/usr/local/bin' '/usr/local/sbin');

########### Functions follow #######################

scanforcaps()
{
[ ! -d $1 ] && return 1
for fname in /$1/*
do
  getcap ${fname}
done
}

show_files_with_caps()
{
 echo "Scanning various folders for binaries with (modern) 'capabilities' embedded ..."
 echo "${SEP}"

 for ((i=0; i<${#gDirArr[@]}; i++))
 do
	dir=${gDirArr[${i}]}
	printf "Scanning %-15s ...\n" "${dir}"
	scanforcaps ${dir}
 done
}

show_traditional_setgid_prg()
{
 echo "Scanning various directories for (traditional) SETGID binaries ..."
 echo "${SEP}"

 for ((i=0; i<${#gDirArr[@]}; i++))
 do
	dir=${gDirArr[${i}]}
	printf "Scanning %-15s ...\n" "${dir}"
	ls -l ${dir} | grep "^-.....s" #| awk '$3=="root" {print $0}'
	echo "${SEP}"
 done
}

show_traditional_setuid_root_prg()
{
 echo "Scanning various directories for (traditional) SETUID-ROOT binaries ..."
 echo "${SEP}"

 for ((i=0; i<${#gDirArr[@]}; i++))
 do
	dir=${gDirArr[${i}]}
	printf "Scanning %-15s ...\n" "${dir}"
	ls -l ${dir} | grep "^-..s" | awk '$3=="root" {print $0}'
	echo "${SEP}"
 done
}

sysinfo()
{
echo "${SEP}"
echo "System Information (LSB):"
echo "${SEP}"
lsb_release -a
echo -n "kernel: "
uname -r
echo "${SEP}"
}

usage()
{
echo "Usage: ${name} 1|2
 1 : Scan for traditional setuid-root and setgid programs installed on the system
 2 : Show for binaries with (modern) POSIX 'capabilities' embedded, installed on the system"
}

##### 'main' : execution starts here #####

[ $# -ne 1 ] && {
	usage
	exit 1
}
case "$1" in
	1) sysinfo
	   show_traditional_setuid_root_prg
	   echo
	   show_traditional_setgid_prg
	;;
	2) sysinfo
	   show_files_with_caps
	;;
	*) usage ; exit 1
esac
exit 0
