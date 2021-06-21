#include"DxLib.h"
#include "Player.h"
#include<math.h>

Game* gameptr;

void Player::SetGame(Game* g) {
	gameptr = g;
}

void Player::initialize()
{
	//�p�b�N�}���̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	Packman[0] = LoadGraph("../Graphic/�p�b�N�}��1.png");
	Packman[1] = LoadGraph("../Graphic/�p�b�N�}��2.png");
	Packman[2] = LoadGraph("../Graphic/�p�b�N�}��3.png");
	Packman[3] = LoadGraph("../Graphic/�p�b�N�}��4.png");
	Packman[4] = LoadGraph("../Graphic/�_���[�W�p�b�N�}��.png");
	PackmanX = 320; PackmanY = 350; Packmanrotate = PI / 2;
	PackmanCounter = 0;
	PackmanReverse = 1;
	//�p�b�N�}���������Ă��邩�ǂ����̕ϐ���(�����Ă��Ȃ�)��\��0����
	BallMoveFlag = 0;
	PackmanDamageFlag = 0;
	PackmanMoveValue = 5;

	ShotSpeed = 10;

	//�e�̃O���t�B�b�N���������Ƀ��[�h
	ShotGraph = LoadGraph("../Graphic/Shot.png");

	//�p�b�N�}���ƒe�̉摜�T�C�Y�𓾂�
	GetGraphSize(Packman[set], &Bw, &Bh);
	GetGraphSize(ShotGraph, &Sw, &Sh);

	hitCount = 0;

	//�e�P�E�Q����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����0�������Ă���
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	//�V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
	ShotBFlag = 0;

	//�e�̃O���t�B�b�N�T�C�Y�𓾂�
	GetGraphSize(ShotGraph, &ShotW, &ShotH);


	ShotAudio = LoadSoundMem("../BGM/�V���b�g.mp3");
	HitAudio = LoadSoundMem("../BGM/�V���b�g����.mp3");
}
void Player::PlayerMove()
{
	{
		//�_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
		if (PackmanDamageFlag == 1)
		{
			set = 4;

			//�_���[�W���󂯂Ă���ꍇ�̓_���[�W�O���t�B�b�N��`�悷��
			DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, 0, Packman[set], TRUE, PackmanReverse);
			//�_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�[��1�����Z����
			PackmanDamageCounter++;

			//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
			//���ɖ߂��Ă�����
			if (PackmanDamageCounter == 30)
			{
				//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
				PackmanDamageFlag = 0;
				set = 0;
			}
		}
		//�p�b�N�}���̈ړ�����
		else
		{
			//�p�b�N�}���̃A�j���[�V����
			{
				if (set == 3)
					set = gameptr->Coroutine(60);

				//�p�b�N�}���������Ă���Ȃ�G���؂�ւ�邩���߂ɃJ�E���^�����Z����
				if (BallMoveFlag == 1)
				{
					PackmanCounter++;

					//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
					//���ɖ߂��Ă�����
					if (PackmanCounter == 3)
					{
						//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
						if (set == 2 || set == 3)
							set = 0;
						else
							set++;

						PackmanCounter = 0;

					}
				}
			}

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
							//�e i �̈ʒu���Z�b�g�A�ʒu�̓p�b�N�}���̒��S�ɂ���
							ShotX[i] = (Bw - Sw) / 2 + PackmanX;
							ShotY[i] = (Bh - Sh) / 2 + PackmanY;

							//�e�̈ړ����x��ݒ肷��
							{
								double sb, sbx, sby, bx, by, sx, sy;

								//�e�̌���������Z�b�g
								sx = ShotX[i] + ShotW / 2;
								sy = ShotY[i] + ShotH / 2;

								bx = (double)gameptr->GetPosX() + (double)gameptr->GetEbw() / 2;
								by = (double)gameptr->GetPosY() + (double)gameptr->GetEbh() / 2;

								sbx = bx - sx;
								sby = by - sy;

								sb = sqrt(sbx * sbx + sby * sby);

								ShotSx = sbx / sb * ShotSpeed;
								ShotSy = sby / sb * ShotSpeed;

								//�e i�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
								ShotFlag[i] = 1;
								PlaySoundMem(ShotAudio, DX_PLAYTYPE_BACK);
								//������o�����̂ŋ����o�����[�v���甲���܂�
								break;
							}

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
		}

		//�p�b�N�}������ʍ��[����͂ݏo�������ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
		if (PackmanX < -64)PackmanX = gameptr->GetWidth();

		//�p�b�N�}������ʉE�[����͂ݏo�������ɂȂ������ʓ��ɖ߂��Ă�����
		if (PackmanX > gameptr->GetWidth())PackmanX = 0;

		// �p�b�N�}������ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
		if (PackmanY < -64)PackmanY = gameptr->GetHeight();
		// �p�b�N�}������ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
		if (PackmanY > gameptr->GetHeight())PackmanY = 0;

		DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, Packmanrotate, Packman[set], TRUE, PackmanReverse);
	}
}
void Player::ShotMove()
{
	for (i = 0; i < SHOT; i++)
	{
		//���@�̒e�P�̈ړ����[�`��(���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��1(���݂���)�̏ꍇ�̂ݍs��)
		if (ShotFlag[i] == 1)
		{
			//�ei��16�h�b�g��Ɉړ�������
			ShotX[i] += ShotSx;
			ShotY[i] += ShotSy;

			//��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
			if (ShotY[i] > gameptr->GetHeight() || ShotY[i] < 0 ||
				ShotX[i]>gameptr->GetWidth() || ShotX[i] < 0)
				ShotFlag[i] = 0;

			//�u�����L�[�Ƃ̓����蔻��
			if (((ShotX[i] > gameptr->GetPosX() && ShotX[i] < gameptr->GetPosX() + gameptr->GetEnemyW()) ||
				(gameptr->GetPosX() > ShotX[i] && gameptr->GetPosX() < ShotX[i] + ShotW)) &&
				((ShotY[i] > gameptr->GetPosY() && ShotY[i] < gameptr->GetPosY() + gameptr->GetEnemyH()) ||
					(gameptr->GetPosY() > ShotY[i] && gameptr->GetPosY() < ShotY[i] + ShotH)))
			{

				if (gameptr->GetDamageFlag() == 0)
					//�q�b�g�J�E���g�����Z����
					gameptr->EhitCount++;

				//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�󂯂Ă���x��\���P����
				gameptr->BlinkyDamageFlag = 1;

				PlaySoundMem(HitAudio, DX_PLAYTYPE_BACK);

				//�u�����L�[���_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
				gameptr->BlinkyDamageCounter = 0;

				//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
				ShotFlag[i] = 0;
			}
			//��ʂɒe i ��`�悷��
			DrawGraph((int)ShotX[i], (int)ShotY[i], ShotGraph, TRUE);
		}
	}
}
