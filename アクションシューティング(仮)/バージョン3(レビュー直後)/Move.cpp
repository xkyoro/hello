#include "Move.h"

//���L�[
bool isLeftKey(AppEnv& env)
{
	if (env.isPressKey('A') || env.isPressKey(GLFW_KEY_LEFT))
	{
		return true;
	}
	else return false;
}

//�E�L�[
bool isRightKey(AppEnv& env)
{
	if (env.isPressKey('D') || env.isPressKey(GLFW_KEY_RIGHT))
	{
		return true;
	}
	else return false;
}

//���ړ�
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

//�W�����v
void Jump(AppEnv& env)
{
	//�d��
	static const float g = -0.98f;
	
	//�W�����v����
	if (env.isPressKey(GLFW_KEY_SPACE) && !player.jumping)
	{
		player.vy = player.jump_power;
		player.jumping = true;
	}

	//�W�����v���̏���
	if (player.jumping)
	{
		player.jumping = true;
		player.y += player.vy +0.5 * g;
		player.vy += g;
	}
	
	//���n
	if (player.y <= -HEIGHT / 2)
	{
		player.jumping = false;
		player.y = -HEIGHT / 2;
		player.vy = 0.0f;
	}
}

//�܂Ƃ�
void MoveUpdate(AppEnv& env)
{
	player.x += PlayerMove(env);
	Jump(env);
}