================================================================================
     Sugarless rev13 (2014/03/23) [ASO-1A-1]
                  �@�@�@�@�@�@�@�@�@�@�@    ����Ґl�i�� �΋��ˑ� / ���㐰��
================================================================================
                                  WARNING : FOR HAND OUT AND USE IN JAPAN ONLY.

1. �t�@�C�����e

	base64.c / base64.h
	crc16.c / crc16.h
	bmpsave.c / bmpsave.h
	input.c / input.h
		 : �\�[�X�t�@�C�� �ڍׂ͉��L

	TEST_BASE64.c
	TEST_bmpsave.c
		 : �f�����X�g���[�V�����v���O���� �ڍׂ͉��L

	compiler.cmd	: �o�b�`�t�@�C�� VisualStudio��CL�R���p�C�������[�h���܂��B
					VC++6.0�AVS2002�AVS2003�AVS2005�AVS2008�AVS2010�AVS2012�Ή�

	clear.cmd	: �o�b�`�t�@�C�� *.obj, *.exe *.exp, *.lib���ꊇ�폜���܂��B

	readme.txt	: ���̃h�L�������g�ł��B

2. �g����

	�֐����C�u�����Ȃ̂ŁC����P�̂ł̎g�p�͂ł��܂���B
	�K��C�R���p�C�����K�v�ƂȂ�܂��B

	�֐��̐���
	�Ebase64.c

		char *c2b(const unsigned char *, unsigned long, unsigned char);
			��1����: �f�[�^�̊i�[�ꏊ
			��2����: �ǂݎ�镶����
			��3����: ���������Ƃɉ��s�����邩(0�w��:���s�Ȃ�)

			�f�[�^��ϊ����ABase64������ւ̃|�C���^��Ԃ��܂��B
			������ւ̃|�C���^�͎g�p��free�֐��ŉ�����Ă��������B
			���s�����镶������4�̔{���łȂ���΂����܂���B

		char *b2c(const unsigned char *, unsigned long *);
			��1����: Base64�f�[�^�̊i�[�ꏊ
			��2����: �������������������i�[����ϐ�(�s�v�Ȃ�NULL�w��)

			Base64�������ϊ����A�f�[�^�ւ̃|�C���^��Ԃ��܂��B
			�f�[�^�ւ̃|�C���^�͎g�p��free�֐��ŉ�����Ă��������B
			Base64������łȂ��f�[�^��n�����ꍇ�A�ϊ��͎��s��
			��������0�ɂ��ANULL�|�C���^��Ԃ��܂��B

		char f2b(const char *, const char *);
			��1����: ���̓t�@�C����
			��2����: �o�̓t�@�C����

			�t�@�C���f�[�^��Base64�t�@�C���ɕϊ����܂��B

		char b2f(const char *, const char *);
			��1����: ���̓t�@�C����
			��2����: �o�̓t�@�C����

			Base64�t�@�C�����t�@�C���f�[�^�ɕϊ����܂��B

	�Ecrc16.c
		void crc16_init(void);

			CRC-16-CCITT�v�Z�p�̃f�[�^�e�[�u�����쐬���܂��B
			crc16�֐����Ăяo���O�Ɉ�x�͎��s���Ă��������B

		unsigned int crc16(unsigned char *, long);
			��1����: �f�[�^�̊i�[�ꏊ
			��2����: �ǂݎ�镶����

			�f�[�^��CRC-16-CCITT�Ōv�Z���ACRC16�l��Ԃ��܂��B

	�Ebmpsave.c

			char bmpsave(const char *, const void *, unsigned long, unsigned long, unsigned char, unsigned char);
			��1����: �o�̓t�@�C����
			��2����: �f�[�^�̊i�[�ꏊ
			��3����: �r�b�g�}�b�v�̕�
			��4����: �r�b�g�}�b�v�̍���
			��5����: 1�s�N�Z�����̃f�[�^��(�o�C�g�P��)
			��6����: �o�̓t�@�C���^�C�v(true: bmp�Afalse: pgm)

			�f�[�^���r�b�g�}�b�v�摜�Ƃ��ăt�@�C���ɕۑ����܂��B
			���݁A1�s�N�Z�����̃f�[�^�ʂ�1�o�C�g(8bit�O���C�X�P�[��)�A
			3�o�C�g�E4�o�C�g(24bit�E32bit true�J���[)�̂ݑΉ��B
			�i�[�f�[�^��Gray1�o�C�g�ARGB3�o�C�g�ARGBA4�o�C�g�̏��ł��B
			�ۑ����s����0�ȊO��Ԃ��܂��B

	�Einput.c
		void input(char *, long);
			������: �f�[�^�̊i�[�ꏊ
			������: �ǂݎ�镶����

			�R���\�[������̓��͂��i�[���܂��B
			���Ԃ�fgets�֐������S���������̂ł��B

	�ETEST_BASE64.c
		�K�{ base64.c, input.c

		Base64�̕ϊ��f���v���O�����B

	�ETEST_bmpsave.c
		�K�{ bmpsave.c

		bmp�̕ۑ��f���v���O�����B


3. �����

	�ȉ��̊��ł̓�����m�F���Ă��܂��B

  [�g�p�R���p�C���[]
  Microsoft Visual Studio 2008 Professional Edition version 9.0.30729.4108 QFE

4. �]�ڋy�ђ��쌠�ɂ���

	NYSL Version 0.9982

	A. �{�\�t�g�E�F�A�� Everyone'sWare �ł��B���̃\�t�g����ɂ�����l��l���A
	   �������̍�������̂������̂Ɠ����悤�ɁA���R�ɗ��p���邱�Ƃ��o���܂��B

	  A-1. �t���[�E�F�A�ł��B��҂���͎g�p������v�����܂���B
	  A-2. �L��������}�̂̔@�����킸�A���R�ɓ]�ځE�Ĕz�z�ł��܂��B
	  A-3. �����Ȃ��ނ� ���ρE���v���O�����ł̗��p ���s���Ă��\���܂���B
	  A-4. �ύX�������̂╔���I�Ɏg�p�������̂́A���Ȃ��̂��̂ɂȂ�܂��B
	       ���J����ꍇ�́A���Ȃ��̖��O�̉��ōs���ĉ������B

	B. ���̃\�t�g�𗘗p���邱�Ƃɂ���Đ��������Q���ɂ��āA��҂�
	   �ӔC�𕉂�Ȃ����̂Ƃ��܂��B�e���̐ӔC�ɂ����Ă����p�������B

	C. ����Ґl�i���� �΋��ˑ� / ���㐰�� �ɋA�����܂��B���쌠�͕������܂��B

	D. �ȏ�̂R���́A�\�[�X�E���s�o�C�i���̑o���ɓK�p����܂��B

5. ���J��ɂ���

	�ꎟ�z�z��́Ahttp://ishibasystems.ikaduchi.com/ �ƂȂ��Ă��܂��B
	���j���[����"�_�E�����[�h"�̃y�[�W�܂ōs���Ό�����͂��c�ł��B

6. �T�|�[�g�ɂ���

	1. ���[��

	Web�y�[�W http://ishibasystems.ikaduchi.com/ 
	�̃��j���[����A"e-mail"�̃y�[�W�ɂ���܂��B

	�T�[�o�y�у��[���u���E�U�̐ݒ�チ�[�����͂��Ȃ�
	 (���ہC�܂���	�폜�����) �ꍇ������܂��̂łł������
	NG���[�h(�X�p�����m����钼�ڃ����NURL�Ȃ�)�͔����Ă��������B

	���悭���A�h��ł��Y��đ����Ă�l�����܂��B���_�ԐM�ł��܂���B

	2. twitter

	�C���^�[�l�b�g�̔g�c�Ƃ������c

	Web�y�[�W http://twitter.com/#!/FujishiroSeiran
	�����̃A�J�E���g�ɂȂ�܂��B

  ��{�I�ɓy�j���E���j���̓C���^�[�l�b�g�����Ă��Ȃ�
  (�g�тŃ��[���̎�M�͉�)�̂Ń^�C�~���O�ɂ���Ă�
  �ԐM��3�������邩���ł��B�Œ�3���قǂ̗]�T��������
  ���₷��悤�ɂ��肢���܂��B

7. �Ō��

        �����̂����ɗ��Ă�΍K���ł��B



