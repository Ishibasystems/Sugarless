/* base64.c */
/* 2013.01.10, 10RU004, �΋��ˑ� */

#include "base64.h"

/* �萔�錾 �f�t�H���g: �I���W�i���� Privacy-Enhanced Mail (PEM) �� Base64 (RFC 1421, deprecated) */
#define def_slong	64L		/* �s������̕�����(���s�Ȃ��� LONG_MAX �ɐݒ�) */
#define base64_62	'+'		/* 63������ */
#define base64_63	'/'		/* 64������ */

char *c2b(const unsigned char *str, unsigned long size, unsigned char slong)
{
	/* char to base64 (�o�C�i�����base64���) */
	unsigned long cnt1, cnt2, cnt;
	char *s = malloc(size * 7 / 5 + 4);

	if (slong % 4 != 0) return s;

	if (slong == 0) slong = def_slong;

	for (cnt1 = cnt2 = 0; cnt1 < size; cnt1 += 3)
	{
		for (cnt = 0; cnt < 4; cnt++, cnt2++)	/* 6bit4���������� */
		{
			if (cnt1 + cnt < size + 1)
			{
				/* 8bit -> 6bit */
				s[cnt2] = (str[cnt1 + cnt - 1] << 6 - cnt * 2 | str[cnt1 + cnt] >> cnt * 2 + 2) & 0x3f;

				/* �ϊ��\���g���ĕϊ� */
				if ( 0 <= s[cnt2] && s[cnt2] <= 25) s[cnt2] += 'A' -  0;
				if (26 <= s[cnt2] && s[cnt2] <= 51) s[cnt2] += 'a' - 26;
				if (52 <= s[cnt2] && s[cnt2] <= 61) s[cnt2] += '0' - 52;
				if (s[cnt2] == 62) s[cnt2] = base64_62;
				if (s[cnt2] == 63) s[cnt2] = base64_63;
			}
			else s[cnt2] = '=';	/* ���p�� */
		}

		if (cnt2 % (slong + 2) == slong)
		{
			s[cnt2++] = '\r';	/* ���s(CR) */
			s[cnt2++] = '\n';	/* ���s(LF) */
		}

		s[cnt2] = '\0';
	}
	return s;
}

char *b2c(const unsigned char *str, unsigned long *size)
{
	/* base64 to char (base64����o�C�i�����) */
	unsigned long cnt1, cnt2, cnt;
	char *s = malloc(strlen(str));

	if (size != NULL) *size = 0;

	for(cnt1 = cnt2 = 0; cnt1 < strlen(str); cnt1 += 4)
	{
		if (str[cnt1] == '\r' && str[cnt1 + 1] == '\n') cnt1 += 2;	/* ���s�͓ǂݔ�΂� */

		for (cnt = cnt1; cnt < cnt1 + 4; cnt++)	/* 6bit4���������� */
			/* �ϊ��\���g���ĕϊ� */
			if (str[cnt] == '=') s[cnt] = 0;	/* ���p�� */
			else
			{
				if (size != NULL) (*size)++;
				if ('A' <= str[cnt] && str[cnt] <= 'Z') s[cnt] = str[cnt] - 'A' +  0;
				else if ('a' <= str[cnt] && str[cnt] <= 'z') s[cnt] = str[cnt] - 'a' + 26;
				else if ('0' <= str[cnt] && str[cnt] <= '9') s[cnt] = str[cnt] - '0' + 52;
				else if (str[cnt] == base64_62) s[cnt] = 62;
				else if (str[cnt] == base64_63) s[cnt] = 63;
				else
				{	/* ���m�̕������� �I�� */
					if (size != NULL) *size = 0;
					free(s);
					return NULL;
				}
			}

		/* 6bit -> 8bit */
		for (cnt = 0; cnt < 3; cnt++) s[cnt2++] = s[cnt1 + cnt] << cnt * 2 + 2 | s[cnt1 + cnt + 1] >> 4 - cnt * 2;

		s[cnt2] = '\0';
	}
	if (size != NULL) *size = *size * 3 / 4;
	return s;
}

char f2b(const char *infile, const char *outfile)
{
	/* flie to base64 (�t�@�C����base64�t�@�C����) */
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
	/* base64 to flie (base64�t�@�C�����t�@�C����) */
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