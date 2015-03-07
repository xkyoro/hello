#pragma once

#include "lib\appEnv.hpp"
#include "lib\font.hpp"
#include "lib\random.hpp"

enum Window 
{
	WIDTH = 512,
	HEIGHT = 512
};

//ìGÇÃêî
enum ENEMY
{
	ENEMY_MAX = 10,
	ENEMY2_MAX = 5,
};

enum BULLES
{
	BULLET_MAX = 3
};

//ÉvÉåÉCÉÑÅ[èÓïÒ
typedef struct Player
{
	float x, y;
	float size_x, size_y;

	float jump_power;
	float vx, vy;

	int HP;
	int ATK, DEF;

	bool active;
	bool jumping;

	bool L, R;

	Color color;

}Pos;

struct Bullet
{
	float x, y;
	float r;
	bool active;

	Color color;
};

//ìGèÓïÒ
struct Enemy
{
	float x, y;
	float size_x, size_y;

	int HP;
	int ATK, DEF;

	bool active;
	bool L, R;

	Color color;
};

extern Pos pos;
extern Bullet bullet[BULLET_MAX];
extern Enemy enemy[ENEMY_MAX];
extern Enemy enemy2[ENEMY2_MAX];
extern Enemy Boss;

void Constructor();
