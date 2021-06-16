#pragma once
#include "Fps.h"
class Game {

#pragma region 変数宣言

	//===================================
	//　アイテムに使用する変数
	int Item;
	int ItemX, ItemY;
	int ItemW, ItemH;
	int ItemFlag;
	int ItemCounter;
	//================================


	//================================
	// 	   ブリンキーの変数
	//ブリンキーと弾の画像サイズ

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



	//ブリンキーにヒットしたカウント
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