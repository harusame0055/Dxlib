#include"DxLib.h"
#include "Player.h"
#include<math.h>

Game* gameptr;

void Player::SetGame(Game* g) {
	gameptr = g;
}

void Player::initialize()
{
	//パックマンのグラフィックをメモリにロード＆表示座標をセット
	Packman[0] = LoadGraph("../Graphic/パックマン1.png");
	Packman[1] = LoadGraph("../Graphic/パックマン2.png");
	Packman[2] = LoadGraph("../Graphic/パックマン3.png");
	Packman[3] = LoadGraph("../Graphic/パックマン4.png");
	Packman[4] = LoadGraph("../Graphic/ダメージパックマン.png");
	PackmanX = 320; PackmanY = 350; Packmanrotate = PI / 2;
	PackmanCounter = 0;
	PackmanReverse = 1;
	//パックマンが動いているかどうかの変数に(動いていない)を表す0を代入
	BallMoveFlag = 0;
	PackmanDamageFlag = 0;
	PackmanMoveValue = 5;

	ShotSpeed = 10;

	//弾のグラフィックをメモリにロード
	ShotGraph = LoadGraph("../Graphic/Shot.png");

	//パックマンと弾の画像サイズを得る
	GetGraphSize(Packman[set], &Bw, &Bh);
	GetGraphSize(ShotGraph, &Sw, &Sh);

	hitCount = 0;

	//弾１・２が画面上に存在しているか保持する変数に『存在していない』を意味する0を代入しておく
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	//ショットボタンが前のフレームで押されたかどうかを保存する変数に０（押されていない）を代入
	ShotBFlag = 0;

	//弾のグラフィックサイズを得る
	GetGraphSize(ShotGraph, &ShotW, &ShotH);


	ShotAudio = LoadSoundMem("../BGM/ショット.mp3");
	HitAudio = LoadSoundMem("../BGM/ショット命中.mp3");
}
void Player::PlayerMove()
{
	{
		//ダメージを受けているかどうかで処理を分岐
		if (PackmanDamageFlag == 1)
		{
			set = 4;

			//ダメージを受けている場合はダメージグラフィックを描画する
			DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, 0, Packman[set], TRUE, PackmanReverse);
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
					set = gameptr->Coroutine(60);

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

								//弾の向かう先をセット
								sx = ShotX[i] + ShotW / 2;
								sy = ShotY[i] + ShotH / 2;

								bx = (double)gameptr->GetPosX() + (double)gameptr->GetEbw() / 2;
								by = (double)gameptr->GetPosY() + (double)gameptr->GetEbh() / 2;

								sbx = bx - sx;
								sby = by - sy;

								sb = sqrt(sbx * sbx + sby * sby);

								ShotSx = sbx / sb * ShotSpeed;
								ShotSy = sby / sb * ShotSpeed;

								//弾 iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
								ShotFlag[i] = 1;
								PlaySoundMem(ShotAudio, DX_PLAYTYPE_BACK);
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
		}

		//パックマンが画面左端からはみ出しそうになっていたら画面内の座標に戻してあげる
		if (PackmanX < -64)PackmanX = gameptr->GetWidth();

		//パックマンが画面右端からはみ出しそうになったら画面内に戻してあげる
		if (PackmanX > gameptr->GetWidth())PackmanX = 0;

		// パックマンが画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PackmanY < -64)PackmanY = gameptr->GetHeight();
		// パックマンが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PackmanY > gameptr->GetHeight())PackmanY = 0;

		DrawRotaGraph2(PackmanX, PackmanY, 16, 16, 1, Packmanrotate, Packman[set], TRUE, PackmanReverse);
	}
}
void Player::ShotMove()
{
	for (i = 0; i < SHOT; i++)
	{
		//自機の弾１の移動ルーチン(存在状態を保持している変数の内容が1(存在する)の場合のみ行う)
		if (ShotFlag[i] == 1)
		{
			//弾iを16ドット上に移動させる
			ShotX[i] += ShotSx;
			ShotY[i] += ShotSy;

			//画面外に出てしまった場合は存在状態を保持している変数に0（存在しない）を代入する
			if (ShotY[i] > gameptr->GetHeight() || ShotY[i] < 0 ||
				ShotX[i]>gameptr->GetWidth() || ShotX[i] < 0)
				ShotFlag[i] = 0;

			//ブリンキーとの当たり判定
			if (((ShotX[i] > gameptr->GetPosX() && ShotX[i] < gameptr->GetPosX() + gameptr->GetEnemyW()) ||
				(gameptr->GetPosX() > ShotX[i] && gameptr->GetPosX() < ShotX[i] + ShotW)) &&
				((ShotY[i] > gameptr->GetPosY() && ShotY[i] < gameptr->GetPosY() + gameptr->GetEnemyH()) ||
					(gameptr->GetPosY() > ShotY[i] && gameptr->GetPosY() < ShotY[i] + ShotH)))
			{

				if (gameptr->GetDamageFlag() == 0)
					//ヒットカウントを加算する
					gameptr->EhitCount++;

				//ブリンキーがダメージを受けているかどうかを保持する変数に『受けている』を表す１を代入
				gameptr->BlinkyDamageFlag = 1;

				PlaySoundMem(HitAudio, DX_PLAYTYPE_BACK);

				//ブリンキーがダメージを受けている時間を測るカウンタ変数に０を代入
				gameptr->BlinkyDamageCounter = 0;

				//接触している場合は当たった弾の存在を消す
				ShotFlag[i] = 0;
			}
			//画面に弾 i を描画する
			DrawGraph((int)ShotX[i], (int)ShotY[i], ShotGraph, TRUE);
		}
	}
}
