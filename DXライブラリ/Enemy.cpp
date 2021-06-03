//#include"DxLib.h"
//#include "Player.h"
//#include"Enemy.h"
//#include<math.h>
//
//void Enemy_Initialization()
//{
//
//	//ブリンキーのグラフィックをメモリにロード＆表示座標をセット
//	BlinkyGraph = LoadGraph("../Graphic/ブリンキー.png");
//	BlinkyX = 640; BlinkyY = 100; Blinkyreverse = FALSE;
//	BlinkyMoveValue = 2;
//
//	//ブリンキーのダメージ時のグラフィックをメモリにロード
//	BlinkyDamageGraph = LoadGraph("../Graphic/ゴースト.png");
//
//	//敵の弾のグラフィックをロード
//	ETamaGraph = LoadGraph("../Graphic/EShot.png");
//
//	//ブリンキーがダメージを受けているかどうかの変数に『受けていない』を表す0を代入
//	BlinkyDamageFlag = 0;
//
//	//敵の弾のグラフィックサイズを得る
//	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);
//
//	//敵の弾が飛んでいるかどうかを保持する変数に『飛んでいない』を表す０を代入
//	ETamaFlag = 0;
//
//	//敵が弾を打つタイミングを取るための計測用変数に0を代入
//	ETamaCounter = 0;
//	//ブリンキーの移動方向をセット
//	BlinkyMuki = 1;
//
//
//	//ブリンキーのグラフィックのサイズを得る
//	GetGraphSize(BlinkyGraph, &BlinkyW, &BlinkyH);
//
//	//ブリンキーと弾の画像サイズを得る
//	GetGraphSize(BlinkyGraph, &Ebw, &Ebh);
//	GetGraphSize(ETamaGraph, &Esw, &Esh);
//
//}
//
//void Enemy_Move()
//{
//	//ダメージを受けているかどうかで処理を分岐
//	if (BlinkyDamageFlag == 1)
//	{
//		//ダメージを受けている場合はダメージグラフィックを描画する
//		DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyDamageGraph, TRUE, Blinkyreverse);
//		//ダメージを受けている時間を測るカウンターに1を加算する
//		BlinkyDamageCounter++;
//
//		//もしダメージを受け始めて３０フレーム経過していたらダメージ状態から
//		//元に戻してあげる
//		if (BlinkyDamageCounter == 30)
//		{
//			//『ダメージを受けていない』を表す０を代入
//			BlinkyDamageFlag = 0;
//		}
//	}
//	else
//	{
//		//ブリンキーの座標を移動している方向に移動する
//		if (BlinkyMuki == 1)BlinkyX += BlinkyMoveValue;
//		if (BlinkyMuki == 0)BlinkyX -= BlinkyMoveValue;
//
//		//ブリンキーが画面右端から出そうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
//		if (BlinkyX > 640)
//		{
//			BlinkyX = 640;
//			BlinkyMuki = 0;
//			Blinkyreverse = FALSE;
//		}
//
//		// ブリンキーが画面左端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
//		if (BlinkyX < 0)
//		{
//			BlinkyX = 0;
//			BlinkyMuki = 1;
//			Blinkyreverse = TRUE;
//		}
//
//		// ブリンキーを描画
//		DrawRotaGraph2(BlinkyX, BlinkyY, 16, 16, 1, 0, BlinkyGraph, TRUE, Blinkyreverse);
//
//		//弾を打つタイミングを計測するためのカウンターに１ずつを加算
//		ETamaCounter++;
//
//		//もしカウンター変数が６０だった場合は弾を打つ処理を行う
//		if (ETamaCounter == 60)
//		{
//			//もしすでに弾が『飛んでいない』状態だった場合のみ発射処理を行う
//			if (ETamaFlag == 0)
//			{
//				//弾の発射位置を設定する
//				ETamaX = BlinkyX + BlinkyW / 2 - ETamaW / 2;
//				ETamaY = BlinkyY + BlinkyH / 2 - ETamaH / 2;
//
//				//弾の移動速度を設定する
//				{
//					double sb, sbx, sby, bx, by, sx, sy;
//
//					sx = ETamaX + ETamaW / 2;
//					sy = ETamaY + ETamaH / 2;
//
//					bx = PackmanX + Bw / 2;
//					by = PackmanY + Bh / 2;
//
//					sbx = bx - sx;
//					sby = by - sy;
//
//					//平方根を求めるのに標準関数のsqrtを使う、
//					//これをつかにはmath.hをインクルードする必要がある
//					sb = sqrt(sbx * sbx + sby * sby);
//
//					//１フレーム当たり８ドット移動するようにする
//					ETamaSx = sbx / sb * 8;
//					ETamaSy = sby / sb * 8;
//				}
//
//				//弾の状態を保持する変数に『飛んでいる』を示す１を代入する
//				ETamaFlag = 1;
//
//			}
//			//弾を打つタイミングを計測するための変数に０を代入
//			ETamaCounter = 0;
//		}
//
//	}
//}
//
//void Enemy_Bullet()
//{
//
//	//敵の弾の状態が『飛んでいる』場合のみ弾の移動処理を行う
//	if (ETamaFlag == 1)
//	{
//		//弾を移動させる
//		ETamaX += ETamaSx;
//		ETamaY += ETamaSy;
//
//		//もし弾が画面下端からはみ出てしまった場合は弾の状態を『飛んでいない』
//		//を表す０にする
//		if (ETamaY > 480 || ETamaY < 0 ||
//			ETamaX>640 || ETamaX < 0)ETamaFlag = 0;
//
//		//ブリンキーとの当たり判定
//		if (((ETamaX > PackmanX && ETamaX < PackmanX + Bw) ||
//			(PackmanX > ETamaX && PackmanX < ETamaX + ETamaW)) &&
//			((ETamaY > PackmanY && ETamaY < PackmanY + Bh) ||
//				(PackmanY > ETamaY && PackmanY < ETamaY + ETamaH)))
//		{
//			//接触している場合は当たった弾の存在を消す
//			ETamaFlag = 0;
//
//			//ヒットカウントを加算する
//			hitCount++;
//		}
//
//		//画面に描画する(ETamaGraph :敵の弾のグラフィックのハンドル)
//		DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
//	}
//
//
//	//弾と敵の当たり判定、弾の数だけ繰り返す
//	for (i = 0; i < SHOT; i++)
//	{
//		//弾iが存在している場合のみ次の処理に映る
//		if (ShotFlag[i] == 1)
//		{
//			//ブリンキーとの当たり判定
//			if (((ShotX[i] > BlinkyX && ShotX[i] < BlinkyX + BlinkyW) ||
//				(BlinkyX > ShotX[i] && BlinkyX < ShotX[i] + ShotW)) &&
//				((ShotY[i] > BlinkyY && ShotY[i] < BlinkyY + BlinkyH) ||
//					(BlinkyY > ShotY[i] && BlinkyY < ShotY[i] + ShotH)))
//			{
//				//接触している場合は当たった弾の存在を消す
//				ShotFlag[i] = 0;
//
//				if (BlinkyDamageFlag == 0)
//					//ヒットカウントを加算する
//					EhitCount++;
//
//				//ブリンキーがダメージを受けているかどうかを保持する変数に『受けている』を表す１を代入
//				BlinkyDamageFlag = 1;
//
//				//ブリンキーがダメージを受けている時間を測るカウンタ変数に０を代入
//				BlinkyDamageCounter = 0;
//
//
//			}
//		}
//	}
//
//}