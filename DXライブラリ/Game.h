#pragma once
#include "Fps.h"
class Game {

#pragma region �ϐ��錾

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

	int BlinkyX, BlinkyY;

	int Ebw, Ebh;

	int BlinkyW, BlinkyH;

	int Esw, Esh;
	int BlinkyMuki, BlinkyGraph, Blinkyreverse, BlinkyMukiCounter;
	int  BlinkyDamageGraph, BlinkyMoveValue;
	int ETamaSpeed = 0;

	int i;

	double ETamaX, ETamaY;
	double ETamaSx, ETamaSy;

	int ETamaFlag;

	int ETamaW, ETamaH, ETamaGraph;
	int ETamaCounter;


	static const int WindowWidth = 1024, WindowHeight = 480;

	//================================

	int white = GetColor(255, 255, 255);
	int yellow = GetColor(255, 255, 0);



	//�u�����L�[�Ƀq�b�g�����J�E���g
	int EhitCount;
	int BlinkyDamageFlag, BlinkyDamageCounter;

	int ShotAudio, HitAudio;

	int LoadScene;

	Fps fps;

#pragma endregion
	int sceneGraph[3];
	int Level;
	int Input;
	int Count;
	int AudioOneShot;
	int AudioSound[3];
	int PowerUpAudio;
	int ItemGet;
	int ItemGetCounter;

public:

	void initialize();
	void Update();
	void ShotPlayAudio();
	void EnemyHitCount() { EhitCount++; };
	void DamageFlag(int flag)
	{
		BlinkyDamageFlag = flag;
	};
	int GetDamageFlag() { return BlinkyDamageFlag; };

	void DamageCounter(int counter) { BlinkyDamageCounter = counter; };

	int Coroutine(int time);
	int GetWidth() { return WindowWidth; };
	int GetHeight() { return WindowHeight; };

	int GetPosX() { return BlinkyX; };
	int GetPosY() { return BlinkyY; };
	int GetEbw() { return Ebw; };
	int GetEbh() { return Ebh; };
	int GetEnemyW() { return BlinkyW; };
	int GetEnemyH() { return BlinkyH; };



};