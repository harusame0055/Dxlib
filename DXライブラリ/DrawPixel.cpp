#include"DxLib.h"
using namespace DxLib;

#define PI 3.1415926535897932384626433832795f

#define SHOT 2

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
	int BallX, BallY, BallGraph;
	int SikakuX, SikakuY, SikakuMuki, SikakuGraph, Sikakureverse;
	int SikakuDamageFlag, SikakuDamageCounter, SikakuDamageGraph;
	int ShotX[SHOT], ShotY[SHOT], ShotFlag[SHOT], ShotGraph;
	int SikakuW, SikakuH, ShotW, ShotH;
	int ShotBFlag;
	int i;

	int white = GetColor(0, 0, 255);

	SetFontSize(32);


	//��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);

	int set = 0;

	//DX���C�u��������������
	if (DxLib_Init() == -1)	return -1;

	float Ballrotate;

	//�O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//�{�[���N�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	BallGraph = LoadGraph("../Graphic/�p�b�N�}��1.png");
	BallX = 320; BallY = 350; Ballrotate = PI / 2;

	//�l�p�N�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	SikakuGraph = LoadGraph("../Graphic/�u�����L�[.png");
	SikakuX = 640; SikakuY = 50; Sikakureverse = FALSE;

	//�l�p�N�̃_���[�W���̃O���t�B�b�N���������Ƀ��[�h
	SikakuDamageGraph = LoadGraph("../Graphic/�S�[�X�g.png");

	//�l�p�N���_���[�W���󂯂Ă��邩�ǂ����̕ϐ��Ɂw�󂯂Ă��Ȃ��x��\��0����
	SikakuDamageFlag = 0;

	//�e�̃O���t�B�b�N���������Ƀ��[�h
	ShotGraph = LoadGraph("../Graphic/Shot.png");


	//�e�P�E�Q����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����0�������Ă���
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	//�V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
	ShotBFlag = 0;

	//�l�p�N�̈ړ��������Z�b�g
	SikakuMuki = 1;

	//�e�̃O���t�B�b�N�T�C�Y�𓾂�
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//�l�p�N�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(SikakuGraph, &SikakuW, &SikakuH);

	//�ړ����[�`��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (set == 3)set = 0;

		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//�{�[���N�̑��샋�[�`��
		{
			//�{�[���N�̈ړ�����
			{
				// ���L�[�������Ă�����{�[���N����Ɉړ�������
				if (CheckHitKey(KEY_INPUT_UP) == 1)
				{
					set++;
					BallY -= 3;
					Ballrotate = PI / 2;
				}
				// ���L�[�������Ă�����{�[���N�����Ɉړ�������
				else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
				{
					set++;
					BallY += 3;
				}
				// ���L�[�������Ă�����{�[���N�����Ɉړ�������
				else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
				{
					set++;
					BallX -= 3;
				}
				// ���L�[�������Ă�����{�[���N���E�Ɉړ�������
				else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
				{
					set++;
					BallX += 3;
				}
			}


			//�X�y�[�X�L�[���������ꍇ�͏����𕪊�
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				//�O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���0��������e�𔭎�
				if (ShotBFlag == 0)
				{
					//��ʏ�ɏo�Ă��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
					for (i = 0; i < SHOT; i++)
					{
						//�ei����ʏ�ɏo�Ă��Ȃ��ꍇ�͂��̒e����ʂɏo��
						if (ShotFlag[i] == 0)
						{
							int Bw, Bh, Sw, Sh;

							//�{�[���N�ƒe�̉摜�̃T�C�Y�𓾂�
							GetGraphSize(BallGraph, &Bw, &Bh);
							GetGraphSize(ShotGraph, &Sw, &Sh);

							//�e i �̈ʒu���Z�b�g�A�ʒu�̓{�[���N�̒��S�ɂ���
							ShotX[i] = BallX - 10;
							ShotY[i] = BallY + 10;

							//�e i�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
							ShotFlag[i] = 1;

							//������o�����̂ŋ����o�����[�v���甲���܂�
							break;
						}
					}
				}

				//�O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂP�i������Ă����j����
				ShotBFlag = 1;
			}
			else
			{
				//�V���b�g�{�^����������Ă��Ȃ������ꍇ��
				//�O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
				ShotBFlag = 0;
			}


			//�{�[���N����ʍ��[����͂ݏo�������ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallX < -64)BallX = 640;

			//�{�[���N����ʉE�[����͂ݏo�������ɂȂ������ʓ��ɖ߂��Ă�����
			if (BallX > 640)BallX = 0;

			// �{�[���N����ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallY < -64)BallY = 480;

			// �{�[���N����ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallY > 480)BallY = 0;

			DrawRotaGraph2(BallX, BallY, 32, 32, 1, Ballrotate, BallGraph, TRUE, TRUE);
		}

		//�e�̐������e�𓮂����������J��Ԃ�
		for (i = 0; i < SHOT; i++)
		{
			//���@�̒e�P�̈ړ����[�`��(���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��1(���݂���)�̏ꍇ�̂ݍs��)
			if (ShotFlag[i] == 1)
			{
				//�ei��16�h�b�g��Ɉړ�������
				ShotY[i] -= 16;

				//��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
				if (ShotY[i] < -80)
				{
					ShotFlag[i] = 0;
				}

				//��ʂɒe i ��`�悷��
				DrawGraph(ShotX[i], ShotY[i], ShotGraph, TRUE);
			}
		}
		//�l�p�N�̈ړ����[�`��
		{
			//�_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
			if (SikakuDamageFlag == 1)
			{
				//�_���[�W���󂯂Ă���ꍇ�̓_���[�W�O���t�B�b�N��`�悷��
				DrawRotaGraph2(SikakuX, SikakuY, 32, 32, 1, 0, SikakuDamageGraph, FALSE, Sikakureverse);
				//�_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�[��1�����Z����
				SikakuDamageCounter++;

				//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
				//���ɖ߂��Ă�����
				if (SikakuDamageCounter == 30)
				{
					//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
					SikakuDamageFlag = 0;
				}
			}
			else
			{
				//�l�p�N�̍��W���ړ����Ă�������Ɉړ�����
				if (SikakuMuki == 1)SikakuX += 3;
				if (SikakuMuki == 0)SikakuX -= 3;

				//�l�p�N����ʉE�[����o�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (SikakuX > 640)
				{
					SikakuX = 640;
					SikakuMuki = 0;
					Sikakureverse = FALSE;
				}

				// �l�p�N����ʍ��[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (SikakuX < 0)
				{
					SikakuX = 0;
					SikakuMuki = 1;
					Sikakureverse = TRUE;
				}

				// �l�p�N��`��
				DrawRotaGraph2(SikakuX, SikakuY, 32, 32, 1, 0, SikakuGraph, TRUE, Sikakureverse);
			}

		}

		//�e�ƓG�̓����蔻��A�e�̐������J��Ԃ�
		for (i = 0; i < SHOT; i++)
		{
			//�ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
			if (ShotFlag[i] == 1)
			{
				//�l�p�N�Ƃ̓����蔻��
				if (((ShotX[i] > SikakuX && ShotX[i] < SikakuX + SikakuW) ||
					(SikakuX > ShotX[i] && SikakuX < ShotX[i] + ShotW)) &&
					((ShotY[i] > SikakuY && ShotY[i] < SikakuY + SikakuH) ||
						(SikakuY > ShotY[i] && SikakuY < ShotY[i] + ShotH)))
				{
					//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					ShotFlag[i] = 0;

					//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					ShotFlag[i] = 0;

					//�l�p�N���_���[�W���󂯂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�󂯂Ă���x��\���P����
					SikakuDamageFlag = 1;

					//�l�p�N���_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
					SikakuDamageCounter = 0;
				}
			}
		}

		//�������\��
		DrawFormatString(0, 0, white, "");

		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();



		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;


	}

	//DX���C�u�����g�p�̏I������
	DxLib::DxLib_End();

	return 0;
}
