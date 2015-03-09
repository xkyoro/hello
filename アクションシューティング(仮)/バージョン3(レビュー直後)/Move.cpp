#include "Move.h"

//左キー
bool isLeftKey(AppEnv& env)
{
	if (env.isPressKey('A') || env.isPressKey(GLFW_KEY_LEFT))
	{
		return true;
	}
	else return false;
}

//右キー
bool isRightKey(AppEnv& env)
{
	if (env.isPressKey('D') || env.isPressKey(GLFW_KEY_RIGHT))
	{
		return true;
	}
	else return false;
}

//横移動
int PlayerMove(AppEnv& env)
{
	if (isLeftKey(env) && !isRightKey(env))
	{
		player.L = true;
		player.R = false;
		return -player.vx;
	}
	if (isRightKey(env) && !isLeftKey(env))
	{
		player.L = false;
		player.R = true;
		return player.vx;
	}
	else return 0;
}

//ジャンプ
void Jump(AppEnv& env)
{
	//重力
	static const float g = -0.98f;
	
	//ジャンプ入力
	if (env.isPressKey(GLFW_KEY_SPACE) && !player.jumping)
	{
		player.vy = player.jump_power;
		player.jumping = true;
	}

	//ジャンプ中の処理
	if (player.jumping)
	{
		player.jumping = true;
		player.y += player.vy +0.5 * g;
		player.vy += g;
	}
	
	//着地
	if (player.y <= -HEIGHT / 2)
	{
		player.jumping = false;
		player.y = -HEIGHT / 2;
		player.vy = 0.0f;
	}
}

//まとめ
void MoveUpdate(AppEnv& env)
{
	player.x += PlayerMove(env);
	Jump(env);
}