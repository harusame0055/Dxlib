#pragma once
#include"DxLib.h"

class Fps {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	static const int N = 45;		//���ς����T���v����
	static const int FPS = 45;	//�ݒ肵��FPS

public:
	Fps();

	bool Update();

	void Draw();

	void Wait();
};
