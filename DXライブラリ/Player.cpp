#include"DxLib.h"
#include "Player.h"
#include"Enemy.h"
#include<math.h>

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
//void player_animation()
//	//�p�b�N�}���̃A�j���[�V����
//{
//	if (set == 3)
//		set = coroutine(60);
//
//	//�p�b�N�}���������Ă���Ȃ�G���؂�ւ�邩���߂ɃJ�E���^�����Z����
//	if (ballmoveflag == 1)
//	{
//		packmancounter++;
//
//		//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
//		//���ɖ߂��Ă�����
//		if (packmancounter == 3)
//		{
//			//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
//			if (set == 2 || set == 3)
//				set = 0;
//			else
//				set++;
//
//			packmancounter = 0;
//
//		}
//	}
//}
//
//void player_move()
//{
//
//
//	//�p�b�N�}���̑��샋�[�`��
//	{
//		//�p�b�N�}���̈ړ�����
//		{
//			// ���L�[�������Ă�����p�b�N�}������Ɉړ�������
//			if (checkhitkey(key_input_up) == 1)
//			{
//				packmany -= packmanmovevalue;
//				packmanrotate = pi / 2;
//				ballmoveflag = 1;
//				packmanreverse = 1;
//			}
//			// ���L�[�������Ă�����p�b�N�}�������Ɉړ�������
//			else if (checkhitkey(key_input_down) == 1)
//			{
//				packmany += packmanmovevalue;
//				ballmoveflag = 1;
//				packmanrotate = pi / 2;
//				packmanreverse = 0;
//			}
//			// ���L�[�������Ă�����p�b�N�}�������Ɉړ�������
//			else if (checkhitkey(key_input_left) == 1)
//			{
//				packmanx -= packmanmovevalue;
//				ballmoveflag = 1;
//				packmanrotate = pi / 180;
//				packmanreverse = 1;
//			}
//			// ���L�[�������Ă�����p�b�N�}�����E�Ɉړ�������
//			else if (checkhitkey(key_input_right) == 1)
//			{
//				packmanx += packmanmovevalue;
//				ballmoveflag = 1;
//				packmanrotate = pi;
//				packmanreverse = 1;
//			}
//			else
//			{
//				ballmoveflag = 0;
//			}
//		}
//		bullet_move();
//		//�p�b�N�}������ʍ��[����͂ݏo�������ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
//		if (packmanx < -64)packmanx = 640;
//
//		//�p�b�N�}������ʉE�[����͂ݏo�������ɂȂ������ʓ��ɖ߂��Ă�����
//		if (packmanx > 640)packmanx = 0;
//
//		// �p�b�N�}������ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
//		if (packmany < -64)packmany = 480;
//
//		// �p�b�N�}������ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
//		if (packmany > 480)packmany = 0;
//
//		drawrotagraph2(packmanx, packmany, 16, 16, 1, packmanrotate, packman[set], true, packmanreverse);
//	}
//
//}
//
//void bullet_move()
//{
//	//�X�y�[�X�L�[���������ꍇ�͏����𕪊�
//	if (checkhitkey(key_input_space))
//	{
//
//		set = 3;
//		//�O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���0��������e�𔭎�
//		if (shotbflag == 0)
//		{
//			//��ʏ�ɏo�Ă��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
//			for (i = 0; i < shot; i++)
//			{
//				//�ei����ʏ�ɏo�Ă��Ȃ��ꍇ�͂��̒e����ʂɏo��
//				if (shotflag[i] == 0)
//				{
//					//�e i �̈ʒu���Z�b�g�A�ʒu�̓p�b�N�}���̒��S�ɂ���
//					shotx[i] = (bw - sw) / 2 + packmanx;
//					shoty[i] = (bh - sh) / 2 + packmany;
//
//					//�e�̈ړ����x��ݒ肷��
//					{
//						double sb, sbx, sby, bx, by, sx, sy;
//
//						sx = shotx[i] + shotw / 2;
//						sy = shoty[i] + shoth / 2;
//
//						bx = blinkyx + ebw / 2;
//						by = blinkyy + ebh / 2;
//
//						sbx = bx - sx;
//						sby = by - sy;
//
//						sb = sqrt(sbx * sbx + sby * sby);
//
//						shotsx = sbx / sb * 8;
//						shotsy = sby / sb * 8;
//
//						//�e i�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
//						shotflag[i] = 1;
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
//		shotbflag = 1;
//
//	}
//	else
//	{
//		//�V���b�g�{�^����������Ă��Ȃ������ꍇ��
//		//�O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
//		shotbflag = 0;
//
//	}
//
//}
//
//void player_bullet()
//{
//	//�e�̐������e�𓮂����������J��Ԃ�
//	for (i = 0; i < shot; i++)
//	{
//		//���@�̒e�P�̈ړ����[�`��(���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��1(���݂���)�̏ꍇ�̂ݍs��)
//		if (shotflag[i] == 1)
//		{
//			//�ei��16�h�b�g��Ɉړ�������
//			shotx[i] += shotsx;
//			shoty[i] += shotsy;
//
//			//��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
//			if (shoty[i] > 480 || shoty[i] < 0 ||
//				shotx[i]>640 || shotx[i] < 0)
//				shotflag[i] = 0;
//
//			//��ʂɒe i ��`�悷��
//			drawgraph((int)shotx[i], (int)shoty[i], shotgraph, true);
//		}
//	}
//}
//
//int coroutine(int time)
//{
//	int cortime = 0;
//	for (int i = 0; i < time; i++)
//	{
//		cortime++;
//		if (cortime == time)
//			break;
//	}
//	return 0;
//}