/* crc16.c */
/* 2011.06.18, 10RU004, �΋��ˑ� */

unsigned int crc16(unsigned char *str, long size)
{
	static unsigned int crctable[0x100];

	unsigned int i, j, r, r = 0xFFFFU;

	if (size < 0)
	{
		for (i = 0; i <= 0xff; i++)
		{
			r = i << 8;

			for (j = 0; j < 8; j++)
				if (r & 0x8000U) r = r << 1 ^ 0x1021U;	/* �g�p����CRC16�̃^�C�v x^16+x^12+x^5+1 */
				else r <<= 1;

			crctable[i] = r & 0xFFFFU;
		}
	}
	else while(--size >= 0) r = r << 8 ^ crctable[(unsigned char)(r >> 8) ^ *str++];

	return ~r & 0xFFFFU;
}

void crc16_init(void)
{
	crc16(NULL, -1);
	return;
}