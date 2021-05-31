#include"DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
	int BallX, BallY, BallGraph;
	int SikakuX, SikakuY, SikakuMuki, SikakuGraph;

	//��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);

	int set = 0;

	//DX���C�u��������������
	if (DxLib_Init() == -1)	return -1;

	int image[3]{};
	LoadDivGraph("../�p�b�N�}��1.png", 3, 1, 3, 64, 64, image);

	float rotate = 0;

	//�O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//�{�[���N�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	BallGraph = LoadGraph("../Graphic/�p�b�N�}��.png");
	BallX = -64; BallY = 0;

	//�l�p�N�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	SikakuGraph = LoadGraph("../Graphic/�u�����L�[.png");
	SikakuX = 640; SikakuY = 300;

	//�l�p�N�̈ړ��������Z�b�g
	SikakuMuki = 1;


	//�ړ����[�`��
	while (1)
	{

		if (set == 3)set = 0;

		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//�{�[���N�̑��샋�[�`��
		{
			// ���L�[�������Ă�����{�[���N����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_UP) == 1)
			{
				set++;
				BallY -= 3;
				rotate = 3.14 / 2;
			}
			// ���L�[�������Ă�����{�[���N�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				set++;
				BallY += 3;
				//�����o���ĂȂ�
				rotate = 4.7;
			}

			// ���L�[�������Ă�����{�[���N�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
				set++;
				BallX -= 3;
				rotate = 0;
			}

			// ���L�[�������Ă�����{�[���N���E�Ɉړ�������
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				set++;
				BallX += 3;
				rotate = 3.16;
			}

			//�{�[���N����ʍ��[����͂ݏo�������ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallX < 0)BallX = 0;

			//�{�[���N����ʉE�[����͂ݏo�������ɂȂ������ʓ��ɖ߂��Ă�����
			if (BallX > 640 - 64)BallX = 640 - 64;

			// �{�[���N����ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallY < 0)BallY = 0;

			// �{�[���N����ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallY > 480 - 64)BallY = 480 - 64;

			//DrawGraph(BallX, BallY, BallGraph, TRUE);
			DrawRotaGraph(BallX, BallY, 1.5f, rotate, image[set], TRUE);
		}

		//�l�p�N�̈ړ����[�`��
		{
			//�l�p�N�̍��W���ړ����Ă�������Ɉړ�����
			if (SikakuMuki == 1)SikakuX += 3;
			if (SikakuMuki == 0)SikakuX -= 3;

			//�l�p�N����ʉE�[����o�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
			if (SikakuX > 576)
			{
				SikakuX = 576;
				SikakuMuki = 0;

			}

			// �l�p�N����ʍ��[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
			if (SikakuX < 0)
			{
				SikakuX = 0;
				SikakuMuki = 1;
			}

			// �l�p�N��`��
			DrawGraph(SikakuX, SikakuY, SikakuGraph, TRUE);
		}

		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	//DX���C�u�����g�p�̏I������
	DxLib_End();

	return 0;
}