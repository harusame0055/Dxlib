//#include"DxLib.h"
//#include "Player.h"
//#include"Enemy.h"
//#include<math.h>
//
//
//void Player_Initialization()
//{
//
//	//�p�b�N�}���̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
//	Packman[0] = LoadGraph("../Graphic/�p�b�N�}��1.png");
//	Packman[1] = LoadGraph("../Graphic/�p�b�N�}��2.png");
//	Packman[2] = LoadGraph("../Graphic/�p�b�N�}��3.png");
//	Packman[3] = LoadGraph("../Graphic/�p�b�N�}��4.png");
//	PackmanX = 320; PackmanY = 350; Packmanrotate = PI / 2;
//	PackmanCounter = 0;
//	PackmanReverse = 1;
//	PackmanMoveValue = 3;
//	//�p�b�N�}���������Ă��邩�ǂ����̕ϐ���(�����Ă��Ȃ�)��\��0����
//	BallMoveFlag = 0;
//	set = 0;
//
//
//	//�p�b�N�}���ƒe�̉摜�T�C�Y�𓾂�
//	GetGraphSize(Packman[set], &Bw, &Bh);
//	GetGraphSize(ShotGraph, &Sw, &Sh);
//
//	//�e�̃O���t�B�b�N���������Ƀ��[�h
//	ShotGraph = LoadGraph("../Graphic/Shot.png");
//
//	//�e�̃O���t�B�b�N�T�C�Y�𓾂�
//	GetGraphSize(ShotGraph, &ShotW, &ShotH);
//
//
//	//�e�P�E�Q����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����0�������Ă���
//	for (i = 0; i < SHOT; i++)
//	{
//		ShotFlag[i] = 0;
//	}
//
//	//�V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
//	ShotBFlag = 0;
//
//
//}
//
//void Player_Animation()
//	//�p�b�N�}���̃A�j���[�V����
//{
//	if (set == 3)
//		set = Coroutine(60);
//
//	//�p�b�N�}���������Ă���Ȃ�G���؂�ւ�邩���߂ɃJ�E���^�����Z����
//	if (BallMoveFlag == 1)
//	{
//		PackmanCounter++;
//
//		//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
//		//���ɖ߂��Ă�����
//		if (PackmanCounter == 3)
//		{
//			//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
//			if (set == 2 || set == 3)
//				set = 0;
//			else
//				set++;
//
//			PackmanCounter = 0;
//
//		}
//	}
//}
//
//void Player_Move()
//{
//
//
//	//�p�b�N�}���̑��샋�[�`��
//	{
//		//�p�b�N�}���̈ړ�����
//		{
//			// ���L�[�������Ă�����p�b�N�}������Ɉړ�������
//			if (CheckHitKey(KEY_INPUT_UP) == 1)
//			{
//				PackmanY -= PackmanMoveValue;
//				Packmanrotate = PI / 2;
//				BallMoveFlag = 1;
//				PackmanReverse = 1;
//			}
//			// ���L�[�������Ă�����p�b�N�}�������Ɉړ�������
//			else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
//			{
//				PackmanY += PackmanMoveValue;
//				BallMoveFlag = 1;
//				Packmanrotate = PI / 2;
//				PackmanReverse = 0;
//			}
//			// ���L�[�������Ă�����p�b�N�}�������Ɉړ�������
//			else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
//			{
//				PackmanX -= PackmanMoveValue;
//				BallMoveFlag = 1;
//				Packmanrotate = PI / 180;
//				PackmanReverse = 1;
//			}
//			// ���L�[�������Ă�����p�b�N�}�����E�Ɉړ�������
//			else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
//			{
//				PackmanX += PackmanMoveValue;
//				BallMoveFlag = 1;
//				Packmanrotate = PI;
//				PackmanReverse = 1;
//			}
//			else
//			{
//				BallMoveFlag = 0;
//			}
//		}
//		Bullet_Move();
//		//�p�b�N�}������ʍ��[����͂ݏo�������ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
//		if (PackmanX < -64)PackmanX = 640;
//
//		//�p�b�N�}������ʉE�[����͂ݏo�������ɂȂ������ʓ��ɖ߂��Ă�����
//		if (PackmanX > 640)PackmanX = 0;
//
//		// �p�b�N�}������ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
//		if (PackmanY < -64)PackmanY = 480;
//
//		// �p�b�N�}������ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
//		if (PackmanY > 480)PackmanY = 0;
//
//		DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, Packmanrotate, Packman[set], TRUE, PackmanReverse);
//	}
//
//}
//
//void Bullet_Move()
//{
//	//�X�y�[�X�L�[���������ꍇ�͏����𕪊�
//	if (CheckHitKey(KEY_INPUT_SPACE))
//	{
//
//		set = 3;
//		//�O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���0��������e�𔭎�
//		if (ShotBFlag == 0)
//		{
//			//��ʏ�ɏo�Ă��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
//			for (i = 0; i < SHOT; i++)
//			{
//				//�ei����ʏ�ɏo�Ă��Ȃ��ꍇ�͂��̒e����ʂɏo��
//				if (ShotFlag[i] == 0)
//				{
//					//�e i �̈ʒu���Z�b�g�A�ʒu�̓p�b�N�}���̒��S�ɂ���
//					ShotX[i] = (Bw - Sw) / 2 + PackmanX;
//					ShotY[i] = (Bh - Sh) / 2 + PackmanY;
//
//					//�e�̈ړ����x��ݒ肷��
//					{
//						double sb, sbx, sby, bx, by, sx, sy;
//
//						sx = ShotX[i] + ShotW / 2;
//						sy = ShotY[i] + ShotH / 2;
//
//						bx = BlinkyX + Ebw / 2;
//						by = BlinkyY + Ebh / 2;
//
//						sbx = bx - sx;
//						sby = by - sy;
//
//						sb = sqrt(sbx * sbx + sby * sby);
//
//						ShotSx = sbx / sb * 8;
//						ShotSy = sby / sb * 8;
//
//						//�e i�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
//						ShotFlag[i] = 1;
//
//						//������o�����̂ŋ����o�����[�v���甲���܂�
//						break;
//					}
//
//				}
//			}
//		}
//
//		//�O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂP�i������Ă����j����
//		ShotBFlag = 1;
//
//	}
//	else
//	{
//		//�V���b�g�{�^����������Ă��Ȃ������ꍇ��
//		//�O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
//		ShotBFlag = 0;
//
//	}
//
//}
//
//void Player_Bullet()
//{
//	//�e�̐������e�𓮂����������J��Ԃ�
//	for (i = 0; i < SHOT; i++)
//	{
//		//���@�̒e�P�̈ړ����[�`��(���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��1(���݂���)�̏ꍇ�̂ݍs��)
//		if (ShotFlag[i] == 1)
//		{
//			//�ei��16�h�b�g��Ɉړ�������
//			ShotX[i] += ShotSx;
//			ShotY[i] += ShotSy;
//
//			//��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
//			if (ShotY[i] > 480 || ShotY[i] < 0 ||
//				ShotX[i]>640 || ShotX[i] < 0)
//				ShotFlag[i] = 0;
//
//			//��ʂɒe i ��`�悷��
//			DrawGraph((int)ShotX[i], (int)ShotY[i], ShotGraph, TRUE);
//		}
//	}
//}
//
//int Coroutine(int time)
//{
//	int corTime = 0;
//	for (int i = 0; i < time; i++)
//	{
//		corTime++;
//		if (corTime == time)
//			break;
//	}
//	return 0;
//}