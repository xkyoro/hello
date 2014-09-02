﻿//
// アプリ雛形
//

#include "lib/appEnv.hpp"
#include "lib\utils.hpp"
#include "main.h"
#include "Player.h"
#include "OBJECT.h"
//using namespace std;


// アプリのウインドウサイズ
/*enum Window {
  WIDTH  = 1024,
  HEIGHT = 768
};*/

AppEnv *app_env;

/*struct Jump{

	float x;
	float y;
	float vx;
	float vy;

	bool jumping;
	bool ju1;
	bool pressJ;
	bool dash_R;
	bool dash_L;
	bool pressR;
	bool pressL;
	bool dush_on;
	bool jump_dush;
};*/


//ジャンプ関数
/*void JUMP(Jump&j, float& g, int& c, Texture& m,float& T,float& T2, float& a_x,float& a_y, int& count,bool D){
	c = 1;
	float a = a_x;
	float b = a_y;

	//ジャンプ中の時
	if (j.jumping){
		j.y += j.vy + 0.5 * g;			//落下
		j.vy += g;						//重力加算
		//右向きの時
		if (j.dash_R){
			a = 4;
			b = 2;
		}
		//左向きの時
		if (j.dash_L){
			a = 1;
			b = 5;
		}
		//ジャンプ中の描画
		drawTextureBox(-200 + j.x, -HEIGHT / 2 + j.y, 30 * 3, 30 * 3,
			30 * a - 30, 30 * b - 30, 30, 30,
			m,
			Color(1, 1, 1));
	}

	//着地
	if (j.y <= 10.0){
		j.y = 10.0f;
		if (!j.pressJ){			//押しっぱなしによる連続ジャンプ撤去
			T = 0;
		}
		if (!D){
			T2 = 0;
		}
		c = 0;
		j.jumping = false;    
		j.jump_dush = false;
		//右を向いていて、Rightを押していないとき
		if (j.dash_R && !j.pressR && !j.jump_dush && !D&&!j.dush_on){
			a = 5;
			if ((count / 5) % 3){			//アニメーション処理
				a += 1;
			}
			b = 1;
		}
		//左を向いていて、Leftを押していないとき
		if (j.dash_L && !j.pressL && !j.jump_dush && !D&&!j.dush_on){
			a = 1;
			if ((count / 5) % 3){
				a += 1;
			}
			b = 4;
		}
		if (j.pressR &&!j.jump_dush&&!D&&!j.dush_on){
			if ((count / 10) % 2){			//右進行
				a -= 1;
			}
		}
		if (j.pressL && !j.jump_dush&&!D&&!j.dush_on){
			if ((count / 10) % 2){			//左進行
				a += 1;
			}
		}
		//キャラクター表示
		drawTextureBox(-200 + j.x, -HEIGHT / 2 + j.y, 30*3, 30*3,
			30 * a - 30, 30 * b - 30/1, 30, 30,
			m,
			Color(1, 1, 1));
		count += 1;
	}
}*/


//弾数の最大値を定義
/*enum {
	SHOT_MAX = 3
};

//
struct Shot{
	bool active;

	float x;
	float y;
};*/

// 
// メインプログラム
// 

int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, true);
  //PLAYER*  player = new PLAYER();

  GM = new GameMain();

  //Texture b("res/29x29blues.png");
  /*
  //弾を配列で用意
  Shot shot_data[SHOT_MAX];

  //初期化
  //すべてを「未使用」とする
  for (int i = 0; i < elemsof(shot_data); ++i){
	  shot_data[i].active = false;
  }*/

  //ジャンプするオブジェクトを用意
  /*Jump jump = {
	  0.0f, 10.0f, 6.0f, 0.0f,
	  false, false,
	  false,
	  true, false,
	  false, false,
	  false, false
  };*/

  /*float press = 0.0f;		//ジャンプボタンを押してる時間変数
  float press2 = 0.0f;		//ダッシュボタンを押してる時間変数
  int count = 0;			//アニメーション用
  float action_x = 0.0;		//アクションしたときに切り取り位置を変える変数ｘ
  float action_y = 0.0;		//アクションしたときに切り取り位置を変える変数ｙ
  bool pressD = false;		//D長押し

  //ジャンプ値から変数を用意
  float normal = 7.0f;
  float water = 1.0f;
  float half = 30.0f;

  //重力
  float gravity = -1.0f;
  float gravi1 = -0.05;
  float gravi2 = -2.0f;*/

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;
	if (app_env.isPressKey(GLFW_KEY_ESCAPE)) return 0;
    
    // 描画準備
	GM->Main();
  }
  
  // アプリ終了
}
