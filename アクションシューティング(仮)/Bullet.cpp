#include "Bullet.h"

//ƒvƒŒƒCƒ„[‚ÌŒü‚«‚Å’e‚Ì‹O“¹‚ð•Ï‚¦‚é’l
int isDirection()
{
	if (pos.L)
	{
		return -10;
	}

	if (pos.R)
	{
		return 10;
	}
}

//’e”­ŽË
void isBulletsShot(AppEnv& env)
{
	static int a = BULLET_MAX - 1;


	if (env.isPushKey(GLFW_KEY_UP) && a >= 0)
	{
		bullet[a].active = true;
		bullet[a].x = pos.x + pos.size_x / 2;
		bullet[a].y = pos.y + pos.size_y * 0.6;
		a--;
	}

	if (bullet[a + 1].active)
	{
		if (bullet[a + 1].x < WIDTH / 2)
		{
			bullet[a + 1].active = true;
		}
	}


	if (bullet[a + 1].x >= WIDTH / 2 || !bullet[a + 1].active)
	{
		bullet[a + 1].active = false;
		bullet[a + 1].x = pos.x + pos.size_x / 2;
		if (a < BULLET_MAX - 1)a++;
	}

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].active)
		{
			bullet[i].x += isDirection();
			drawFillCircle(bullet[i].x, bullet[i].y, bullet[i].r, bullet[i].r, 60, Color(1, 0, 0));
		}
	}
}