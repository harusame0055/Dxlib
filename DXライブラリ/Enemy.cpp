//#include"DxLib.h"
//#include "Player.h"
//#include"Enemy.h"
//#include<math.h>
//
//void Enemy_Initialization()
//{
//
//	//�u�����L�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
//	BlinkyGraph = LoadGraph("../Graphic/�u�����L�[.png");
//	BlinkyX = 640; BlinkyY = 100; Blinkyreverse = FALSE;
//	BlinkyMoveValue = 2;
//
//	//�u�����L�[�̃_���[�W���̃O���t�B�b�N���������Ƀ��[�h
//	BlinkyDamageGraph = LoadGraph("../Graphic/�S�[�X�g.png");
//
//	//�G�̒e�̃O���t�B�b�N�����[�h
//	ETamaGraph = LoadGraph("../Graphic/EShot.png");
//
//	//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ����̕ϐ��Ɂw�󂯂Ă��Ȃ��x��\��0����
//	BlinkyDamageFlag = 0;
//
//	//�G�̒e�̃O���t�B�b�N�T�C�Y�𓾂�
//	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);
//
//	//�G�̒e�����ł��邩�ǂ�����ێ�����ϐ��Ɂw���ł��Ȃ��x��\���O����
//	ETamaFlag = 0;
//
//	//�G���e��ł^�C�~���O����邽�߂̌v���p�ϐ���0����
//	ETamaCounter = 0;
//	//�u�����L�[�̈ړ��������Z�b�g
//	BlinkyMuki = 1;
//
//
//	//�u�����L�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
//	GetGraphSize(BlinkyGraph, &BlinkyW, &BlinkyH);
//
//	//�u�����L�[�ƒe�̉摜�T�C�Y�𓾂�
//	GetGraphSize(BlinkyGraph, &Ebw, &Ebh);
//	GetGraphSize(ETamaGraph, &Esw, &Esh);
//
//}
//
//void Enemy_Move()
//{
//	//�_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
//	if (BlinkyDamageFlag == 1)
//	{
//		//�_���[�W���󂯂Ă���ꍇ�̓_���[�W�O���t�B�b�N��`�悷��
//		DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyDamageGraph, TRUE, Blinkyreverse);
//		//�_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�[��1�����Z����
//		BlinkyDamageCounter++;
//
//		//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
//		//���ɖ߂��Ă�����
//		if (BlinkyDamageCounter == 30)
//		{
//			//�w�_���[�W���󂯂Ă��Ȃ��x��\���O����
//			BlinkyDamageFlag = 0;
//		}
//	}
//	else
//	{
//		//�u�����L�[�̍��W���ړ����Ă�������Ɉړ�����
//		if (BlinkyMuki == 1)BlinkyX += BlinkyMoveValue;
//		if (BlinkyMuki == 0)BlinkyX -= BlinkyMoveValue;
//
//		//�u�����L�[����ʉE�[����o�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
//		if (BlinkyX > 640)
//		{
//			BlinkyX = 640;
//			BlinkyMuki = 0;
//			Blinkyreverse = FALSE;
//		}
//
//		// �u�����L�[����ʍ��[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
//		if (BlinkyX < 0)
//		{
//			BlinkyX = 0;
//			BlinkyMuki = 1;
//			Blinkyreverse = TRUE;
//		}
//
//		// �u�����L�[��`��
//		DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyGraph, TRUE, Blinkyreverse);
//
//		//�e��ł^�C�~���O���v�����邽�߂̃J�E���^�[�ɂP�������Z
//		ETamaCounter++;
//
//		//�����J�E���^�[�ϐ����U�O�������ꍇ�͒e��ł������s��
//		if (ETamaCounter == 60)
//		{
//			//�������łɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
//			if (ETamaFlag == 0)
//			{
//				//�e�̔��ˈʒu��ݒ肷��
//				ETamaX = BlinkyX + BlinkyW / 2 - ETamaW / 2;
//				ETamaY = BlinkyY + BlinkyH / 2 - ETamaH / 2;
//
//				//�e�̈ړ����x��ݒ肷��
//				{
//					double sb, sbx, sby, bx, by, sx, sy;
//
//					sx = ETamaX + ETamaW / 2;
//					sy = ETamaY + ETamaH / 2;
//
//					bx = PackmanX + Bw / 2;
//					by = PackmanY + Bh / 2;
//
//					sbx = bx - sx;
//					sby = by - sy;
//
//					//�����������߂�̂ɕW���֐���sqrt���g���A
//					//��������ɂ�math.h���C���N���[�h����K�v������
//					sb = sqrt(sbx * sbx + sby * sby);
//
//					//�P�t���[��������W�h�b�g�ړ�����悤�ɂ���
//					ETamaSx = sbx / sb * 8;
//					ETamaSy = sby / sb * 8;
//				}
//
//				//�e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
//				ETamaFlag = 1;
//
//			}
//			//�e��ł^�C�~���O���v�����邽�߂̕ϐ��ɂO����
//			ETamaCounter = 0;
//		}
//
//	}
//}
//
//void Enemy_Bullet()
//{
//
//	//�G�̒e�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
//	if (ETamaFlag == 1)
//	{
//		//�e���ړ�������
//		ETamaX += ETamaSx;
//		ETamaY += ETamaSy;
//
//		//�����e����ʉ��[����͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
//		//��\���O�ɂ���
//		if (ETamaY > 480 || ETamaY < 0 ||
//			ETamaX>640 || ETamaX < 0)ETamaFlag = 0;
//
//		//�u�����L�[�Ƃ̓����蔻��
//		if (((ETamaX > PackmanX && ETamaX < PackmanX + Bw) ||
//			(PackmanX > ETamaX && PackmanX < ETamaX + ETamaW)) &&
//			((ETamaY > PackmanY && ETamaY < PackmanY + Bh) ||
//				(PackmanY > ETamaY && PackmanY < ETamaY + ETamaH)))
//		{
//			//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
//			ETamaFlag = 0;
//
//			//�q�b�g�J�E���g�����Z����
//			hitCount++;
//		}
//
//		//��ʂɕ`�悷��(ETamaGraph :�G�̒e�̃O���t�B�b�N�̃n���h��)
//		DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
//	}
//
//
//	//�e�ƓG�̓����蔻��A�e�̐������J��Ԃ�
//	for (i = 0; i < SHOT; i++)
//	{
//		//�ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
//		if (ShotFlag[i] == 1)
//		{
//			//�u�����L�[�Ƃ̓����蔻��
//			if (((ShotX[i] > BlinkyX && ShotX[i] < BlinkyX + BlinkyW) ||
//				(BlinkyX > ShotX[i] && BlinkyX < ShotX[i] + ShotW)) &&
//				((ShotY[i] > BlinkyY && ShotY[i] < BlinkyY + BlinkyH) ||
//					(BlinkyY > ShotY[i] && BlinkyY < ShotY[i] + ShotH)))
//			{
//				//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
//				ShotFlag[i] = 0;
//
//				if (BlinkyDamageFlag == 0)
//					//�q�b�g�J�E���g�����Z����
//					EhitCount++;
//
//				//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�󂯂Ă���x��\���P����
//				BlinkyDamageFlag = 1;
//
//				//�u�����L�[���_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
//				BlinkyDamageCounter = 0;
//
//
//			}
//		}
//	}
//
//}