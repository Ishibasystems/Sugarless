/* base64.h */
/* 2013.01.10, 10RU004, Î‹´Ë‘¾ */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef __base64_h__

	#define __base64_h__

	char *c2b(const unsigned char *, unsigned long, unsigned char);
	char *b2c(const unsigned char *, unsigned long *);
	char f2b(const char *, const char *);
	char b2f(const char *, const char *);

#endif
