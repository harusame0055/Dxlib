#pragma once
#include"DxLib.h"

class Fps {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 45;		//平均を取るサンプル数
	static const int FPS = 45;	//設定したFPS

public:
	Fps();

	bool Update();

	void Draw();

	void Wait();
};
