#include"DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
	int BallX, BallY, BallGraph;
	int SikakuX, SikakuY, SikakuMuki, SikakuGraph;

	//画面モードの設定
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);

	int set = 0;

	//DXライブラリ初期化処理
	if (DxLib_Init() == -1)	return -1;

	int image[3]{};
	LoadDivGraph("../パックマン1.png", 3, 1, 3, 64, 64, image);

	float rotate = 0;

	//グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//ボール君のグラフィックをメモリにロード＆表示座標をセット
	BallGraph = LoadGraph("../Graphic/パックマン.png");
	BallX = -64; BallY = 0;

	//四角君のグラフィックをメモリにロード＆表示座標をセット
	SikakuGraph = LoadGraph("../Graphic/ブリンキー.png");
	SikakuX = 640; SikakuY = 300;

	//四角君の移動方向をセット
	SikakuMuki = 1;


	//移動ルーチン
	while (1)
	{

		if (set == 3)set = 0;

		//画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//ボール君の操作ルーチン
		{
			// ↑キーを押していたらボール君を上に移動させる
			if (CheckHitKey(KEY_INPUT_UP) == 1)
			{
				set++;
				BallY -= 3;
				rotate = 3.14 / 2;
			}
			// ↓キーを押していたらボール君を下に移動させる
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				set++;
				BallY += 3;
				//ここ出来てない
				rotate = 4.7;
			}

			// ←キーを押していたらボール君を左に移動させる
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
				set++;
				BallX -= 3;
				rotate = 0;
			}

			// →キーを押していたらボール君を右に移動させる
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				set++;
				BallX += 3;
				rotate = 3.16;
			}

			//ボール君が画面左端からはみ出しそうになっていたら画面内の座標に戻してあげる
			if (BallX < 0)BallX = 0;

			//ボール君が画面右端からはみ出しそうになったら画面内に戻してあげる
			if (BallX > 640 - 64)BallX = 640 - 64;

			// ボール君が画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY < 0)BallY = 0;

			// ボール君が画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY > 480 - 64)BallY = 480 - 64;

			//DrawGraph(BallX, BallY, BallGraph, TRUE);
			DrawRotaGraph(BallX, BallY, 1.5f, rotate, image[set], TRUE);
		}

		//四角君の移動ルーチン
		{
			//四角君の座標を移動している方向に移動する
			if (SikakuMuki == 1)SikakuX += 3;
			if (SikakuMuki == 0)SikakuX -= 3;

			//四角君が画面右端から出そうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
			if (SikakuX > 576)
			{
				SikakuX = 576;
				SikakuMuki = 0;

			}

			// 四角君が画面左端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
			if (SikakuX < 0)
			{
				SikakuX = 0;
				SikakuMuki = 1;
			}

			// 四角君を描画
			DrawGraph(SikakuX, SikakuY, SikakuGraph, TRUE);
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
	DxLib_End();

	return 0;
}