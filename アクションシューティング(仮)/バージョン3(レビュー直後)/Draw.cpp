#include "Draw.h"

//�`��֐�
void Draw()
{
	//�G1
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].active)
		{
			drawFillBox(enemy[i].x, enemy[i].y, enemy[i].size_x, enemy[i].size_y, Color(1, 0, 0));
		}
	}
	
	//�G2
	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		if (enemy2[i].active)
		{
			drawFillBox(enemy2[i].x, enemy2[i].y, enemy2[i].size_x, enemy2[i].size_y, Color(0, 1, 0));
		}
	}

	//�{�X
	if (Boss.active)
	{
		drawFillBox(Boss.x, Boss.y, Boss.size_x, Boss.size_y, Color(0, 0, 1));
	}

	//�v���C���[
	if (pos.active)
	{
		drawFillBox(pos.x, pos.y, pos.size_x, pos.size_y, Color(1, 1, 1));
	}
}