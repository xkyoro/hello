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
	Init();

	//メインループ
	while (env.isOpen())
	{
		//プレイヤーの移動処理
		MoveUpdate(env);

		//描画準備
		env.setupDraw();

		isBulletsShot(env);

		//描画処理
		Draw();

		//処理の終了
		env.update();

		if (bullet[0].L)std::cout << "= L" << std::endl;
		if (bullet[0].R)std::cout << "= R" << std::endl;
	}
}
