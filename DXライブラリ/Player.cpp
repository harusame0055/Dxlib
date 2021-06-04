#include"DxLib.h"
#include "Player.h"
#include"Enemy.h"
#include<math.h>

//
//void Player_Initialization()
//{
//
//	//パックマンのグラフィックをメモリにロード＆表示座標をセット
//	Packman[0] = LoadGraph("../Graphic/パックマン1.png");
//	Packman[1] = LoadGraph("../Graphic/パックマン2.png");
//	Packman[2] = LoadGraph("../Graphic/パックマン3.png");
//	Packman[3] = LoadGraph("../Graphic/パックマン4.png");
//	PackmanX = 320; PackmanY = 350; Packmanrotate = PI / 2;
//	PackmanCounter = 0;
//	PackmanReverse = 1;
//	PackmanMoveValue = 3;
//	//パックマンが動いているかどうかの変数に(動いていない)を表す0を代入
//	BallMoveFlag = 0;
//	set = 0;
//
//
//	//パックマンと弾の画像サイズを得る
//	GetGraphSize(Packman[set], &Bw, &Bh);
//	GetGraphSize(ShotGraph, &Sw, &Sh);
//
//	//弾のグラフィックをメモリにロード
//	ShotGraph = LoadGraph("../Graphic/Shot.png");
//
//	//弾のグラフィックサイズを得る
//	GetGraphSize(ShotGraph, &ShotW, &ShotH);
//
//
//	//弾１・２が画面上に存在しているか保持する変数に『存在していない』を意味する0を代入しておく
//	for (i = 0; i < SHOT; i++)
//	{
//		ShotFlag[i] = 0;
//	}
//
//	//ショットボタンが前のフレームで押されたかどうかを保存する変数に０（押されていない）を代入
//	ShotBFlag = 0;
//
//
//}
//
//void player_animation()
//	//パックマンのアニメーション
//{
//	if (set == 3)
//		set = coroutine(60);
//
//	//パックマンが動いているなら絵が切り替わるかためにカウンタを加算する
//	if (ballmoveflag == 1)
//	{
//		packmancounter++;
//
//		//もしダメージを受け始めて３０フレーム経過していたらダメージ状態から
//		//元に戻してあげる
//		if (packmancounter == 3)
//		{
//			//『ダメージを受けていない』を表す０を代入
//			if (set == 2 || set == 3)
//				set = 0;
//			else
//				set++;
//
//			packmancounter = 0;
//
//		}
//	}
//}
//
//void player_move()
//{
//
//
//	//パックマンの操作ルーチン
//	{
//		//パックマンの移動操作
//		{
//			// ↑キーを押していたらパックマンを上に移動させる
//			if (checkhitkey(key_input_up) == 1)
//			{
//				packmany -= packmanmovevalue;
//				packmanrotate = pi / 2;
//				ballmoveflag = 1;
//				packmanreverse = 1;
//			}
//			// ↓キーを押していたらパックマンを下に移動させる
//			else if (checkhitkey(key_input_down) == 1)
//			{
//				packmany += packmanmovevalue;
//				ballmoveflag = 1;
//				packmanrotate = pi / 2;
//				packmanreverse = 0;
//			}
//			// ←キーを押していたらパックマンを左に移動させる
//			else if (checkhitkey(key_input_left) == 1)
//			{
//				packmanx -= packmanmovevalue;
//				ballmoveflag = 1;
//				packmanrotate = pi / 180;
//				packmanreverse = 1;
//			}
//			// →キーを押していたらパックマンを右に移動させる
//			else if (checkhitkey(key_input_right) == 1)
//			{
//				packmanx += packmanmovevalue;
//				ballmoveflag = 1;
//				packmanrotate = pi;
//				packmanreverse = 1;
//			}
//			else
//			{
//				ballmoveflag = 0;
//			}
//		}
//		bullet_move();
//		//パックマンが画面左端からはみ出しそうになっていたら画面内の座標に戻してあげる
//		if (packmanx < -64)packmanx = 640;
//
//		//パックマンが画面右端からはみ出しそうになったら画面内に戻してあげる
//		if (packmanx > 640)packmanx = 0;
//
//		// パックマンが画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
//		if (packmany < -64)packmany = 480;
//
//		// パックマンが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
//		if (packmany > 480)packmany = 0;
//
//		drawrotagraph2(packmanx, packmany, 16, 16, 1, packmanrotate, packman[set], true, packmanreverse);
//	}
//
//}
//
//void bullet_move()
//{
//	//スペースキーを押した場合は処理を分岐
//	if (checkhitkey(key_input_space))
//	{
//
//		set = 3;
//		//前フレームでショットボタンを押したかが保存されている変数が0だったら弾を発射
//		if (shotbflag == 0)
//		{
//			//画面上に出ていない弾があるか、弾の数だけ繰り返して調べる
//			for (i = 0; i < shot; i++)
//			{
//				//弾iが画面上に出ていない場合はその弾を画面に出す
//				if (shotflag[i] == 0)
//				{
//					//弾 i の位置をセット、位置はパックマンの中心にする
//					shotx[i] = (bw - sw) / 2 + packmanx;
//					shoty[i] = (bh - sh) / 2 + packmany;
//
//					//弾の移動速度を設定する
//					{
//						double sb, sbx, sby, bx, by, sx, sy;
//
//						sx = shotx[i] + shotw / 2;
//						sy = shoty[i] + shoth / 2;
//
//						bx = blinkyx + ebw / 2;
//						by = blinkyy + ebh / 2;
//
//						sbx = bx - sx;
//						sby = by - sy;
//
//						sb = sqrt(sbx * sbx + sby * sby);
//
//						shotsx = sbx / sb * 8;
//						shotsy = sby / sb * 8;
//
//						//弾 iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
//						shotflag[i] = 1;
//
//						//一つ球を出したので球を出すループから抜けます
//						break;
//					}
//
//				}
//			}
//		}
//
//		//前フレームでショットボタンを押されていたかを保存する変数に１（押されていた）を代入
//		shotbflag = 1;
//
//	}
//	else
//	{
//		//ショットボタンが押されていなかった場合は
//		//前フレームでショットボタンが押されていたかを保存する変数に０（おされていない）を代入
//		shotbflag = 0;
//
//	}
//
//}
//
//void player_bullet()
//{
//	//弾の数だけ弾を動かす処理を繰り返す
//	for (i = 0; i < shot; i++)
//	{
//		//自機の弾１の移動ルーチン(存在状態を保持している変数の内容が1(存在する)の場合のみ行う)
//		if (shotflag[i] == 1)
//		{
//			//弾iを16ドット上に移動させる
//			shotx[i] += shotsx;
//			shoty[i] += shotsy;
//
//			//画面外に出てしまった場合は存在状態を保持している変数に0（存在しない）を代入する
//			if (shoty[i] > 480 || shoty[i] < 0 ||
//				shotx[i]>640 || shotx[i] < 0)
//				shotflag[i] = 0;
//
//			//画面に弾 i を描画する
//			drawgraph((int)shotx[i], (int)shoty[i], shotgraph, true);
//		}
//	}
//}
//
//int coroutine(int time)
//{
//	int cortime = 0;
//	for (int i = 0; i < time; i++)
//	{
//		cortime++;
//		if (cortime == time)
//			break;
//	}
//	return 0;
//}