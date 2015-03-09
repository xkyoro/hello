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
int isPlayerMove(AppEnv& env)
{
	if (isLeftKey(env) && !isRightKey(env))
	{
		pos.L = true;
		pos.R = false;
		return -pos.vx;
	}
	if (isRightKey(env) && !isLeftKey(env))
	{
		pos.L = false;
		pos.R = true;
		return pos.vx;
	}
	else return 0;
}

//�W�����v
void Jump(AppEnv& env)
{
	//�d��
	static const float g = -0.98f;
	
	//�W�����v����
	if (env.isPressKey(GLFW_KEY_SPACE) && !pos.jumping)
	{
		pos.vy = pos.jump_power;
		pos.jumping = true;
	}

	//�W�����v���̏���
	if (pos.jumping)
	{
		pos.jumping = true;
		pos.y += pos.vy +0.5 * g;
		pos.vy += g;
	}
	
	//���n
	if (pos.y <= -HEIGHT / 2)
	{
		pos.jumping = false;
		pos.y = -HEIGHT / 2;
		pos.vy = 0.0f;
	}
}

//�܂Ƃ�
void MoveUpdate(AppEnv& env)
{
	pos.x += isPlayerMove(env);
	Jump(env);
}