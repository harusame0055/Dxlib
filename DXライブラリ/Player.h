#pragma once

#define PI 3.1415926535897932384626433832795f
#define SHOT 5
#define ITEM 5

#include"Game.h"

class Player {
	int PackmanX, PackmanY, Packman[5], PackmanReverse;
	int PackmanCounter, BallMoveFlag;
	int PackmanDamageFlag, PackmanDamageCounter;

	int  PackmanMoveValue;		//パックマンの移動スピード
	int ShotSpeed;					//弾のスピード

	double ShotX[SHOT], ShotY[SHOT];
	double ShotSx, ShotSy;
	int ShotFlag[SHOT], ShotGraph;

	//画像の描画変更
	int set = 0;

	//パックマンと弾の画像サイズ
	int Bw, Bh, Sw, Sh;
	float Packmanrotate;

	int ShotBFlag;
	int i;

	int  ShotW, ShotH;

	//パックマンにヒットしたカウント	
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
