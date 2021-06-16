#pragma once

#define PI 3.1415926535897932384626433832795f
#define SHOT 5
#define ITEM 5

#include"Game.h"

class Player {
	int PackmanX, PackmanY, Packman[5], PackmanReverse;
	int PackmanCounter, BallMoveFlag;
	int PackmanDamageFlag, PackmanDamageCounter;

	int  PackmanMoveValue;		//�p�b�N�}���̈ړ��X�s�[�h
	int ShotSpeed;					//�e�̃X�s�[�h

	double ShotX[SHOT], ShotY[SHOT];
	double ShotSx, ShotSy;
	int ShotFlag[SHOT], ShotGraph;

	//�摜�̕`��ύX
	int set = 0;

	//�p�b�N�}���ƒe�̉摜�T�C�Y
	int Bw, Bh, Sw, Sh;
	float Packmanrotate;

	int ShotBFlag;
	int i;

	int  ShotW, ShotH;

	//�p�b�N�}���Ƀq�b�g�����J�E���g	
	int hitCount;

	int ShotAudio, HitAudio;

	Game game;

public:

	Player() = default;

	void SetGame(Game& g);

	void initialize();
	void PlayerMove();
	void ShotMove();

	int GetPosX() { return PackmanX; };
	int GetPosY() { return PackmanY; };
	int GetBw() { return Bw; };
	int GetBh() { return Bh; };
	int GetDamageFlag() { return PackmanDamageFlag; };
	int GetHitCount() { return hitCount; };

	void HitCount() { hitCount++; };
	void DamegeFlag(int flag) { PackmanDamageFlag = flag; };
	void DamageCounter(int counter) { PackmanDamageCounter = counter; };

	void ShotHitCheck();

};
