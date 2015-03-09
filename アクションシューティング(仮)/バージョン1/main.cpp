//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Variable.h"
#include "Draw.h"
#include "Move.h"
#include "Bullet.h"
#include <iostream>

// 
// メインプログラム
// 
int main() 
{
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);

	//プレイヤーと敵の初期化処理
	Constructor();
	//メインループ
	while (env.isOpen())
	{
		//プレイヤーの移動処理
		MoveUpdate(env);

		//描画準備
		env.setupDraw();

		isBulletsShot(env);

		//描画処理
		isDraw();

		//処理の終了
		env.update();

		
	}
}
