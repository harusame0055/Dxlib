#pragma once

class Game {

#pragma region �ϐ��錾
	//=======================
	// 	   �p�b�N�}���Ɏg���ϐ�
	int PackmanX, PackmanY, Packman[5], PackmanReverse;
	int PackmanCounter, BallMoveFlag;
	int PackmanDamageFlag, PackmanDamageCounter;

	int  PackmanMoveValue;		//�p�b�N�}���̈ړ��X�s�[�h
	int ShotSpeed;					//�e�̃X�s�[�h

	//�p�b�N�}���Ƀq�b�g�����J�E���g	
	int hitCount;

	double ShotX[SHOT], ShotY[SHOT];
	double ShotSx, ShotSy;
	int ShotFlag[SHOT], ShotGraph;

	//�摜�̕`��ύX
	int set = 0;

	//�p�b�N�}���ƒe�̉摜�T�C�Y
	int Bw, Bh, Sw, Sh;

	//===================================

	//===================================
	//�@�A�C�e���Ɏg�p����ϐ�
	int Item;
	int ItemX, ItemY;
	int ItemW, ItemH;
	int ItemFlag;
	int ItemCounter;
	//================================


	//================================
	// 	   �u�����L�[�̕ϐ�
	//�u�����L�[�ƒe�̉摜�T�C�Y
	int Ebw, Ebh, Esw, Esh;
	int BlinkyX, BlinkyY, BlinkyMuki, BlinkyGraph, Blinkyreverse, BlinkyMukiCounter;
	int BlinkyDamageFlag, BlinkyDamageCounter, BlinkyDamageGraph, BlinkyMoveValue;
	int ETamaSpeed = 0;

	int BlinkyW, BlinkyH, ShotW, ShotH;
	int ShotBFlag;
	int i;

	double ETamaX, ETamaY;
	double ETamaSx, ETamaSy;

	int ETamaFlag;

	int ETamaW, ETamaH, ETamaGraph;
	int ETamaCounter;


	//�u�����L�[�Ƀq�b�g�����J�E���g
	int EhitCount;

	//================================

	int white = GetColor(255, 255, 255);
	int yellow = GetColor(255, 255, 0);



	Fps fps;

#pragma endregion
	int sceneGraph[3];
	int Level;
	int Input;
	int Count;
	int AudioOneShot;
	int ShotAudio, HitAudio;
	int AudioSound[3];
	int PowerUpAudio;
	int ItemGet;
	int ItemGetCounter;

	float Packmanrotate;

public:
	void initialize();

	void Update();

	int Coroutine(int time);
};