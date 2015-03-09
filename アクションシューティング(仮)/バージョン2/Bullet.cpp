#include "Bullet.h"

//�v���C���[�̌����Œe�̋O����ς���l
int isDirection(int i)
{
		if (bullet[i].L)
		{
			return -10;
		}

		if (bullet[i].R)
		{
			return 10;
		}
}

//�e����
void isBulletsShot(AppEnv& env)
{
	static int a = 0;

	isPushBullets(env, a);

	DrawBullet(a);
	
}

void isPushBullets(AppEnv& env,int& a)
{
	//�\���L�[�̏�Œe����
	if (env.isPushKey(GLFW_KEY_UP) && a < BULLET_MAX)
	{
		bullet[a].active = true;
		bullet[a].x = pos.x + pos.size_x / 2;
		bullet[a].y = pos.y + pos.size_y * 0.6;
		if (pos.L)
		{
			bullet[a].L = true;
			bullet[a].R = false;
		}
		else if (pos.R)
		{
			bullet[a].R = true;
			bullet[a].L = false;
		}
		a++;
	}
}

void DrawBullet(int& a)
{
	//��ʉE�[�Œe��������(�L�E��:;.:...
	if (bullet[a - 1].x >= WIDTH / 2 || bullet[a - 1].x <= -WIDTH / 2 || !bullet[a - 1].active)
	{
		bullet[a - 1].active = false;
		bullet[a - 1].x = pos.x + pos.size_x / 2;
		if (a > 0)a--;
	}

	//�`�悳��Ă�e�̕\���ƈړ�����
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].active)
		{

			bullet[i].x += isDirection(i);
			drawFillCircle(bullet[i].x, bullet[i].y, bullet[i].r, bullet[i].r, 60, Color(1, 0, 0));


		}
	}
}