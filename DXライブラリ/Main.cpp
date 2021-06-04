#include"DxLib.h"
#include<math.h>
#include"Player.h"
#include"Enemy.h"
using namespace DxLib;

#define PI 3.1415926535897932384626433832795f
#define SHOT 5
#define SHOTSPEED 10;
int Coroutine(int time);
int SeceneGraph[4];

enum Scene
{
	Title,
	Main,
	GameClear,
	GameOver,
};

class Fps {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 45;//平均を取るサンプル数
	static const int FPS = 45;	//設定したFPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60フレーム目なら平均を計算する
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw() {
		DrawFormatString(600, 460, GetColor(255, 255, 255), "%.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
#pragma region 変数宣言
	int PackmanX, PackmanY, Packman[5], PackmanReverse;
	int PackmanCounter, BallMoveFlag, PackmanMoveValue;
	int PackmanDamageFlag, PackmanDamageCounter;

	int hitCount;
	int EhitCount;

	//パックマンと弾の画像サイズ
	int Bw, Bh, Sw, Sh;

	//ブリンキーと弾の画像サイズ
	int Ebw, Ebh, Esw, Esh;
	int set = 0;

	int BlinkyX, BlinkyY, BlinkyMuki, BlinkyGraph, Blinkyreverse;
	int BlinkyDamageFlag, BlinkyDamageCounter, BlinkyDamageGraph, BlinkyMoveValue;

	double ShotX[SHOT], ShotY[SHOT];
	double ShotSx, ShotSy;


	int ShotFlag[SHOT], ShotGraph;

	int BlinkyW, BlinkyH, ShotW, ShotH;
	int ShotBFlag;
	int i;

	double ETamaX, ETamaY;
	double ETamaSx, ETamaSy;

	int ETamaFlag;

	int ETamaW, ETamaH, ETamaGraph;
	int ETamaCounter;

	int white = GetColor(255, 255, 255);
	int yellow = GetColor(255, 255, 0);

	Fps fps;

#pragma endregion

#pragma region DxLibの初期化
	//画面モードの設定
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);
	SetBackgroundColor(0, 120, 138);


	//DXライブラリ初期化処理
	if (DxLib_Init() == -1)	return -1;

	float Packmanrotate;

	//グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

#pragma endregion


#pragma region 初期化
	//タイトルに初期化
	Scene scene = Title;
	SeceneGraph[0]= LoadGraph("../Graphic/五条悟.jpg");


	//パックマンのグラフィックをメモリにロード＆表示座標をセット
	Packman[0] = LoadGraph("../Graphic/パックマン1.png");
	Packman[1] = LoadGraph("../Graphic/パックマン2.png");
	Packman[2] = LoadGraph("../Graphic/パックマン3.png");
	Packman[3] = LoadGraph("../Graphic/パックマン4.png");
	Packman[4] = LoadGraph("../Graphic/ダメージパックマン.png");
	PackmanDamageFlag = 0;

	PackmanX = 320; PackmanY = 350; Packmanrotate = PI / 2;
	PackmanCounter = 0;
	PackmanReverse = 1;
	PackmanMoveValue = 3;
	//パックマンが動いているかどうかの変数に(動いていない)を表す0を代入
	BallMoveFlag = 0;

	//ブリンキーのグラフィックをメモリにロード＆表示座標をセット
	BlinkyGraph = LoadGraph("../Graphic/ブリンキー.png");
	BlinkyX = 640; BlinkyY = 100; Blinkyreverse = FALSE;
	BlinkyMoveValue = 2;


	//弾のグラフィックをメモリにロード
	ShotGraph = LoadGraph("../Graphic/Shot.png");

	//ブリンキーのダメージ時のグラフィックをメモリにロード
	BlinkyDamageGraph = LoadGraph("../Graphic/ゴースト.png");

	//敵の弾のグラフィックをロード
	ETamaGraph = LoadGraph("../Graphic/EShot.png");


	//弾のグラフィックサイズを得る
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//ブリンキーがダメージを受けているかどうかの変数に『受けていない』を表す0を代入
	BlinkyDamageFlag = 0;

	//敵の弾のグラフィックサイズを得る
	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

	//敵の弾が飛んでいるかどうかを保持する変数に『飛んでいない』を表す０を代入
	ETamaFlag = 0;

	//敵が弾を打つタイミングを取るための計測用変数に0を代入
	ETamaCounter = 0;



	//弾１・２が画面上に存在しているか保持する変数に『存在していない』を意味する0を代入しておく
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	//ショットボタンが前のフレームで押されたかどうかを保存する変数に０（押されていない）を代入
	ShotBFlag = 0;

	//ブリンキーの移動方向をセット
	BlinkyMuki = 1;


	//ブリンキーのグラフィックのサイズを得る
	GetGraphSize(BlinkyGraph, &BlinkyW, &BlinkyH);

	//パックマンと弾の画像サイズを得る
	GetGraphSize(Packman[set], &Bw, &Bh);
	GetGraphSize(ShotGraph, &Sw, &Sh);

	//ブリンキーと弾の画像サイズを得る
	GetGraphSize(BlinkyGraph, &Ebw, &Ebh);
	GetGraphSize(ETamaGraph, &Esw, &Esh);


	hitCount = 0;
	EhitCount = 0;
#pragma endregion

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		switch (scene)
		{
		case Title:
		{
			//フォントサイズ
			DrawGraph(0, 0, SeceneGraph[0], TRUE);
			//フォントサイズ
			SetFontSize(20);
			DrawFormatString(250, 240, white, "Enterを押すと遊べます");
			// 裏画面の内容を表画面にコピーする
			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_RETURN) == 1)
			{
				scene = Main;
			}
		}

		break;
		case Main:
		{
			//フォントサイズ
			SetFontSize(20);


			//画面を初期化(真っ黒にする)
			ClearDrawScreen();

			//パックマンの操作ルーチン
			{
				//ダメージを受けているかどうかで処理を分岐
				if (PackmanDamageFlag == 1)
				{
					set = 4;

					//ダメージを受けている場合はダメージグラフィックを描画する
					DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, Packman[set], TRUE, PackmanReverse);
					//ダメージを受けている時間を測るカウンターに1を加算する
					PackmanDamageCounter++;

					//もしダメージを受け始めて３０フレーム経過していたらダメージ状態から
					//元に戻してあげる
					if (PackmanDamageCounter == 30)
					{
						//『ダメージを受けていない』を表す０を代入
						PackmanDamageFlag = 0;
						set = 0;
					}
				}
				//パックマンの移動操作
				else 
				{

					//パックマンのアニメーション
					{
						if (set == 3)
							set = Coroutine(60);

						//パックマンが動いているなら絵が切り替わるかためにカウンタを加算する
						if (BallMoveFlag == 1)
						{
							PackmanCounter++;

							//もしダメージを受け始めて３０フレーム経過していたらダメージ状態から
							//元に戻してあげる
							if (PackmanCounter == 3)
							{
								//『ダメージを受けていない』を表す０を代入
								if (set == 2 || set == 3)
									set = 0;
								else
									set++;

								PackmanCounter = 0;

							}
						}
					}

					// ↑キーを押していたらパックマンを上に移動させる
					if (CheckHitKey(KEY_INPUT_UP) == 1)
					{
						PackmanY -= PackmanMoveValue;
						Packmanrotate = PI / 2;
						BallMoveFlag = 1;
						PackmanReverse = 1;
					}
					// ↓キーを押していたらパックマンを下に移動させる
					else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
					{
						PackmanY += PackmanMoveValue;
						BallMoveFlag = 1;
						Packmanrotate = PI / 2;
						PackmanReverse = 0;
					}
					// ←キーを押していたらパックマンを左に移動させる
					else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
					{
						PackmanX -= PackmanMoveValue;
						BallMoveFlag = 1;
						Packmanrotate = PI / 180;
						PackmanReverse = 1;
					}
					// →キーを押していたらパックマンを右に移動させる
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
				}

				//スペースキーを押した場合は処理を分岐
				if (CheckHitKey(KEY_INPUT_SPACE))
				{

					set = 3;
					//前フレームでショットボタンを押したかが保存されている変数が0だったら弾を発射
					if (ShotBFlag == 0)
					{
						//画面上に出ていない弾があるか、弾の数だけ繰り返して調べる
						for (i = 0; i < SHOT; i++)
						{
							//弾iが画面上に出ていない場合はその弾を画面に出す
							if (ShotFlag[i] == 0)
							{
								//弾 i の位置をセット、位置はパックマンの中心にする
								ShotX[i] = (Bw - Sw) / 2 + PackmanX;
								ShotY[i] = (Bh - Sh) / 2 + PackmanY;

								//弾の移動速度を設定する
								{
									double sb, sbx, sby, bx, by, sx, sy;

									sx = ShotX[i] + ShotW / 2;
									sy = ShotY[i] + ShotH / 2;

									bx = BlinkyX + Ebw / 2;
									by = BlinkyY + Ebh / 2;

									sbx = bx - sx;
									sby = by - sy;

									sb = sqrt(sbx * sbx + sby * sby);

									ShotSx = sbx / sb * SHOTSPEED;
									ShotSy = sby / sb * SHOTSPEED;

									//弾 iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
									ShotFlag[i] = 1;

									//一つ球を出したので球を出すループから抜けます
									break;
								}

							}
						}
					}

					//前フレームでショットボタンを押されていたかを保存する変数に１（押されていた）を代入
					ShotBFlag = 1;

				}
				else
				{
					//ショットボタンが押されていなかった場合は
					//前フレームでショットボタンが押されていたかを保存する変数に０（おされていない）を代入
					ShotBFlag = 0;

				}


				//パックマンが画面左端からはみ出しそうになっていたら画面内の座標に戻してあげる
				if (PackmanX < -64)PackmanX = 640;

				//パックマンが画面右端からはみ出しそうになったら画面内に戻してあげる
				if (PackmanX > 640)PackmanX = 0;

				// パックマンが画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
				if (PackmanY < -64)PackmanY = 480;

				// パックマンが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
				if (PackmanY > 480)PackmanY = 0;

				DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, Packmanrotate, Packman[set], TRUE, PackmanReverse);
			}

			//弾の数だけ弾を動かす処理を繰り返す
			for (i = 0; i < SHOT; i++)
			{
				//自機の弾１の移動ルーチン(存在状態を保持している変数の内容が1(存在する)の場合のみ行う)
				if (ShotFlag[i] == 1)
				{
					//弾iを16ドット上に移動させる
					ShotX[i] += ShotSx;
					ShotY[i] += ShotSy;

					//画面外に出てしまった場合は存在状態を保持している変数に0（存在しない）を代入する
					if (ShotY[i] > 480 || ShotY[i] < 0 ||
						ShotX[i]>640 || ShotX[i] < 0)
						ShotFlag[i] = 0;

					//画面に弾 i を描画する
					DrawGraph((int)ShotX[i], (int)ShotY[i], ShotGraph, TRUE);
				}
			}

			//ブリンキーの移動ルーチン
			{
				//ダメージを受けているかどうかで処理を分岐
				if (BlinkyDamageFlag == 1)
				{
					//ダメージを受けている場合はダメージグラフィックを描画する
					DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyDamageGraph, TRUE, Blinkyreverse);
					//ダメージを受けている時間を測るカウンターに1を加算する
					BlinkyDamageCounter++;

					//もしダメージを受け始めて３０フレーム経過していたらダメージ状態から
					//元に戻してあげる
					if (BlinkyDamageCounter == 30)
					{
						//『ダメージを受けていない』を表す０を代入
						BlinkyDamageFlag = 0;
					}
				}
				else
				{
					//ブリンキーの座標を移動している方向に移動する
					if (BlinkyMuki == 1)BlinkyX += BlinkyMoveValue;
					if (BlinkyMuki == 0)BlinkyX -= BlinkyMoveValue;

					//ブリンキーが画面右端から出そうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
					if (BlinkyX > 640)
					{
						BlinkyX = 640;
						BlinkyMuki = 0;
						Blinkyreverse = FALSE;
					}

					// ブリンキーが画面左端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
					if (BlinkyX < 0)
					{
						BlinkyX = 0;
						BlinkyMuki = 1;
						Blinkyreverse = TRUE;
					}

					// ブリンキーを描画
					DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyGraph, TRUE, Blinkyreverse);

					//弾を打つタイミングを計測するためのカウンターに１ずつを加算
					ETamaCounter++;

					//もしカウンター変数が６０だった場合は弾を打つ処理を行う
					if (ETamaCounter == 60)
					{
						//もしすでに弾が『飛んでいない』状態だった場合のみ発射処理を行う
						if (ETamaFlag == 0)
						{
							//弾の発射位置を設定する
							ETamaX = BlinkyX + BlinkyW / 2 - ETamaW / 2;
							ETamaY = BlinkyY + BlinkyH / 2 - ETamaH / 2;

							//弾の移動速度を設定する
							{
								double sb, sbx, sby, bx, by, sx, sy;

								sx = ETamaX + ETamaW / 2;
								sy = ETamaY + ETamaH / 2;

								bx = PackmanX + Bw / 2;
								by = PackmanY + Bh / 2;

								sbx = bx - sx;
								sby = by - sy;

								//平方根を求めるのに標準関数のsqrtを使う、
								//これをつかにはmath.hをインクルードする必要がある
								sb = sqrt(sbx * sbx + sby * sby);

								//１フレーム当たり８ドット移動するようにする
								ETamaSx = sbx / sb * SHOTSPEED;
								ETamaSy = sby / sb * SHOTSPEED;
							}

							//弾の状態を保持する変数に『飛んでいる』を示す１を代入する
							ETamaFlag = 1;

						}
						//弾を打つタイミングを計測するための変数に０を代入
						ETamaCounter = 0;
					}

				}

			}

			//敵の弾の状態が『飛んでいる』場合のみ弾の移動処理を行う
			if (ETamaFlag == 1)
			{
				//弾を移動させる
				ETamaX += ETamaSx;
				ETamaY += ETamaSy;

				//もし弾が画面下端からはみ出てしまった場合は弾の状態を『飛んでいない』
				//を表す０にする
				if (ETamaY > 480 || ETamaY < 0 ||
					ETamaX>640 || ETamaX < 0)ETamaFlag = 0;

				//ブリンキーとの当たり判定
				if (((ETamaX > PackmanX && ETamaX < PackmanX + Bw) ||
					(PackmanX > ETamaX && PackmanX < ETamaX + ETamaW)) &&
					((ETamaY > PackmanY && ETamaY < PackmanY + Bh) ||
						(PackmanY > ETamaY && PackmanY < ETamaY + ETamaH)))
				{

					if (PackmanDamageFlag == 0)
						//ヒットカウントを加算する
						hitCount++;

					//ブリンキーがダメージを受けているかどうかを保持する変数に『受けている』を表す１を代入
					PackmanDamageFlag = 1;

					//ブリンキーがダメージを受けている時間を測るカウンタ変数に０を代入
					PackmanDamageCounter = 0;

					//接触している場合は当たった弾の存在を消す
					ETamaFlag = 0;

				}

				//画面に描画する(ETamaGraph :敵の弾のグラフィックのハンドル)
				DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
			}


			//弾と敵の当たり判定、弾の数だけ繰り返す
			for (i = 0; i < SHOT; i++)
			{
				//弾iが存在している場合のみ次の処理に映る
				if (ShotFlag[i] == 1)
				{
					//ブリンキーとの当たり判定
					if (((ShotX[i] > BlinkyX && ShotX[i] < BlinkyX + BlinkyW) ||
						(BlinkyX > ShotX[i] && BlinkyX < ShotX[i] + ShotW)) &&
						((ShotY[i] > BlinkyY && ShotY[i] < BlinkyY + BlinkyH) ||
							(BlinkyY > ShotY[i] && BlinkyY < ShotY[i] + ShotH)))
					{
						//接触している場合は当たった弾の存在を消す
						ShotFlag[i] = 0;

						if (BlinkyDamageFlag == 0)
							//ヒットカウントを加算する
							EhitCount++;

						//ブリンキーがダメージを受けているかどうかを保持する変数に『受けている』を表す１を代入
						BlinkyDamageFlag = 1;

						//ブリンキーがダメージを受けている時間を測るカウンタ変数に０を代入
						BlinkyDamageCounter = 0;


					}
				}
			}

			DrawFormatString(0, 0, white, "ブリンキーにあてた回数 : %d\n当たった回数 : %d", EhitCount, hitCount);
			DrawFormatString(400, 0, white, "space :弾を発射 \n十字キー : 移動");


			fps.Update();	//更新
			fps.Draw();		//描画
			fps.Wait();		//待機




			// 裏画面の内容を表画面にコピーする
			ScreenFlip();

			if (EhitCount == 25)
				scene = GameClear;
			else if (hitCount == 10)
				scene = GameOver;

		}

		break;
		case GameClear:
		{
			//フォントサイズ
			SetFontSize(80);

			DrawFormatString(180, 200, yellow, "GameClear");
			// 裏画面の内容を表画面にコピーする
			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_RETURN) == 1)
			{
				scene = Title;
			}

		}
		break;
		case GameOver:
		{
			//フォントサイズ
			SetFontSize(80);

			DrawFormatString(180, 200, yellow, "GameOver");
			// 裏画面の内容を表画面にコピーする
			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_RETURN) == 1)
			{
				scene = Title;
			}
		}
		break;
		default:
			break;
		}
		//移動ルーチン

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

	}

	//DXライブラリ使用の終了処理
	DxLib::DxLib_End();

	return 0;
}

int Coroutine(int time)
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
