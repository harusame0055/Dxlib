#include"DxLib.h"
#include<math.h>
using namespace DxLib;

#define PI 3.1415926535897932384626433832795f

#define SHOT 5
#define ITEM 5


int WindowWidth = 1024, WindowHeight = 480;

int LoadScene;
// �ǉ��������
#include"Scene.h"
#include"Fps.h"
#include"Game.h"
#include"Player.h"

	//�^�C�g���ɏ�����
Scene scene = Title;
Game game;
Player player;

/// <summary>
/// �ϐ��̏������֐�
/// </summary>
void Game::initialize()
{
	sceneGraph[0] = LoadGraph("../Graphic/Title2.png");
	sceneGraph[1] = LoadGraph("../Graphic/�犪.jpg");
	sceneGraph[2] = LoadGraph("../Graphic/�s�k��.jpg");

	Level = 1;
	Input = 0;
	Count = 0;
	int WindowWidth = 1024, WindowHeight = 480;

	AudioOneShot = 0;

	ShotAudio = LoadSoundMem("../BGM/�V���b�g.mp3");
	HitAudio = LoadSoundMem("../BGM/�V���b�g����.mp3");
	PowerUpAudio = LoadSoundMem("../BGM/PowerUp.mp3");

	AudioSound[0] = LoadSoundMem("../BGM/�p�b�N�}��SE.mp3");
	AudioSound[1] = LoadSoundMem("../BGM/TETRIS.mp3");
	AudioSound[2] = LoadSoundMem("../BGM/�R�b�N�J���T�L.mp3");

	ItemGet = 0;
	ItemGetCounter = 0;


	Item = LoadGraph("../Graphic/Cherry.png");


	ItemX = GetRand(WindowWidth - 50) + 20;
	ItemY = GetRand(WindowHeight - 50) + 20;


	LoadScene = 0;

}
/// <summary>
/// �ق��̊֐����Ăяo�����߂̃A�b�v�f�[�g�֐�
/// </summary>
void Game::Update()
{
	switch (scene)
	{
	case Title:
	{
		if (AudioOneShot == 0)
		{
			AudioOneShot = 1;
			//PlaySoundFile("../BGM/  .mp3", DX_PLAYTYPE_NOMAL);
		}

		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();
		//�t�H���g�T�C�Y
		SetFontSize(40);
		DrawFormatString(250, 420, yellow, "LEVEL %d", Level);

		//�t�H���g�T�C�Y
		DrawGraph(0, 0, sceneGraph[0], TRUE);

		//�t�H���g�T�C�Y
		SetFontSize(20);
		DrawFormatString(10, 10, yellow, "Enter�������ƗV�ׂ܂�");

		fps.Update();	//�X�V
		fps.Draw();		//�`��
		fps.Wait();		//�ҋ@

		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_UP) == 1 && Input == 0)
		{
			if (Level < 3)
			{
				Input = 1;
				Level++;
			}
		}
		else	if (CheckHitKey(KEY_INPUT_DOWN) == 1 && Input == 0)
		{
			if (Level > 1)
			{
				Input = 1;
				Level--;
			}
		}
		else if (CheckHitKey(KEY_INPUT_RETURN) == 1 && Input == 0)
		{
#pragma region ������

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

			//�u�����L�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
			BlinkyGraph = LoadGraph("../Graphic/�u�����L�[.png");
			BlinkyX = 640; BlinkyY = 100; Blinkyreverse = FALSE;
			BlinkyMukiCounter = 0;

			switch (Level)
			{
			case 1:
				ETamaSpeed = 7;
				BlinkyMoveValue = 5;
				break;
			case 2:
				ETamaSpeed = 10;
				BlinkyMoveValue = 6;
				break;
			case 3:
				ETamaSpeed = 15;
				BlinkyMoveValue = 7;
				break;
			default:
				break;
			}

			//�e�̃O���t�B�b�N���������Ƀ��[�h
			ShotGraph = LoadGraph("../Graphic/Shot.png");

			//�u�����L�[�̃_���[�W���̃O���t�B�b�N���������Ƀ��[�h
			BlinkyDamageGraph = LoadGraph("../Graphic/�S�[�X�g.png");

			//�G�̒e�̃O���t�B�b�N�����[�h
			ETamaGraph = LoadGraph("../Graphic/EShot.png");

			//�e�̃O���t�B�b�N�T�C�Y�𓾂�
			GetGraphSize(ShotGraph, &ShotW, &ShotH);

			//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ����̕ϐ��Ɂw�󂯂Ă��Ȃ��x��\��0����
			BlinkyDamageFlag = 0;

			//�G�̒e�̃O���t�B�b�N�T�C�Y�𓾂�
			GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

			//�G�̒e�����ł��邩�ǂ�����ێ�����ϐ��Ɂw���ł��Ȃ��x��\���O����
			ETamaFlag = 0;

			//�G���e��ł^�C�~���O����邽�߂̌v���p�ϐ���0����
			ETamaCounter = 0;

			//ITEM�̃O���t�B�b�N�T�C�Y�𓾂�
			GetGraphSize(Item, &ItemW, &ItemH);

			//�e�P�E�Q����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����0�������Ă���
			for (i = 0; i < SHOT; i++)
			{
				ShotFlag[i] = 0;
			}

			ItemFlag = 0;
			//�V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ��ɂO�i������Ă��Ȃ��j����
			ShotBFlag = 0;

			//�u�����L�[�̈ړ��������Z�b�g
			BlinkyMuki = 1;

			//�u�����L�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
			GetGraphSize(BlinkyGraph, &BlinkyW, &BlinkyH);

			//�p�b�N�}���ƒe�̉摜�T�C�Y�𓾂�
			GetGraphSize(Packman[set], &Bw, &Bh);
			GetGraphSize(ShotGraph, &Sw, &Sh);

			//�u�����L�[�ƒe�̉摜�T�C�Y�𓾂�
			GetGraphSize(BlinkyGraph, &Ebw, &Ebh);
			GetGraphSize(ETamaGraph, &Esw, &Esh);

			hitCount = 0;
			EhitCount = 0;

			ItemCounter = 0;

#pragma endregion	

			LoadScene = 1;
			AudioOneShot = 0;
			scene = Load;
		}
		else
		{
			Count++;
			if (Count == 10)
			{
				Input = 0;

				Count = 0;
			}
		}
	}
	break;
	case MainGame:
	{
		//�t�H���g�T�C�Y
		SetFontSize(20);

		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();
		//�p�b�N�}���̑��샋�[�`��
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
						set = game.Coroutine(60);

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

									sx = ShotX[i] + ShotW / 2;
									sy = ShotY[i] + ShotH / 2;

									bx = BlinkyX + Ebw / 2;
									by = BlinkyY + Ebh / 2;

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
			if (PackmanX < -64)PackmanX = WindowWidth;

			//�p�b�N�}������ʉE�[����͂ݏo�������ɂȂ������ʓ��ɖ߂��Ă�����
			if (PackmanX > WindowWidth)PackmanX = 0;

			// �p�b�N�}������ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (PackmanY < -64)PackmanY = WindowHeight;

			// �p�b�N�}������ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (PackmanY > WindowHeight)PackmanY = 0;

			DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, Packmanrotate, Packman[set], TRUE, PackmanReverse);
		}

		//�e�̐������e�𓮂����������J��Ԃ�
		for (i = 0; i < SHOT; i++)
		{
			//���@�̒e�P�̈ړ����[�`��(���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��1(���݂���)�̏ꍇ�̂ݍs��)
			if (ShotFlag[i] == 1)
			{
				//�ei��16�h�b�g��Ɉړ�������
				ShotX[i] += ShotSx;
				ShotY[i] += ShotSy;

				//��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���0�i���݂��Ȃ��j��������
				if (ShotY[i] > WindowHeight || ShotY[i] < 0 ||
					ShotX[i]>WindowWidth || ShotX[i] < 0)
					ShotFlag[i] = 0;

				//��ʂɒe i ��`�悷��
				DrawGraph((int)ShotX[i], (int)ShotY[i], ShotGraph, TRUE);
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

				BlinkyMukiCounter++;
				if (BlinkyMukiCounter == 30)
				{
					BlinkyMuki = GetRand(3);
					BlinkyMukiCounter = 0;
				}

				if (BlinkyMuki == 0)
				{
					BlinkyX += BlinkyMoveValue;
					Blinkyreverse = TRUE;
				}
				else if (BlinkyMuki == 1)
				{
					BlinkyX -= BlinkyMoveValue;
					Blinkyreverse = FALSE;
				}
				else if (BlinkyMuki == 2)
					BlinkyY += BlinkyMoveValue;
				else if (BlinkyMuki == 3)
					BlinkyY -= BlinkyMoveValue;

				//�u�����L�[����ʉE�[����o���甽�Α�����o��������
				if (BlinkyX > WindowWidth)
				{
					BlinkyX = WindowWidth;
					Blinkyreverse = FALSE;
				}
				// �u�����L�[����ʍ��[����o���甽�Α�����o��������
				if (BlinkyX < 0)
				{
					BlinkyX = 0;
					Blinkyreverse = TRUE;
				}

				//�u�����L�[����ʉE�[����o���甽�Α�����o��������
				if (BlinkyY > WindowHeight)
				{
					BlinkyY = 0;
				}
				// �u�����L�[����ʍ��[����o���甽�Α�����o��������
				if (BlinkyY < 0)
				{
					BlinkyY = WindowHeight;
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

						//�e�̈ړ����x��ݒ肷��
						{
							double sb, sbx, sby, bx, by, sx, sy;

							sx = ETamaX + ETamaW / 2;
							sy = ETamaY + ETamaH / 2;

							bx = PackmanX + Bw / 2;
							by = PackmanY + Bh / 2;

							sbx = bx - sx;
							sby = by - sy;

							//�����������߂�̂ɕW���֐���sqrt���g���A
							//��������ɂ�math.h���C���N���[�h����K�v������
							sb = sqrt(sbx * sbx + sby * sby);

							//�P�t���[��������W�h�b�g�ړ�����悤�ɂ���
							ETamaSx = sbx / sb * ETamaSpeed;
							ETamaSy = sby / sb * ETamaSpeed;

							PlaySoundMem(ShotAudio, DX_PLAYTYPE_BACK);
						}

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
			//�e���ړ�������
			ETamaX += ETamaSx;
			ETamaY += ETamaSy;

			//�����e����ʉ��[����͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
			//��\���O�ɂ���
			if (ETamaY > WindowHeight || ETamaY < 0 ||
				ETamaX>WindowWidth || ETamaX < 0)ETamaFlag = 0;

			//�p�b�N�}���Ƃ̓����蔻��
			if (((ETamaX > PackmanX && ETamaX < PackmanX + Bw) ||
				(PackmanX > ETamaX && PackmanX < ETamaX + ETamaW)) &&
				((ETamaY > PackmanY && ETamaY < PackmanY + Bh) ||
					(PackmanY > ETamaY && PackmanY < ETamaY + ETamaH)))
			{
				if (PackmanDamageFlag == 0)
					//�q�b�g�J�E���g�����Z����
					hitCount++;

				//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�󂯂Ă���x��\���P����
				PackmanDamageFlag = 1;
				PlaySoundMem(HitAudio, DX_PLAYTYPE_BACK);

				//�u�����L�[���_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
				PackmanDamageCounter = 0;

				//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
				ETamaFlag = 0;

			}
			//��ʂɕ`�悷��(ETamaGraph :�G�̒e�̃O���t�B�b�N�̃n���h��)
			DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
		}

#pragma region �A�C�e���֘A

		if (ItemFlag == 0)
		{
			ItemCounter++;
			if (ItemCounter == 1000)
			{
				ItemFlag = 1;
				ItemCounter = 0;
			}
		}

		if (ItemFlag == 1)
		{
			DrawGraph(ItemX, ItemY, Item, TRUE);

			if (((ItemX > PackmanX && ItemX < PackmanX + Bw) ||
				(PackmanX > ItemX && PackmanX < ItemX + ItemW)) &&
				((ItemY > PackmanY && ItemY < PackmanY + Bh) ||
					(PackmanY > ItemY && PackmanY < ItemY + ItemH)))
			{
				Item = 0;

				ItemGet = 1;

				StopSoundMem(AudioSound[1]);
			}
		}

		if (ItemGet == 1)
		{
			if (ItemGet == 1)
			{
				PackmanMoveValue = 10;
				ItemGetCounter = 1;

				if (CheckSoundMem(PowerUpAudio) == 0)
				{
					PackmanMoveValue = 5;
				}
				else
					ItemGetCounter = 0;
			}
		}

#pragma endregion

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

					if (BlinkyDamageFlag == 0)
						//�q�b�g�J�E���g�����Z����
						EhitCount++;
					PlaySoundMem(HitAudio, DX_PLAYTYPE_BACK);

					//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�󂯂Ă���x��\���P����
					BlinkyDamageFlag = 1;

					//�u�����L�[���_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
					BlinkyDamageCounter = 0;
				}
			}
		}
		DrawFormatString(0, 0, white, "�u�����L�[�ɂ��Ă��� : %d \n ���������� : %d", EhitCount, hitCount);
		DrawFormatString(850, 0, white, "space :�e�𔭎� \n�\���L�[ : �ړ�");

		fps.Update();	//�X�V
		fps.Draw();		//�`��
		fps.Wait();		//�ҋ@

		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		//BGM�̏���
		if (AudioOneShot == 0)
		{
			AudioOneShot = 1;
			PlaySoundMem(AudioSound[0], DX_PLAYTYPE_NORMAL);
			PlaySoundMem(AudioSound[1], DX_PLAYTYPE_BACK);
		}
		if (ItemGetCounter == 1 && CheckSoundMem(AudioSound[1]) == 0)
		{
			PlaySoundMem(PowerUpAudio, DX_PLAYTYPE_BACK);
		}
		if (CheckSoundMem(PowerUpAudio) == 0 && CheckSoundMem(AudioSound[1]) == 0)
		{
			PlaySoundMem(AudioSound[1], DX_PLAYTYPE_BACK);
		}

		if (EhitCount == 25)
		{
			LoadScene = 2;
			scene = Load;
			StopSoundMem(AudioSound[1]);
			AudioOneShot = 0;
		}
		else if (EhitCount == 15)
		{
			switch (Level)
			{
			case 1:
				ETamaSpeed = 12;
				BlinkyMoveValue = 5;
				break;
			case 2:
				ETamaSpeed = 15;
				BlinkyMoveValue = 6;
				break;
			case 3:
				ETamaSpeed = 17;
				BlinkyMoveValue = 7;
				break;
			default:
				break;
			}

		}
		else if (hitCount == 10)
		{
			LoadScene = 3;
			AudioOneShot = 0;
			StopSoundMem(AudioSound[1]);
			scene = Load;
		}
	}
	break;
	case GameClear:
	{
		if (AudioOneShot == 0)
		{
			AudioOneShot = 1;
		}
		DrawGraph(0, 50, sceneGraph[1], TRUE);
		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_RETURN) == 1)
		{
			LoadScene = 0;
			AudioOneShot = 0;
			scene = Load;
		}

	}
	break;
	case GameOver:
	{
		if (AudioOneShot == 0)
		{
			PlaySoundMem(AudioSound[2], DX_PLAYTYPE_NORMAL);
			AudioOneShot = 1;
		}
		DrawGraph(0, 50, sceneGraph[2], TRUE);
		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_RETURN) == 1)
		{
			LoadScene = 0;
			scene = Load;
			Input = 1;
		}
	}
	break;
	case Load:
	{
		Count++;

		fps.Update();	//�X�V
		fps.Draw();		//�`��
		fps.Wait();		//�ҋ@

		if (Count == 50)
		{
			scene = Scene(LoadScene);

			Count = 0;
		}
	}
	break;
	default:
		break;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{

#pragma region DxLib�̏�����

	//��ʃ��[�h�̐ݒ�
	SetGraphMode(WindowWidth, WindowHeight, 16);
	ChangeWindowMode(true);
	//�O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g

	SetDrawScreen(DX_SCREEN_BACK);

	//DX���C�u��������������
	if (DxLib_Init() == -1)	return -1;
#pragma endregion

	//�ϐ��̏���������
	game.initialize();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�A�b�v�f�[�g�֐����g���v���C���[��A�G�̓������Ăяo��
		game.Update();

		
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

/// <summary>
///		�w�肵���b���ҋ@���A�O�̒l��Ԃ��R���[�`���֐�
/// </summary>
/// <param name="time"></param>
/// <returns></returns>
int Game::Coroutine(int time)
{
	int corTime = 0;
	for (int i = 0; i < time; i++)
	{
		corTime++;
		if (corTime == time)
			break;
	}
	return 0;
}
