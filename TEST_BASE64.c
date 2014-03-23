/* TEST_BASE64.c */
/* 2011.06.19, 10RU004, êŒã¥èÀëæ */

#include "input.h"
#include "base64.h"

void main()
{
	char a[0x100], *p, *q;

	printf("INPUT : ");

	input(a, 0xff);

	p = c2b(a, strlen(a), 0);

	printf("ENCODE: %s\n", p);

	q = b2c(p, NULL);

	printf("DECODE: %s\n", q);

	free(p);
	free(q);

	f2b("readme.txt", "readme.b64");
	b2f("readme.b64", "readme2.txt");

	return;
}