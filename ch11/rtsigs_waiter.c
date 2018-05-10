/*
 * ch11:rtsigs_waiter.c
 * ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:
 *  Ch 11 : Signalling
 ****************************************************************
 * Brief Description:
 *
 *
 * Useful to use the shell script 'bombard_sigrt.sh' to literally bombard
 * the process with multiple realtime signals repeatedly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/file.h>
#include "../common.h"

#define	MAX	10
static volatile sig_atomic_t s=0, t=0, blocked=1;

/* 
 * stack(): return the current value of the stack pointer register.
 * The trick/hack: on x86 CPU's, the ABI tells us that the return
 * value is always in the accumulator (EAX/RAX); so we just initialize
 * it to the stack pointer (using inline assembly)!
 */
void *stack(void)
{
	if (__WORDSIZE == 32) {
		__asm__("movl %esp, %eax");
	} else if (__WORDSIZE == 64) {
		__asm__("movq %rsp, %rax");
	}
/* Accumulator holds the return value */
}

/* 
 * Strictly speaking, should not use fprintf here as it's not
 * async-signal safe; indeed, it sometimes does not work well!
 */
static void rt_sighdlr(int signum)
{
	fprintf(stderr, "\nsighdlr: signal %d,", signum);
	if ((signum == SIGRTMAX-5) ||
	    (signum == SIGRTMIN+5) ||
	    (signum == SIGRTMAX)) {
		s ++; t ++;
		if (s >= MAX)
			s = 1;
		fprintf(stderr, " s=%d ; total=%d; stack %p :", s, t, stack());
		DELAY_LOOP_SILENT(s+48, 25); /* +48 to get the equivalent ASCII value */
		fprintf(stderr, "*");
	}
}
static void toggle_rtsigs(int signum)
{
	sigset_t sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGRTMAX-5);
	sigaddset(&sigset, SIGRTMIN+5);
	sigaddset(&sigset, SIGRTMAX);

	if (blocked) {
		fprintf(stderr, "\n*** SIGUSR1 : now *unblocking* the three realtime signals\n");
		if (sigprocmask(SIG_UNBLOCK, &sigset, 0) < 0)
			FATAL("sigprocmask -unblock- failed\n");
		blocked=0;
	} else {
		fprintf(stderr, "\n*** SIGUSR1 : first checking if any of the 3 RT signals\n"
				"are pending delivery...");
		if (sigismember(&sigset, SIGRTMAX-5) ||
		    sigismember(&sigset, SIGRTMIN+5) ||
		    sigismember(&sigset, SIGRTMAX)) {
			fprintf(stderr, " yes; unmasking them\n");
			if (sigprocmask(SIG_UNBLOCK, &sigset, 0) < 0)
				FATAL("sigprocmask -unblock- failed\n");
		}
		fprintf(stderr, " \nNow *blocking* the three realtime signals\n");
		if (sigprocmask(SIG_BLOCK, &sigset, 0) < 0)
			FATAL("sigprocmask -block- failed\n");
		blocked=1;
	}
}

int main(int argc, char **argv)
{
	struct sigaction act;
	sigset_t sigset;

	printf("Trapping the three realtime signals\n");
	memset(&act, 0, sizeof(act));
	act.sa_handler = rt_sighdlr;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGRTMAX-5, &act, 0) == -1)
		FATAL("sigaction %s failed\n", "SIGRTMAX-5");
	if (sigaction(SIGRTMIN+5, &act, 0) == -1)
		FATAL("sigaction %s failed\n", "SIGRTMIN+5");
	if (sigaction(SIGRTMAX, &act, 0) == -1)
		FATAL("sigaction %s failed\n", "SIGRTMAX");

	printf("Now blocking the three realtime signals\n");
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGRTMAX-5);
	sigaddset(&sigset, SIGRTMIN+5);
	sigaddset(&sigset, SIGRTMAX);
	if (sigprocmask(SIG_BLOCK, &sigset, 0) < 0)
		FATAL("sigprocmask -block- failed\n");
	blocked=1;

	/* Trap SIGUSR1 : we'll unblock the RT sigs when this arrives! */
	printf("Trapping SIGUSR1 (RT signal mask toggler)\n");
	memset(&act, 0, sizeof(act));
	act.sa_handler = toggle_rtsigs;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &act, 0) == -1)
		FATAL("sigaction %s failed\n", "SIGUSR1");

	printf("Process awaiting signals ...\n");
	while (1)
		(void)pause();
	exit(EXIT_SUCCESS);
}
/* vi: ts=8 */
