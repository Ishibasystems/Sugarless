#include "bmpsave.h"

#define _USE_MATH_DEFINES
#include <math.h>

void main()
{
	unsigned char buf[256*256*3];
	short x, y;
	double inf;

	for (y = 0; y < 256; y++)
	{
		for (x = 0; x < 256; x++)
		{
			inf = M_PI * 330 / 180 *  sqrt(x * x + y * y) / sqrt(256 * 256 * 2);
			buf[3*y*256+3*x+0] = (unsigned char)(255 * (cos(inf               ) + 1) / 2);
			buf[3*y*256+3*x+1] = (unsigned char)(255 * (cos(inf - M_PI * 2 / 3) + 1) / 2);
			buf[3*y*256+3*x+2] = (unsigned char)(255 * (cos(inf - M_PI * 4 / 3) + 1) / 2);
		}
		printf("%d ok.\n", y);
	}
	printf("ok.\n");
	bmpsave("test_save.bmp", buf, 256, 256, 3, 1);
	return;
}