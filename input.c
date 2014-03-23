/* input.c */
/* 2011.06.12, 10RU004,	Î‹´Ë‘¾ */

#include <stdio.h>

void input(char s[], long len)
{
	fgets(s, len, stdin);

	if (strchr(s, '\n') != 0) s[strlen(s) - 1] = '\0';
	else while(getchar() != '\n');

	return;
}