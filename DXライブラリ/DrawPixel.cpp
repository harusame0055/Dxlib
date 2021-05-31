#include"DxLib.h"

#define PI 3.1415926535897932384626433832795f


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
	int BallX, BallY, BallGraph;
	int SikakuX, SikakuY, SikakuMuki, SikakuGraph, Sikakureverse;
	int ShotX, ShotY, ShotFlag, ShotGraph;

	//画面モードの設定
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);

	int set = 0;

	//DXライブラリ初期化処理
	if (DxLib_Init() == -1)	return -1;

	int image[16]{};
	LoadDivGraph("../Graphic/パックマン1.png", 3, 1, 3, 64, 64, image);

	float Ballrotate;

	//グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//ボール君のグラフィックをメモリにロード＆表示座標をセット
	BallGraph = LoadGraph("../Graphic/パックマン.png");
	BallX = 320; BallY = 350; Ballrotate = PI / 2;

	//四角君のグラフィックをメモリにロード＆表示座標をセット
	SikakuGraph = LoadGraph("../Graphic/ブリンキー.png");
	SikakuX = 640; SikakuY = 50; Sikakureverse = FALSE;

	//弾のグラフィックをメモリにロード
	ShotGraph = LoadGraph("../Graphic/Shot.png");

	//弾が画面上に存在しているか保持する変数に『存在していない』を意味する0を代入しておく
	ShotFlag = 0;

	//四角君の移動方向をセット
	SikakuMuki = 1;

	DrawPixel(320, 240, GetColor(255, 255, 255));

	//移動ルーチン
	while (1)
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

			//スペースキーを押していて、且弾が撃ち出されていなかったら弾を発射する
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && ShotFlag == 0)
			{
				int Bw, Bh, Sw, Sh;

				//ボール君と弾の画像サイズを得る
				GetGraphSize(image[set], &Bw, &Bh);
				GetGraphSize(ShotGraph, &Sw, &Sh);

				//弾の位置をセット、位置はボール君の中心にする
				ShotX = BallX - 5;
				ShotY = BallY + 10;

				//弾は現時点を持って存在するので、存在状態を保持する変数に1を代入する
				ShotFlag = 1;
			}

			//ボール君が画面左端からはみ出しそうになっていたら画面内の座標に戻してあげる
			if (BallX < -64)BallX = 640;

			//ボール君が画面右端からはみ出しそうになったら画面内に戻してあげる
			if (BallX > 640)BallX = 0;

			// ボール君が画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY < -64)BallY = 480;

			// ボール君が画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY > 480)BallY = 0;

			//DrawGraph(BallX, BallY, BallGraph, TRUE);

			DrawRotaGraph2(BallX, BallY, 32, 32, 1, Ballrotate, image[set], TRUE, FALSE);
		}

		//自機の弾の移動ルーチン(存在状態を保持している変数の内容が1(存在する)の場合のみ行う)
		if (ShotFlag == 1)
		{
			//弾を16ドット上に移動させる
			ShotY -= 4;

			//画面外に出てしまった場合は存在状態を保持している変数に0(存在しない)を代入する
			if (ShotY < -80)
				ShotFlag = 0;

			//画面に弾を描画する
			DrawGraph(ShotX, ShotY, ShotGraph, TRUE);
		}

		//四角君の移動ルーチン
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