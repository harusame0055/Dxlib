#include"DxLib.h"
using namespace DxLib;

#define PI 3.1415926535897932384626433832795f

#define SHOT 2

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
	int BallX, BallY, BallGraph;
	int SikakuX, SikakuY, SikakuMuki, SikakuGraph, Sikakureverse;
	int SikakuDamageFlag, SikakuDamageCounter, SikakuDamageGraph;
	int ShotX[SHOT], ShotY[SHOT], ShotFlag[SHOT], ShotGraph;
	int SikakuW, SikakuH, ShotW, ShotH;
	int ShotBFlag;
	int i;

	int white = GetColor(0, 0, 255);

	SetFontSize(32);


	//画面モードの設定
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);

	int set = 0;

	//DXライブラリ初期化処理
	if (DxLib_Init() == -1)	return -1;

	float Ballrotate;

	//グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//ボール君のグラフィックをメモリにロード＆表示座標をセット
	BallGraph = LoadGraph("../Graphic/パックマン1.png");
	BallX = 320; BallY = 350; Ballrotate = PI / 2;

	//四角君のグラフィックをメモリにロード＆表示座標をセット
	SikakuGraph = LoadGraph("../Graphic/ブリンキー.png");
	SikakuX = 640; SikakuY = 50; Sikakureverse = FALSE;

	//四角君のダメージ時のグラフィックをメモリにロード
	SikakuDamageGraph = LoadGraph("../Graphic/ゴースト.png");

	//四角君がダメージを受けているかどうかの変数に『受けていない』を表す0を代入
	SikakuDamageFlag = 0;

	//弾のグラフィックをメモリにロード
	ShotGraph = LoadGraph("../Graphic/Shot.png");


	//弾１・２が画面上に存在しているか保持する変数に『存在していない』を意味する0を代入しておく
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	//ショットボタンが前のフレームで押されたかどうかを保存する変数に０（押されていない）を代入
	ShotBFlag = 0;

	//四角君の移動方向をセット
	SikakuMuki = 1;

	//弾のグラフィックサイズを得る
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//四角君のグラフィックのサイズを得る
	GetGraphSize(SikakuGraph, &SikakuW, &SikakuH);

	//移動ルーチン
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (set == 3)set = 0;

		//画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//ボール君の操作ルーチン
		{
			//ボール君の移動操作
			{
				// ↑キーを押していたらボール君を上に移動させる
				if (CheckHitKey(KEY_INPUT_UP) == 1)
				{
					set++;
					BallY -= 3;
					Ballrotate = PI / 2;
				}
				// ↓キーを押していたらボール君を下に移動させる
				else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
				{
					set++;
					BallY += 3;
				}
				// ←キーを押していたらボール君を左に移動させる
				else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
				{
					set++;
					BallX -= 3;
				}
				// →キーを押していたらボール君を右に移動させる
				else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
				{
					set++;
					BallX += 3;
				}
			}


			//スペースキーを押した場合は処理を分岐
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				//前フレームでショットボタンを押したかが保存されている変数が0だったら弾を発射
				if (ShotBFlag == 0)
				{
					//画面上に出ていない弾があるか、弾の数だけ繰り返して調べる
					for (i = 0; i < SHOT; i++)
					{
						//弾iが画面上に出ていない場合はその弾を画面に出す
						if (ShotFlag[i] == 0)
						{
							int Bw, Bh, Sw, Sh;

							//ボール君と弾の画像のサイズを得る
							GetGraphSize(BallGraph, &Bw, &Bh);
							GetGraphSize(ShotGraph, &Sw, &Sh);

							//弾 i の位置をセット、位置はボール君の中心にする
							ShotX[i] = BallX - 10;
							ShotY[i] = BallY + 10;

							//弾 iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
							ShotFlag[i] = 1;

							//一つ球を出したので球を出すループから抜けます
							break;
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


			//ボール君が画面左端からはみ出しそうになっていたら画面内の座標に戻してあげる
			if (BallX < -64)BallX = 640;

			//ボール君が画面右端からはみ出しそうになったら画面内に戻してあげる
			if (BallX > 640)BallX = 0;

			// ボール君が画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY < -64)BallY = 480;

			// ボール君が画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY > 480)BallY = 0;

			DrawRotaGraph2(BallX, BallY, 32, 32, 1, Ballrotate, BallGraph, TRUE, TRUE);
		}

		//弾の数だけ弾を動かす処理を繰り返す
		for (i = 0; i < SHOT; i++)
		{
			//自機の弾１の移動ルーチン(存在状態を保持している変数の内容が1(存在する)の場合のみ行う)
			if (ShotFlag[i] == 1)
			{
				//弾iを16ドット上に移動させる
				ShotY[i] -= 16;

				//画面外に出てしまった場合は存在状態を保持している変数に0（存在しない）を代入する
				if (ShotY[i] < -80)
				{
					ShotFlag[i] = 0;
				}

				//画面に弾 i を描画する
				DrawGraph(ShotX[i], ShotY[i], ShotGraph, TRUE);
			}
		}
		//四角君の移動ルーチン
		{
			//ダメージを受けているかどうかで処理を分岐
			if (SikakuDamageFlag == 1)
			{
				//ダメージを受けている場合はダメージグラフィックを描画する
				DrawRotaGraph2(SikakuX, SikakuY, 32, 32, 1, 0, SikakuDamageGraph, FALSE, Sikakureverse);
				//ダメージを受けている時間を測るカウンターに1を加算する
				SikakuDamageCounter++;

				//もしダメージを受け始めて３０フレーム経過していたらダメージ状態から
				//元に戻してあげる
				if (SikakuDamageCounter == 30)
				{
					//『ダメージを受けていない』を表す０を代入
					SikakuDamageFlag = 0;
				}
			}
			else
			{
				//四角君の座標を移動している方向に移動する
				if (SikakuMuki == 1)SikakuX += 3;
				if (SikakuMuki == 0)SikakuX -= 3;

				//四角君が画面右端から出そうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
				if (SikakuX > 640)
				{
					SikakuX = 640;
					SikakuMuki = 0;
					Sikakureverse = FALSE;
				}

				// 四角君が画面左端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
				if (SikakuX < 0)
				{
					SikakuX = 0;
					SikakuMuki = 1;
					Sikakureverse = TRUE;
				}

				// 四角君を描画
				DrawRotaGraph2(SikakuX, SikakuY, 32, 32, 1, 0, SikakuGraph, TRUE, Sikakureverse);
			}

		}

		//弾と敵の当たり判定、弾の数だけ繰り返す
		for (i = 0; i < SHOT; i++)
		{
			//弾iが存在している場合のみ次の処理に映る
			if (ShotFlag[i] == 1)
			{
				//四角君との当たり判定
				if (((ShotX[i] > SikakuX && ShotX[i] < SikakuX + SikakuW) ||
					(SikakuX > ShotX[i] && SikakuX < ShotX[i] + ShotW)) &&
					((ShotY[i] > SikakuY && ShotY[i] < SikakuY + SikakuH) ||
						(SikakuY > ShotY[i] && SikakuY < ShotY[i] + ShotH)))
				{
					//接触している場合は当たった弾の存在を消す
					ShotFlag[i] = 0;

					//接触している場合は当たった弾の存在を消す
					ShotFlag[i] = 0;

					//四角君がダメージを受けているかどうかを保持する変数に『受けている』を表す１を代入
					SikakuDamageFlag = 1;

					//四角君がダメージを受けている時間を測るカウンタ変数に０を代入
					SikakuDamageCounter = 0;
				}
			}
		}

		//文字列を表示
		DrawFormatString(0, 0, white, "");

		// 裏画面の内容を表画面にコピーする
		ScreenFlip();



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
