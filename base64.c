/* base64.c */
/* 2013.01.10, 10RU004, 石橋祥太 */

#include "base64.h"

/* 定数宣言 デフォルト: オリジナルの Privacy-Enhanced Mail (PEM) の Base64 (RFC 1421, deprecated) */
#define def_slong	64L		/* 行あたりの文字数(改行なしは LONG_MAX に設定) */
#define base64_62	'+'		/* 63文字目 */
#define base64_63	'/'		/* 64文字目 */

char *c2b(const unsigned char *str, unsigned long size, unsigned char slong)
{
	/* char to base64 (バイナリ列をbase64列へ) */
	unsigned long cnt1, cnt2, cnt;
	char *s = malloc(size * 7 / 5 + 4);

	if (s == NULL) return NULL;

	if (slong % 4 != 0) return s;	/* 行あたりの文字数は必ず4の倍数を指定 */
	if (slong == 0) slong = def_slong;

	for (cnt1 = cnt2 = 0; cnt1 < size; cnt1 += 3)
	{
		for (cnt = 0; cnt < 4; cnt++, cnt2++)	/* 6bit4文字ずつ処理 */
		{
			if (cnt1 + cnt < size + 1)
			{
				/* 8bit -> 6bit */
				s[cnt2] = (str[cnt1 + cnt - 1] << 6 - cnt * 2 | str[cnt1 + cnt] >> cnt * 2 + 2) & 0x3f;

				/* 変換表を使って変換 */
				if (s[cnt2] <= 25) s[cnt2] += 'A';
				else if (26 <= s[cnt2] && s[cnt2] <= 51) s[cnt2] += 'a' - 26;
				else if (52 <= s[cnt2] && s[cnt2] <= 61) s[cnt2] += '0' - 52;
				else if (s[cnt2] == 62) s[cnt2] = base64_62;
				else s[cnt2] = base64_63;	/* 必ず64文字目 */
			}
			else s[cnt2] = '=';	/* 腹パン */
		}

		if (cnt2 % (slong + 2) == slong)
		{
			s[cnt2++] = '\r';	/* 改行(CR) */
			s[cnt2++] = '\n';	/* 改行(LF) */
		}

		s[cnt2] = '\0';
	}
	return s;
}

char *b2c(const unsigned char *str, unsigned long *size)
{
	/* base64 to char (base64列をバイナリ列へ) */
	unsigned long cnt1, cnt2, cnt;
	char *s = malloc(strlen(str) * 5 / 7 + 1);

	if (size != NULL) *size = 0;

	for(cnt1 = cnt2 = 0; cnt1 < strlen(str); cnt1 += 4)
	{
		if (str[cnt1] == '\r' && str[cnt1 + 1] == '\n') cnt1 += 2;	/* 改行は読み飛ばし */

		for (cnt = cnt1; cnt < cnt1 + 4; cnt++)	/* 6bit4文字ずつ処理 */
			/* 変換表を使って変換 */
			if (str[cnt] == '=') s[cnt] = 0;	/* 腹パン */
			else
			{
				if (size != NULL) (*size)++;
				if ('A' <= str[cnt] && str[cnt] <= 'Z') s[cnt] = str[cnt] - 'A' +  0;
				else if ('a' <= str[cnt] && str[cnt] <= 'z') s[cnt] = str[cnt] - 'a' + 26;
				else if ('0' <= str[cnt] && str[cnt] <= '9') s[cnt] = str[cnt] - '0' + 52;
				else if (str[cnt] == base64_62) s[cnt] = 62;
				else if (str[cnt] == base64_63) s[cnt] = 63;
				else
				{	/* 未知の文字混在 終了 */
					if (size != NULL) *size = 0;
					free(s);
					return NULL;
				}
			}

		/* 6bit -> 8bit */
		for (cnt = 0; cnt < 3; cnt++)
			s[cnt2++] = s[cnt1 + cnt] << cnt * 2 + 2 | s[cnt1 + cnt + 1] >> 4 - cnt * 2;

		s[cnt2] = '\0';
	}
	if (size != NULL) *size = cnt2;
	return s;
}

char f2b(const char *infile, const char *outfile)
{
	/* flie to base64 (ファイルをbase64ファイルへ) */
	char *s, size;
	unsigned char buffer[def_slong * 3 / 4];
	FILE *fp1, *fp2;

	if ((fp1 = fopen(infile, "rb")) == NULL) return 0;
	if ((fp2 = fopen(outfile, "wb")) == NULL) return 0;

	while ((size = fread(buffer, sizeof(unsigned char), def_slong * 3 / 4, fp1)) != 0)
	{
		fprintf(fp2, "%s", s = c2b(buffer, size, 0));
		free(s);
		if (size != def_slong * 3 / 4) break;
	}; 

	fclose(fp1);
	fclose(fp2);
	return 1;
}

char b2f(const char *infile, const char *outfile)
{
	/* base64 to flie (base64ファイルをファイルへ) */
	unsigned char *s;
	char *t;
	unsigned long u, size;
	FILE *fp1, *fp2;

	if ((fp1 = fopen(infile, "rb")) == NULL) return 0;
	if ((fp2 = fopen(outfile, "wb")) == NULL) return 0;

	fseek(fp1, 0, SEEK_END);
	size = ftell(fp1);
	fseek(fp1, 0, SEEK_SET);

	fread(s = malloc(size + 1), sizeof(unsigned char), size, fp1);
	s[size] = '\0';
	t = b2c(s, &u);
	fwrite(t, sizeof(char), u, fp2);

	free(s);
	free(t);
	fclose(fp1);
	fclose(fp2);
	return 1;
}
