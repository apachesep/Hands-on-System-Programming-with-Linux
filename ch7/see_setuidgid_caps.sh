#!/bin/bash
# ch6:see_setuidgid_caps.sh
# 
#***************************************************************
# This program is part of the source code released for the book
#  "Hands-on System Programming with Linux"
#  (c) Author: Kaiwan N Billimoria
#  Publisher:  Packt
#
# From:
#  Ch 6 : Process Credentials
#****************************************************************
# Brief Description:
# Based on user choice, this bash script scans the system for all
# installed :
# 1. traditional setuid-root and setgid programs
# 2. modern POSIX capabilities-embedded programs.
name=$(basename $0)
SEP="------------------------------------------------------------------"

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
 ShowTitle "Scanning various folders for binaries with (modern) 'capabilities' embedded ..."
 aecho "Scanning /bin ..."
 scanforcaps /bin
 aecho "Scanning /usr/bin ..."
 scanforcaps /usr/bin
 aecho "Scanning /sbin ..."
 scanforcaps /sbin
 aecho "Scanning /usr/sbin ..."
 scanforcaps /usr/sbin
 aecho "Scanning /usr/local/bin ..."
 scanforcaps /usr/local/bin
 aecho "Scanning /usr/local/sbin ..."
 scanforcaps /usr/local/sbin
}

show_traditional_setuid_root()
{
 echo "${SEP}"
 echo "Scanning various folders for traditional setuid-root binaries ..."
 echo "${SEP}"
 echo "Scanning /bin ..."
 ls -l /bin/  |grep "^-..s" |awk '$3=="root" {print $0}'
 echo "${SEP}"
 echo "Scanning /usr/bin ..."
 ls -l /usr/bin/  |grep "^-..s" |awk '$3=="root" {print $0}'
 echo "${SEP}"
 echo "Scanning /sbin ..."
 ls -l /sbin/  |grep "^-..s" |awk '$3=="root" {print $0}'
 echo "${SEP}"
 echo "Scanning /usr/sbin ..."
 ls -l /usr/sbin/  |grep "^-..s" |awk '$3=="root" {print $0}'
 echo "${SEP}"
 echo "Scanning /usr/local/bin ..."
 ls -l /usr/local/bin/  |grep "^-..s" |awk '$3=="root" {print $0}'
 echo "${SEP}"
 echo "Scanning /usr/local/sbin ..."
 ls -l /usr/local/sbin/  |grep "^-..s" |awk '$3=="root" {print $0}'
}

sysinfo()
{
echo "${SEP}"
echo "System Information (LSB):"
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
	   show_traditional_setuid_root
	;;
	2) sysinfo
	   show_files_with_caps
	;;
	*) usage ; exit 1
esac
exit 0
