#pragma once

class Game {

#pragma region 変数宣言
	//=======================
	// 	   パックマンに使う変数
	int PackmanX, PackmanY, Packman[5], PackmanReverse;
	int PackmanCounter, BallMoveFlag;
	int PackmanDamageFlag, PackmanDamageCounter;

	int  PackmanMoveValue;		//パックマンの移動スピード
	int ShotSpeed;					//弾のスピード

	//パックマンにヒットしたカウント	
	int hitCount;

	double ShotX[SHOT], ShotY[SHOT];
	double ShotSx, ShotSy;
	int ShotFlag[SHOT], ShotGraph;

	//画像の描画変更
	int set = 0;

	//パックマンと弾の画像サイズ
	int Bw, Bh, Sw, Sh;

	//===================================

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


	//ブリンキーにヒットしたカウント
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