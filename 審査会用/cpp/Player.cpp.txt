#include "lib\appEnv.hpp"
#include "lib\random.hpp"
#include <iostream>
#include <time.h>
#include "lib\utils.hpp"
#include "Player.h"
#include "main.h"


PLAYER::PLAYER() :b("res/29x29blues.png")
{
	float x = 0.0f;
	float y = 10.0f;
	float vx = 6.0f;
	float vy = 0.0f;

	bool jumping = false;
	bool ju1 = false;
	bool pressJ = false;
	bool dash_R = true;
	bool dash_L = false;
	bool pressR = false;
	bool pressL = false;
	bool dush_on = false;
	bool jump_dush = false;

	int pressT = 0;

	float press = 0.0f;		//ジャンプボタンを押してる時間変数
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
	const float g = -1.0f;
	//const float gravi1 = -0.05;
	//const float gravi2 = -2.0f;
}

void PLAYER::JUMP(int& c, Texture& m, float& T, float& T2, float& a_x, float& a_y, int& count, bool D)
{
	c = 1;
	float a = a_x;
	float b = a_y;

	//ジャンプ中の時
	if (jumping){
		y += vy + 0.5 * g;			//落下
		vy += g;						//重力加算
		//右向きの時
		if (dash_R){
			a = 4;
			b = 2;
		}
		//左向きの時
		if (dash_L){
			a = 1;
			b = 5;
		}
		//ジャンプ中の描画
		drawTextureBox(-200 + x, -HEIGHT / 2 + y, 30 * 3, 30 * 3,
			30 * a - 30, 30 * b - 30, 30, 30,
			m,
			Color(1, 1, 1));
	}

	//着地
	if (y <= 10.0){
		y = 10.0f;
		if (!pressJ){			//押しっぱなしによる連続ジャンプ撤去
			T = 0;
		}
		if (!D){
			T2 = 0;
		}
		c = 0;
		jumping = false;
		jump_dush = false;
		//右を向いていて、Rightを押していないとき
		if (dash_R && !pressR && !jump_dush && !D&&!dush_on){
			a = 5;
			if ((count / 5) % 3){			//アニメーション処理
				a += 1;
			}
			b = 1;
		}
		//左を向いていて、Leftを押していないとき
		if (dash_L && !pressL && !jump_dush && !D&&!dush_on){
			a = 1;
			if ((count / 5) % 3){
				a += 1;
			}
			b = 4;
		}
		if (pressR &&!jump_dush&&!D&&!dush_on){
			if ((count / 10) % 2){			//右進行
				a -= 1;
			}
		}
		if (pressL && !jump_dush&&!D&&!dush_on){
			if ((count / 10) % 2){			//左進行
				a += 1;
			}
		}
		//キャラクター表示
		drawTextureBox(-200 + x, -HEIGHT / 2 + y, 30 * 3, 30 * 3,
			30 * a - 30, 30 * b - 30 / 1, 30, 30,
			m,
			Color(1, 1, 1));
		count += 1;
	}

}
//ジャンプ関数
void PLAYER::JUMPING(float& jp, bool& D){
	vy = jp;
	if (y > 5){
		vy += 7.0;
	}
	if (!jumping){
		jumping = true;
		if (jumping){
			D = false;
		}
	}
}

//ダッシュ
void PLAYER::DUSH(bool& D){
	if (dush_on&&D){
		//右向き
		if (dash_R && !jumping){
			jump_dush = false;

		}
		if (dash_R && jumping){
			jump_dush = true;
		}
		//左向き
		if (dash_L && !jumping){
			jump_dush = false;
		}
		if (dash_L && jumping){
			jump_dush = true;
		}
	}
	//ジャンプ中
	if (jump_dush&&jumping){
		if (dash_L){
			x += -vx*1.2;
		}
		if (dash_R){
			x += vx*1.2;
		}
		else if (!D){
			//x = 0;
		}
	}
}

void PLAYER::ACTION(){
	if (app_env->isPressKey(GLFW_KEY_SPACE)){
		pressJ = true;
	}
	else{
		pressJ = false;
	}
	if (app_env->isPressKey(GLFW_KEY_SPACE) && press < 13){			//Pressのさじ加減でジャンプ量が変わる
		press++;
		JUMPING(normal, pressD);
	}
	if (press > 0 && !app_env->isPressKey(GLFW_KEY_SPACE)){		//ジャンプ入力を再度出来ないようにする
		press = 30;
	}
	//Leftで左に走る
	if (app_env->isPressKey(GLFW_KEY_LEFT) && !pressR && !dush_on){
		dash_L = true;
		dash_R = false;
		pressL = true;
		pressR = false;
		x += -vx;
		action_x = 1;
		action_y = 6;

	}
	else {
		pressL = false;
	}

	//Rightで右に走る
	if (app_env->isPressKey(GLFW_KEY_RIGHT) && !pressL && !dush_on){
		dash_R = true;
		dash_L = false;
		pressR = true;
		pressL = false;
		x += vx;
		action_x = 6;
		action_y = 3;
	}
	else{
		pressR = false;
	}

	//左ダッシュ
	if (pressL && app_env->isPressKey('D') && !pressR && press2 < 13 && !jumping){
		press2++;
		pressD = true;
		dush_on = true;
		x += -vx*1.3;
		action_x = 6;
		action_y = 4;
	}

	//右ダッシュ
	if (pressR && app_env->isPressKey('D') && !pressL && press2 < 13 && !jumping){
		press2++;
		pressD = true;
		dush_on = true;
		x += vx*1.3;
		action_x = 2;
		action_y = 1;
	}

	//左ダッシュジャンプ
	if (pressL && app_env->isPressKey('D') && !pressR &&!pressD){
		jump_dush = true;
		dush_on = false;
		//pressD = true;
	}
	else{
		pressD = false;

	}

	//右ダッシュジャンプ
	if (pressR && app_env->isPressKey('D') && !pressL &&!pressD){
		jump_dush = true;
		dush_on = false;
		//pressD = true;
	}
	else{
		pressD = false;
	}

	if (!pressD && press2 > 0){
		press2 = 30;
		dush_on = false;
	}
	
}
void PLAYER::Update()
{
	ACTION();
	JUMPING(normal, pressD);
	DUSH(pressD);
	JUMP(pressT, b, press, press2, action_x, action_y, count, pressD);
}