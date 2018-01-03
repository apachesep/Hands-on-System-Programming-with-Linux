/*
 * hello.c
 *
 **********************************************************************
 * This program is part of the source code released for the book
 *  "Linux System Programming"
 *  (c) Kaiwan N Billimoria
 *  Packt Publishers
 *
 * From:
 *  Ch 1 : Linux System Architecture
 **********************************************************************
 * A quick 'Hello, World'-like program to demonstrate using objdump to
 * show the corresponding assembly and machine language.
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int a;

	printf("Hello, Linux System Programming, World!\n");
	a = 5;
	exit(0);
}
