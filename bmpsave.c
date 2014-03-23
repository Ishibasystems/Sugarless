/* bmpとしてデータ列を保存 bmpsave.c */
/* Mandelbrot.c (2012.01.16) からの抜き出し */
/* 2013.01.10, 10RU004, 石橋祥太 */

#include "bmpsave.h"

#define ERROR_FORMAT	1
#define ERROR_FILEOPEN	2

char bmpsave(const char *filename, const void *pixmaps, unsigned long XSIZE, unsigned long YSIZE, unsigned char ZSIZE, unsigned char mode)
{
	const unsigned char *maps = pixmaps;
	unsigned short BMPHEADERm[4] = {0, 0, 1, ZSIZE * 8};
	unsigned long BMPHEADER[10];
	unsigned long count, countX, countY;
	FILE *fp;

	if (mode)
	{	/* BITMAP出力処理 */

		/* フォーマット例外 */
		if (XSIZE > LONG_MAX) return ERROR_FORMAT;
		if (YSIZE > LONG_MAX) return ERROR_FORMAT;
		if (54 + XSIZE * YSIZE * ZSIZE > ULONG_MAX) return ERROR_FORMAT;

		/* ファイル書き込み開始 */
		if ((fp = fopen(filename, "wb")) == NULL) return ERROR_FILEOPEN;

		/* 構造体のアライメント回避が(クロスプラットフォームだとコンパイラの指定変更とか)
		   面倒なので非構造体で書き出し */

		/* BMPFILEHEADER */
		fprintf(fp, "BM");	/* bfType */
		BMPHEADER[0] = 54 + XSIZE * YSIZE * ZSIZE;	/* bfSize */
		memcpy(&BMPHEADER[1], BMPHEADERm, 4);	/* bfReserved1 + bfReserved2 */
		BMPHEADER[2] = 54;	/* bfOffBits */
		fwrite(BMPHEADER, sizeof(unsigned long), 3, fp);

		/* BMPINFOHEADER */
		BMPHEADER[0] = 40;	/* biSize */
		BMPHEADER[1] = XSIZE;	/* biWidth */
		BMPHEADER[2] = YSIZE;	/* biHeight */
		memcpy(&BMPHEADER[3], &BMPHEADERm[2], 4);	/* biPlanes + biBitCount */
		BMPHEADER[4] = 0;	/* biCompression */
		BMPHEADER[5] = XSIZE * YSIZE * ZSIZE;	/* biSizeImage */
		BMPHEADER[6] = 0;	/* biXPelsPerMeter */
		BMPHEADER[7] = 0;	/* biYPelsPerMeter */
		BMPHEADER[8] = 0;	/* biClrUsed */
		BMPHEADER[9] = 0;	/* biClrImportant */
		fwrite(BMPHEADER, sizeof(unsigned long), 10, fp);

		/* DATA */
		for (countY = YSIZE; countY > 0; countY--)	/* 左下から右上へ */
		{
			for (countX = (countY - 1) * XSIZE; countX < XSIZE + (countY - 1) * XSIZE; countX++)
				for (count = ZSIZE; count > 0; count--)
					fprintf(fp, "%c", maps[countX * ZSIZE + count - 1]);

			/* 1ラインは必ず4バイトの倍数にする */
			for (count = 0; count < (4 - XSIZE * ZSIZE % 4) % 4; count++)
				fprintf(fp, "%c", 0);
		}
	}
	else
	switch (ZSIZE)
	{	/* ファイル書き込み開始 */
		if ((fp = fopen(filename, "wb")) == NULL) return ERROR_FILEOPEN;

	case 1:	/* P5出力処理 */
		fprintf(fp, "P5\n# bmpsave.c\n%d %d\n255\n", XSIZE, YSIZE);
		fwrite(maps, sizeof(unsigned char), XSIZE * YSIZE, fp);
		break;

	case 3:	/* P6出力処理 */
	case 4:
		fprintf(fp, "P6\n# bmpsave.c\n%d %d\n255\n", XSIZE, YSIZE);
		for (count = 0; count < XSIZE * YSIZE; count++)
			fprintf(fp, "%c%c%c", maps[count * ZSIZE + 0], maps[count * ZSIZE + 1], maps[count * ZSIZE + 2]);
		break;
	}
	fclose(fp);	/* ファイル書き込み終了 */
	return 0;
}