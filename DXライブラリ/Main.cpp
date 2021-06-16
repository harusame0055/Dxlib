#include"DxLib.h"
#include<math.h>
using namespace DxLib;

// �ǉ��������
#include"Scene.h"
#include"Fps.h"
#include"Game.h"
#include"Player.h"

	//�^�C�g���ɏ�����
Scene scene;
Player player;
/// <summary>
/// �ϐ��̏������֐�
/// </summary>
void Game::initialize()
{
	sceneGraph[0] = LoadGraph("../Graphic/Title2.png");
	sceneGraph[1] = LoadGraph("../Graphic/GameClear.png");
	sceneGraph[2] = LoadGraph("../Graphic/GameOver.png");

	Level = 1;
	Input = 0;
	Count = 0;

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


	//�u�����L�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	BlinkyGraph = LoadGraph("../Graphic/�u�����L�[.png");
	BlinkyX = 640; BlinkyY = 100; Blinkyreverse = FALSE;
	BlinkyMukiCounter = 0;

	BlinkyDamageCounter = 0;

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

			player.initialize();

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

			//�u�����L�[�̃_���[�W���̃O���t�B�b�N���������Ƀ��[�h
			BlinkyDamageGraph = LoadGraph("../Graphic/�S�[�X�g.png");

			//�G�̒e�̃O���t�B�b�N�����[�h
			ETamaGraph = LoadGraph("../Graphic/EShot.png");



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


			ItemFlag = 0;

			//�u�����L�[�̈ړ��������Z�b�g
			BlinkyMuki = 1;

			//�u�����L�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
			GetGraphSize(BlinkyGraph, &BlinkyW, &BlinkyH);

			//�u�����L�[�ƒe�̉摜�T�C�Y�𓾂�
			GetGraphSize(BlinkyGraph, &Ebw, &Ebh);
			GetGraphSize(ETamaGraph, &Esw, &Esh);

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
		player.PlayerMove();

		//�u�����L�[�̈ړ����[�`��
		{
			//�_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
			if (BlinkyDamageFlag == 1)
			{
				//�_���[�W���󂯂Ă���ꍇ�̓_���[�W�O���t�B�b�N��`�悷��
				DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyDamageGraph, TRUE, Blinkyreverse);
				//�_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�[��1�����Z����
				BlinkyDamageCounter++;

				//		//�����_���[�W���󂯎n�߂ĂR�O�t���[���o�߂��Ă�����_���[�W��Ԃ���
				//		//���ɖ߂��Ă�����
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

							bx = player.GetPosX() + player.GetBw() / 2;
							by = player.GetPosY() + player.GetBh() / 2;

							sbx = bx - sx;
							sby = by - sy;

							//�����������߂�̂ɕW���֐���sqrt���g���A
							//��������ɂ�math.h���C���N���[�h����K�v������
							sb = sqrt(sbx * sbx + sby * sby);

							//�P�t���[��������W�h�b�g�ړ�����悤�ɂ���
							ETamaSx = sbx / sb * ETamaSpeed;
							ETamaSy = sby / sb * ETamaSpeed;
							ShotPlayAudio();
						}

						//�e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
						ETamaFlag = 1;
					}
					//�e��ł^�C�~���O���v�����邽�߂̕ϐ��ɂO����
					ETamaCounter = 0;
				}
			}
		}

		//�e�̐������e�𓮂����������J��Ԃ�
		player.ShotMove();

		//�e�ƓG�̓����蔻��A�e�̐������J��Ԃ�
		//player.ShotHitCheck();

		//�G�̒e�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
		if (ETamaFlag == 1)
		{
			//�e���ړ�������
			ETamaX += ETamaSx;
			ETamaY += ETamaSy;

			//�����e����ʉ��[����͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
			//��\���O�ɂ���
			if (ETamaY > WindowHeight || ETamaY < 0 ||
				ETamaX>WindowWidth || ETamaX < 0)
				ETamaFlag = 0;

			//�p�b�N�}���Ƃ̓����蔻��
			if (((ETamaX > player.GetPosX() && ETamaX < player.GetPosX() + player.GetBw()) ||
				(player.GetPosX() > ETamaX && player.GetPosX() < ETamaX + ETamaW)) &&
				((ETamaY > player.GetPosY() && ETamaY < player.GetPosY() + player.GetBh()) ||
					(player.GetPosY() > ETamaY && player.GetPosY() < ETamaY + ETamaH)))
			{
				if (player.GetDamageFlag() == 0)
					//�q�b�g�J�E���g�����Z����
					player.HitCount();

				//�u�����L�[���_���[�W���󂯂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�󂯂Ă���x��\���P����
				player.DamegeFlag(1);

				PlaySoundMem(HitAudio, DX_PLAYTYPE_BACK);

				//�u�����L�[���_���[�W���󂯂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
				player.DamageCounter(0);

				//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
				ETamaFlag = 0;

			}
			//��ʂɕ`�悷��(ETamaGraph :�G�̒e�̃O���t�B�b�N�̃n���h��)
			DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
		}

		//player.ItemGeneration();


		DrawFormatString(0, 0, white, "�u�����L�[�ɂ��Ă��� : %d \n ���������� : %d", BlinkyDamageCounter, BlinkyDamageFlag);
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
		else if (player.GetHitCount() == 10)
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
		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

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
		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		if (AudioOneShot == 0)
		{
			PlaySoundMem(AudioSound[2], DX_PLAYTYPE_BACK);
			AudioOneShot = 1;
		}
		DrawGraph(0, 0, sceneGraph[2], TRUE);
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

		//��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		fps.Update();	//�X�V
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

void Game::ShotPlayAudio()
{
	PlaySoundMem(ShotAudio, DX_PLAYTYPE_BACK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
	Game game;

#pragma region DxLib�̏�����

	//��ʃ��[�h�̐ݒ�
	SetGraphMode(game.GetWidth(), game.GetHeight(), 16);
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

		//�v���C���[��game�ւ̎Q�Ƃ��Z�b�g
		player.SetGame(game);

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
