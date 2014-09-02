/*#include "Jump.h"
#include "OBJECT.h"
#include "lib\appEnv.hpp"
#include "Player.h"
#include "main.h"
#include "GameMain.h"



CJump::CJump()
{
	x = 0.0f;
	y = 10.0f;
	vy = 0.0f;

	jumping = false;
	ju1 = false;
	pressJ = false;
	dash_R = true;
	dash_L = false;
	pressR = false;
	pressL = false;
	dush_on = false;
	jump_dush = false;

	press = 0.0f;		//ジャンプボタンを押してる時間変数
	press2 = 0.0f;		//ダッシュボタンを押してる時間変数
	count = 0;			//アニメーション用
	action_x = 0.0;		//
	action_y = 0.0;		//
	Dpress = false;

	//ジャンプ値から変数を用意
	normal = 7.0f;
	//water = 1.0f;
	//half = 30.0f;

	//重力
	gravity = -1.0f;
	//gravi1 = -0.05;
	//gravi2 = -2.0f;
}


void CJump::Move()
{
	int pressT = 0;
	pressT = 1;
	float a = action_x;
	float b = action_y;
	if (jumping){
		y += vy + 0.5 * gravity;
		vy += gravity;
		if (dash_R){
			a = 4;
			b = 2;
		}
		if (dash_L){
			a = 1;
			b = 5;
		}
		drawTextureBox(-200 + x, -Window::HEIGHT / 2 + y, 30 * 3, 30 * 3,
			30 * a - 30, 30 * b - 30, 30, 30,
			GM->Blues,
			Color(1, 1, 1));
	}
	if (y <= 10.0){
		y = 10.0f;
		if (!pressJ){			//押しっぱなしによる連続ジャンプ撤去
			press = 0;
		}
		if (!Dpress){
			press2 = 0;
		}
		pressT = 0;
		jumping = false;

		//右を向いていて、Sを押していないとき
		if (dash_R && !pressR&&!jump_dush){
			a = 5;
			if ((count / 5) % 3){			//アニメーション処理
				a += 1;
			}
			b = 1;
		}
		//左を向いていて、Aを押していないとき
		if (dash_L && !pressL&&!jump_dush){
			a = 1;
			if ((count / 5) % 3){
				a += 1;
			}
			b = 4;
		}
		if (pressR&&!jump_dush){
			if ((count / 10) % 2){			//右進行
				a -= 1;
			}
		}
		if (pressL&&!jump_dush){
			if ((count / 10) % 2){			//左進行
				a += 1;
			}
		}
		//キャラクター表示
		drawTextureBox(-200 + x, -Window::HEIGHT / 2 + y, 30 * 3, 30 * 3,
			30 * a - 30, 30 * b - 30 / 1, 30, 30,
			GM->Blues,
			Color(1, 1, 1));
		count += 1;
	}
}
void CJump::Draw()
{

}
void CJump::Update()
{
	Move();
}*/