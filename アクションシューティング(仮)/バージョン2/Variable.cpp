#include "Variable.h"

Pos pos;
Bullet bullet[BULLET_MAX];
Enemy enemy[ENEMY_MAX];
Enemy enemy2[ENEMY2_MAX];
Enemy Boss;

//初期化関数
void Init()
{
	
	//プレイヤー
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.size_x = 20.0f;
	pos.size_y = 40.0f;
	pos.jump_power = 20.0f;

	pos.vx = 5.0f;
	pos.vy = 0.0f;
	pos.HP = 20;
	pos.ATK = 2;
	pos.DEF = 0;
	pos.active = true;
	pos.jumping = true;
	pos.L = false;
	pos.R = true;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i].x = pos.x + pos.size_x / 2;
		bullet[i].y = pos.y + pos.size_y * 0.6;
		bullet[i].r = 5.0f;
		bullet[i].active = false;
		bullet[i].L = false;
		bullet[i].R = false;
	}


	//敵1
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].x = 0.0f;
		enemy[i].y = 0.0f;
		enemy[i].size_x = 25.0f;
		enemy[i].size_y = 40.0f;
		enemy[i].HP = 3;
		enemy[i].ATK = 1;
		enemy[i].DEF = 0;
		enemy[i].active = false;
		enemy[i].L = true;
		enemy[i].R = false;
	}

	//敵2
	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		enemy2[i].x = 0.0f;
		enemy2[i].y = 0.0f;
		enemy2[i].size_x = 40.0f;
		enemy2[i].size_y = 20.0f;
		enemy2[i].HP = 6;
		enemy2[i].ATK = 2;
		enemy2[i].DEF = 1;
		enemy2[i].active = false;
		enemy[i].L = true;
		enemy[i].R = false;
	}

	//ボス
	Boss.x = 0.0f;
	Boss.y = 0.0f;
	Boss.size_x = 40.0f;
	Boss.size_y = 60.0f;
	Boss.HP = 20;
	Boss.ATK = 2;
	Boss.DEF = 1;
	Boss.active = false;
	Boss.L = true;
	Boss.R = false;
}