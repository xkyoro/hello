#pragma once
#include "lib/appEnv.hpp"

using namespace std;

class COBJECT
{
public:
	COBJECT(){}
	~COBJECT(){};

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

	int pressT;

	

	float press;		//ジャンプボタンを押してる時間変数
	float press2;		//ダッシュボタンを押してる時間変数
	int count;			//アニメーション用
	float action_x;		//アクションしたときに切り取り位置を変える変数ｘ
	float action_y;		//アクションしたときに切り取り位置を変える変数ｙ
	bool pressD;		//D長押し

	//ジャンプ値から変数を用意
	float normal;
	float water;
	float half;

	//重力
	const float g = -1.0f;
	//const float gravi1 = -0.05;
	//const float gravi2 = -2.0f;

	virtual void JUMP(){}
	virtual void JUMPING(){}
	virtual void DUSH(){}
	virtual void ACTION(){}
	/*virtual void Move(){}
	virtual void Draw(){}*/
	virtual void Update(){}
	//virtual void Collision(){}
};

