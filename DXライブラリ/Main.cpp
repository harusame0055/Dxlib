#include"DxLib.h"
#include<math.h>
using namespace DxLib;

// 追加したやつ
#include"Scene.h"
#include"Fps.h"
#include"Game.h"
#include"Player.h"

	//タイトルに初期化
Scene scene;
Player player;
/// <summary>
/// 変数の初期化関数
/// </summary>
void Game::initialize()
{
	sceneGraph[0] = LoadGraph("../Graphic/Title2.png");
	sceneGraph[1] = LoadGraph("../Graphic/GameClear.png");
	sceneGraph[2] = LoadGraph("../Graphic/GameOver.png");

	Level = 1;
	Input = 0;
	Count = 0;

	AudioOneShot = 0;

	ShotAudio = LoadSoundMem("../BGM/ショット.mp3");
	HitAudio = LoadSoundMem("../BGM/ショット命中.mp3");
	PowerUpAudio = LoadSoundMem("../BGM/PowerUp.mp3");

	AudioSound[0] = LoadSoundMem("../BGM/パックマンSE.mp3");
	AudioSound[1] = LoadSoundMem("../BGM/TETRIS.mp3");
	AudioSound[2] = LoadSoundMem("../BGM/コックカワサキ.mp3");

	ItemGet = 0;
	ItemGetCounter = 0;


	Item = LoadGraph("../Graphic/Cherry.png");


	ItemX = GetRand(WindowWidth - 50) + 20;
	ItemY = GetRand(WindowHeight - 50) + 20;


	//ブリンキーのグラフィックをメモリにロード＆表示座標をセット
	BlinkyGraph = LoadGraph("../Graphic/ブリンキー.png");
	BlinkyX = 640; BlinkyY = 100; Blinkyreverse = FALSE;
	BlinkyMukiCounter = 0;

	BlinkyDamageCounter = 0;

	LoadScene = 0;

}
/// <summary>
/// ほかの関数を呼び出すためのアップデート関数
/// </summary>
void Game::Update()
{
	switch (scene)
	{
	case Title:
	{
		if (AudioOneShot == 0)
		{
			AudioOneShot = 1;
			//PlaySoundFile("../BGM/  .mp3", DX_PLAYTYPE_NOMAL);
		}

		//画面を初期化(真っ黒にする)
		ClearDrawScreen();
		//フォントサイズ
		SetFontSize(40);
		DrawFormatString(250, 420, yellow, "LEVEL %d", Level);

		//フォントサイズ
		DrawGraph(0, 0, sceneGraph[0], TRUE);

		//フォントサイズ
		SetFontSize(20);
		DrawFormatString(10, 10, yellow, "Enterを押すと遊べます");

		fps.Update();	//更新
		fps.Draw();		//描画
		fps.Wait();		//待機

		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_UP) == 1 && Input == 0)
		{
			if (Level < 3)
			{
				Input = 1;
				Level++;
			}
		}
		else	if (CheckHitKey(KEY_INPUT_DOWN) == 1 && Input == 0)
		{
			if (Level > 1)
			{
				Input = 1;
				Level--;
			}
		}
		else if (CheckHitKey(KEY_INPUT_RETURN) == 1 && Input == 0)
		{
#pragma region 初期化

			player.initialize();

			switch (Level)
			{
			case 1:
				ETamaSpeed = 7;
				BlinkyMoveValue = 5;
				break;
			case 2:
				ETamaSpeed = 10;
				BlinkyMoveValue = 6;
				break;
			case 3:
				ETamaSpeed = 15;
				BlinkyMoveValue = 7;
				break;
			default:
				break;
			}

			//ブリンキーのダメージ時のグラフィックをメモリにロード
			BlinkyDamageGraph = LoadGraph("../Graphic/ゴースト.png");

			//敵の弾のグラフィックをロード
			ETamaGraph = LoadGraph("../Graphic/EShot.png");



			//ブリンキーがダメージを受けているかどうかの変数に『受けていない』を表す0を代入
			BlinkyDamageFlag = 0;

			//敵の弾のグラフィックサイズを得る
			GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

			//敵の弾が飛んでいるかどうかを保持する変数に『飛んでいない』を表す０を代入
			ETamaFlag = 0;

			//敵が弾を打つタイミングを取るための計測用変数に0を代入
			ETamaCounter = 0;

			//ITEMのグラフィックサイズを得る
			GetGraphSize(Item, &ItemW, &ItemH);


			ItemFlag = 0;

			//ブリンキーの移動方向をセット
			BlinkyMuki = 1;

			//ブリンキーのグラフィックのサイズを得る
			GetGraphSize(BlinkyGraph, &BlinkyW, &BlinkyH);

			//ブリンキーと弾の画像サイズを得る
			GetGraphSize(BlinkyGraph, &Ebw, &Ebh);
			GetGraphSize(ETamaGraph, &Esw, &Esh);

			EhitCount = 0;

			ItemCounter = 0;

#pragma endregion	

			LoadScene = 1;
			AudioOneShot = 0;
			scene = Load;
		}
		else
		{
			Count++;
			if (Count == 10)
			{
				Input = 0;

				Count = 0;
			}
		}
	}
	break;
	case MainGame:
	{
		//フォントサイズ
		SetFontSize(20);

		//画面を初期化(真っ黒にする)
		ClearDrawScreen();
		//パックマンの操作ルーチン
		player.PlayerMove();

		//ブリンキーの移動ルーチン
		{
			//ダメージを受けているかどうかで処理を分岐
			if (BlinkyDamageFlag == 1)
			{
				//ダメージを受けている場合はダメージグラフィックを描画する
				DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyDamageGraph, TRUE, Blinkyreverse);
				//ダメージを受けている時間を測るカウンターに1を加算する
				BlinkyDamageCounter++;

				//		//もしダメージを受け始めて３０フレーム経過していたらダメージ状態から
				//		//元に戻してあげる
				if (BlinkyDamageCounter == 30)
				{
					//『ダメージを受けていない』を表す０を代入
					BlinkyDamageFlag = 0;
				}
			}
			else
			{
				//ブリンキーの座標を移動している方向に移動する

				BlinkyMukiCounter++;
				if (BlinkyMukiCounter == 30)
				{
					BlinkyMuki = GetRand(3);
					BlinkyMukiCounter = 0;
				}

				if (BlinkyMuki == 0)
				{
					BlinkyX += BlinkyMoveValue;
					Blinkyreverse = TRUE;
				}
				else if (BlinkyMuki == 1)
				{
					BlinkyX -= BlinkyMoveValue;
					Blinkyreverse = FALSE;
				}
				else if (BlinkyMuki == 2)
					BlinkyY += BlinkyMoveValue;
				else if (BlinkyMuki == 3)
					BlinkyY -= BlinkyMoveValue;

				//ブリンキーが画面右端から出たら反対側から出現させる
				if (BlinkyX > WindowWidth)
				{
					BlinkyX = WindowWidth;
					Blinkyreverse = FALSE;
				}
				// ブリンキーが画面左端から出たら反対側から出現させる
				if (BlinkyX < 0)
				{
					BlinkyX = 0;
					Blinkyreverse = TRUE;
				}

				//ブリンキーが画面右端から出たら反対側から出現させる
				if (BlinkyY > WindowHeight)
				{
					BlinkyY = 0;
				}
				// ブリンキーが画面左端から出たら反対側から出現させる
				if (BlinkyY < 0)
				{
					BlinkyY = WindowHeight;
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

							bx = player.GetPosX() + player.GetBw() / 2;
							by = player.GetPosY() + player.GetBh() / 2;

							sbx = bx - sx;
							sby = by - sy;

							//平方根を求めるのに標準関数のsqrtを使う、
							//これをつかにはmath.hをインクルードする必要がある
							sb = sqrt(sbx * sbx + sby * sby);

							//１フレーム当たり８ドット移動するようにする
							ETamaSx = sbx / sb * ETamaSpeed;
							ETamaSy = sby / sb * ETamaSpeed;
							ShotPlayAudio();
						}

						//弾の状態を保持する変数に『飛んでいる』を示す１を代入する
						ETamaFlag = 1;
					}
					//弾を打つタイミングを計測するための変数に０を代入
					ETamaCounter = 0;
				}
			}
		}

		//弾の数だけ弾を動かす処理を繰り返す
		player.ShotMove();

		//弾と敵の当たり判定、弾の数だけ繰り返す
		//player.ShotHitCheck();

		//敵の弾の状態が『飛んでいる』場合のみ弾の移動処理を行う
		if (ETamaFlag == 1)
		{
			//弾を移動させる
			ETamaX += ETamaSx;
			ETamaY += ETamaSy;

			//もし弾が画面下端からはみ出てしまった場合は弾の状態を『飛んでいない』
			//を表す０にする
			if (ETamaY > WindowHeight || ETamaY < 0 ||
				ETamaX>WindowWidth || ETamaX < 0)
				ETamaFlag = 0;

			//パックマンとの当たり判定
			if (((ETamaX > player.GetPosX() && ETamaX < player.GetPosX() + player.GetBw()) ||
				(player.GetPosX() > ETamaX && player.GetPosX() < ETamaX + ETamaW)) &&
				((ETamaY > player.GetPosY() && ETamaY < player.GetPosY() + player.GetBh()) ||
					(player.GetPosY() > ETamaY && player.GetPosY() < ETamaY + ETamaH)))
			{
				if (player.GetDamageFlag() == 0)
					//ヒットカウントを加算する
					player.HitCount();

				//ブリンキーがダメージを受けているかどうかを保持する変数に『受けている』を表す１を代入
				player.DamegeFlag(1);

				PlaySoundMem(HitAudio, DX_PLAYTYPE_BACK);

				//ブリンキーがダメージを受けている時間を測るカウンタ変数に０を代入
				player.DamageCounter(0);

				//接触している場合は当たった弾の存在を消す
				ETamaFlag = 0;

			}
			//画面に描画する(ETamaGraph :敵の弾のグラフィックのハンドル)
			DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
		}

		//player.ItemGeneration();


		DrawFormatString(0, 0, white, "ブリンキーにあてた回数 : %d \n 当たった回数 : %d", BlinkyDamageCounter, BlinkyDamageFlag);
		DrawFormatString(850, 0, white, "space :弾を発射 \n十字キー : 移動");

		fps.Update();	//更新
		fps.Draw();		//描画
		fps.Wait();		//待機

		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		//BGMの処理
		if (AudioOneShot == 0)
		{
			AudioOneShot = 1;
			PlaySoundMem(AudioSound[0], DX_PLAYTYPE_NORMAL);
			PlaySoundMem(AudioSound[1], DX_PLAYTYPE_BACK);
		}
		if (ItemGetCounter == 1 && CheckSoundMem(AudioSound[1]) == 0)
		{
			PlaySoundMem(PowerUpAudio, DX_PLAYTYPE_BACK);
		}
		if (CheckSoundMem(PowerUpAudio) == 0 && CheckSoundMem(AudioSound[1]) == 0)
		{
			PlaySoundMem(AudioSound[1], DX_PLAYTYPE_BACK);
		}

		if (EhitCount == 25)
		{
			LoadScene = 2;
			scene = Load;
			StopSoundMem(AudioSound[1]);
			AudioOneShot = 0;
		}
		else if (EhitCount == 15)
		{
			switch (Level)
			{
			case 1:
				ETamaSpeed = 12;
				BlinkyMoveValue = 5;
				break;
			case 2:
				ETamaSpeed = 15;
				BlinkyMoveValue = 6;
				break;
			case 3:
				ETamaSpeed = 17;
				BlinkyMoveValue = 7;
				break;
			default:
				break;
			}

		}
		else if (player.GetHitCount() == 10)
		{
			LoadScene = 3;
			AudioOneShot = 0;
			StopSoundMem(AudioSound[1]);
			scene = Load;
		}
	}
	break;
	case GameClear:
	{
		//画面を初期化(真っ黒にする)
		ClearDrawScreen();

		if (AudioOneShot == 0)
		{
			AudioOneShot = 1;
		}
		DrawGraph(0, 50, sceneGraph[1], TRUE);
		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_RETURN) == 1)
		{
			LoadScene = 0;
			AudioOneShot = 0;
			scene = Load;
		}

	}
	break;
	case GameOver:
	{
		//画面を初期化(真っ黒にする)
		ClearDrawScreen();

		if (AudioOneShot == 0)
		{
			PlaySoundMem(AudioSound[2], DX_PLAYTYPE_BACK);
			AudioOneShot = 1;
		}
		DrawGraph(0, 0, sceneGraph[2], TRUE);
		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_RETURN) == 1)
		{
			LoadScene = 0;
			scene = Load;
			Input = 1;
		}
	}
	break;
	case Load:
	{
		Count++;

		//画面を初期化(真っ黒にする)
		ClearDrawScreen();

		fps.Update();	//更新
		fps.Wait();		//待機

		if (Count == 50)
		{
			scene = Scene(LoadScene);

			Count = 0;
		}
	}
	break;
	default:
		break;
	}
}

void Game::ShotPlayAudio()
{
	PlaySoundMem(ShotAudio, DX_PLAYTYPE_BACK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpcmdLine, int nCmdShow)
{
	Game game;

#pragma region DxLibの初期化

	//画面モードの設定
	SetGraphMode(game.GetWidth(), game.GetHeight(), 16);
	ChangeWindowMode(true);

	//グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//DXライブラリ初期化処理
	if (DxLib_Init() == -1)	return -1;
#pragma endregion

	//変数の初期化処理
	game.initialize();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//アップデート関数を使いプレイヤーや、敵の動きを呼び出す
		game.Update();

		//プレイヤーにgameへの参照をセット
		player.SetGame(game);

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

/// <summary>
///		指定した秒数待機し、０の値を返すコルーチン関数
/// </summary>
/// <param name="time"></param>
/// <returns></returns>
int Game::Coroutine(int time)
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
