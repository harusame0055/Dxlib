#include"DxLib.h"
using namespace DxLib;

#define PI 3.1415926535897932384626433832795f
#define SHOT 5

int Coroutine(int time, int set);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
#pragma region �ϐ��錾
	int PackmanX, PackmanY, Packman[4], PackmanReverse;
	int PackmanCounter, BallMoveFlag, PackmanMoveValue;

	int set = 0;

	int BlinkyX, BlinkyY, BlinkyMuki, BlinkyGraph, Blinkyreverse;
	int BlinkyDamageFlag, BlinkyDamageCounter, BlinkyDamageGraph, BlinkyMoveValue;

	int ShotX[SHOT], ShotY[SHOT], ShotFlag[SHOT], ShotGraph;

	int BlinkyW, BlinkyH, ShotW, ShotH;
	int ShotBFlag;
	int i;

	int ETamaX, ETamaY, ETamaFlag;
	int ETamaW, ETamaH, ETamaGraph;
	int ETamaCounter;

	int white = GetColor(255, 255, 255);


#pragma endregion

#pragma region DxLib�̏�����
	SetFontSize(32);
	//��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);
	SetBackgroundColor(0, 120, 138);


	//DX���C�u��������������
	if (DxLib_Init() == -1)	return -1;

	float Packmanrotate;

	//�O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

#pragma endregion


#pragma region ������
	//�p�b�N�}���̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	Packman[0] = LoadGraph("../Graphic/�p�b�N�}��1.png");
	Packman[1] = LoadGraph("../Graphic/�p�b�N�}��2.png");
	Packman[2] = LoadGraph("../Graphic/�p�b�N�}��3.png");
	Packman[3] = LoadGraph("../Graphic/�p�b�N�}��4.png");
	PackmanX = 320; PackmanY = 350; Packmanrotate = PI / 2;
	PackmanCounter = 0;
	PackmanReverse = 1;
	PackmanMoveValue = 2;
	//�p�b�N�}���������Ă��邩�ǂ����̕ϐ���(�����Ă��Ȃ�)��\��0����
	BallMoveFlag = 0;

	//�u�����L�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	BlinkyGraph = LoadGraph("../Graphic/�u�����L�[.png");
	BlinkyX = 640; BlinkyY = 100; Blinkyreverse = FALSE;
	BlinkyMoveValue = 2;

	//�u�����L�[�̃_���[�W���̃O���t�B�b�N���������Ƀ��[�h
	BlinkyDamageGraph = LoadGraph("../Graphic/�S�[�X�g.png");

	//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ����̕ϐ��Ɂw�󂯂Ă��Ȃ��x��\��0����
	BlinkyDamageFlag = 0;

	//�G�̒e�̃O���t�B�b�N�����[�h
	ETamaGraph = LoadGraph("../Graphic/EShot.png");

	//�G�̒e�̃O���t�B�b�N�T�C�Y�𓾂�
	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

	//�G�̒e�����ł��邩�ǂ�����ێ�����ϐ��Ɂw���ł��Ȃ��x��\���O����
	ETamaFlag = 0;

	//�G���e��ł^�C�~���O����邽�߂̌v���p�ϐ���0����
	ETamaCounter = 0;

	//�e�̃O���t�B�b�N���������Ƀ��[�h
	ShotGraph = LoadGraph("../Graphic/Shot.png");



	//�e�P�E�Q����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����0�������Ă���
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	//�V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
	ShotBFlag = 0;

	//�u�����L�[�̈ړ��������Z�b�g
	BlinkyMuki = 1;

	//�e�̃O���t�B�b�N�T�C�Y�𓾂�
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//�u�����L�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(BlinkyGraph, &BlinkyW, &BlinkyH);

#pragma endregion


	//�ړ����[�`��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		//�p�b�N�}���������Ă���Ȃ�G���؂�ւ�邩���߂ɃJ�E���^�����Z����
		if (BallMoveFlag == 1)
		{
			PackmanCounter++;

			//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
			//���ɖ߂��Ă�����
			if (PackmanCounter == 10)
			{
				//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
				if (set == 2)
					set = 0;
				else
					set++;

				PackmanCounter = 0;

			}
		}


		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//�p�b�N�}���̑��샋�[�`��
		{
			//�p�b�N�}���̈ړ�����
			{
				// ���L�[�������Ă�����p�b�N�}������Ɉړ�������
				if (CheckHitKey(KEY_INPUT_UP) == 1)
				{
					PackmanY -= PackmanMoveValue;
					Packmanrotate = PI / 2;
					BallMoveFlag = 1;
					PackmanReverse = 1;
				}
				// ���L�[�������Ă�����p�b�N�}�������Ɉړ�������
				else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
				{
					PackmanY += PackmanMoveValue;
					BallMoveFlag = 1;
					Packmanrotate = PI / 2;
					PackmanReverse = 0;
				}
				// ���L�[�������Ă�����p�b�N�}�������Ɉړ�������
				else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
				{
					PackmanX -= PackmanMoveValue;
					BallMoveFlag = 1;
					Packmanrotate = PI / 180;
					PackmanReverse = 1;
				}
				// ���L�[�������Ă�����p�b�N�}�����E�Ɉړ�������
				else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
				{
					PackmanX += PackmanMoveValue;
					BallMoveFlag = 1;
					Packmanrotate = PI;
					PackmanReverse = 1;
				}
				else
				{
					BallMoveFlag = 0;
				}
			}

			//�X�y�[�X�L�[���������ꍇ�͏����𕪊�
			if (CheckHitKey(KEY_INPUT_SPACE))
			{

				set = 3;
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

							//�p�b�N�}���ƒe�̉摜�̃T�C�Y�𓾂�
							GetGraphSize(Packman[set], &Bw, &Bh);
							GetGraphSize(ShotGraph, &Sw, &Sh);

							//�e i �̈ʒu���Z�b�g�A�ʒu�̓p�b�N�}���̒��S�ɂ���
							ShotX[i] = (Bw - Sw) / 2 + PackmanX - 15;
							ShotY[i] = (Bh - Sh) / 2 + PackmanY - 20;

							//�e i�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
							ShotFlag[i] = 1;

							//������o�����̂ŋ����o�����[�v���甲���܂�
							break;
						}
					}
				}

				//�O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂP�i������Ă����j����
				ShotBFlag = 1;

				//�R���[�`�������
				set = Coroutine(15, 0);
			}
			else
			{
				//�V���b�g�{�^����������Ă��Ȃ������ꍇ��
				//�O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
				ShotBFlag = 0;


			}


			//�p�b�N�}������ʍ��[����͂ݏo�������ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (PackmanX < -64)PackmanX = 640;

			//�p�b�N�}������ʉE�[����͂ݏo�������ɂȂ������ʓ��ɖ߂��Ă�����
			if (PackmanX > 640)PackmanX = 0;

			// �p�b�N�}������ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (PackmanY < -64)PackmanY = 480;

			// �p�b�N�}������ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (PackmanY > 480)PackmanY = 0;

			DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, Packmanrotate, Packman[set], TRUE, PackmanReverse);
		}

		//�e�̐������e�𓮂����������J��Ԃ�
		for (i = 0; i < SHOT; i++)
		{
			//���@�̒e�P�̈ړ����[�`��(���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��1(���݂���)�̏ꍇ�̂ݍs��)
			if (ShotFlag[i] == 1)
			{
				//�ei��16�h�b�g��Ɉړ�������
				ShotY[i] -= 4;

				//��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
				if (ShotY[i] < -80)
				{
					ShotFlag[i] = 0;
				}

				//��ʂɒe i ��`�悷��
				DrawGraph(ShotX[i], ShotY[i], ShotGraph, TRUE);
			}
		}

		//�u�����L�[�̈ړ����[�`��
		{
			//�_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
			if (BlinkyDamageFlag == 1)
			{
				//�_���[�W���󂯂Ă���ꍇ�̓_���[�W�O���t�B�b�N��`�悷��
				DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyDamageGraph, TRUE, Blinkyreverse);
				//�_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�[��1�����Z����
				BlinkyDamageCounter++;

				//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
				//���ɖ߂��Ă�����
				if (BlinkyDamageCounter == 30)
				{
					//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
					BlinkyDamageFlag = 0;
				}
			}
			else
			{
				//�u�����L�[�̍��W���ړ����Ă�������Ɉړ�����
				if (BlinkyMuki == 1)BlinkyX += BlinkyMoveValue;
				if (BlinkyMuki == 0)BlinkyX -= BlinkyMoveValue;

				//�u�����L�[����ʉE�[����o�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (BlinkyX > 640)
				{
					BlinkyX = 640;
					BlinkyMuki = 0;
					Blinkyreverse = FALSE;
				}

				// �u�����L�[����ʍ��[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (BlinkyX < 0)
				{
					BlinkyX = 0;
					BlinkyMuki = 1;
					Blinkyreverse = TRUE;
				}

				// �u�����L�[��`��
				DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyGraph, TRUE, Blinkyreverse);

				//�e��ł^�C�~���O���v�����邽�߂̃J�E���^�[�ɂP�������Z
				ETamaCounter++;

				//�����J�E���^�[�ϐ����U�O�������ꍇ�͒e��ł������s��
				if (ETamaCounter == 60)
				{
					//�������łɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
					if (ETamaFlag == 0)
					{
						//�e�̔��ˈʒu��ݒ肷��
						ETamaX = BlinkyX + BlinkyW / 2 - ETamaW / 2;
						ETamaY = BlinkyY + BlinkyH / 2 - ETamaH / 2;
						//�e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
						ETamaFlag = 1;

					}
					//�e��ł^�C�~���O���v�����邽�߂̕ϐ��ɂO����
					ETamaCounter = 0;
				}

			}

		}

		//�G�̒e�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
		if (ETamaFlag == 1)
		{
			//�������ɂ��炷
			ETamaY += 8;

			//�����e����ʉ��[����͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
			//��\���O�ɂ���
			if (ETamaY > 480)
				ETamaFlag = 0;

			//��ʂɕ`�悷��(ETamaGraph :�G�̒e�̃O���t�B�b�N�̃n���h��)
			DrawGraph(ETamaX, ETamaY, ETamaGraph, TRUE);
		}


		//�e�ƓG�̓����蔻��A�e�̐������J��Ԃ�
		for (i = 0; i < SHOT; i++)
		{
			//�ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
			if (ShotFlag[i] == 1)
			{
				//�u�����L�[�Ƃ̓����蔻��
				if (((ShotX[i] > BlinkyX && ShotX[i] < BlinkyX + BlinkyW) ||
					(BlinkyX > ShotX[i] && BlinkyX < ShotX[i] + ShotW)) &&
					((ShotY[i] > BlinkyY && ShotY[i] < BlinkyY + BlinkyH) ||
						(BlinkyY > ShotY[i] && BlinkyY < ShotY[i] + ShotH)))
				{
					//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					ShotFlag[i] = 0;

					//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					ShotFlag[i] = 0;

					//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�󂯂Ă���x��\���P����
					BlinkyDamageFlag = 1;

					//�u�����L�[���_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
					BlinkyDamageCounter = 0;
				}
			}
		}

		//�������\��
		DrawFormatString(0, 0, white, "�Q�[�����");

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

int Coroutine(int time, int set)
{
	int corTime = 0;
	for (int i = 0; i < time; i++)
	{
		if (i == time - 1)
		{
			corTime++;
			if (corTime == 10)
				break;
		}
	}
	return set;
}
