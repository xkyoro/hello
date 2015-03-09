#pragma once

#include "lib\appEnv.hpp"
#include "lib\font.hpp"
#include "lib\random.hpp"
#include <iostream>

enum Window 
{
	WIDTH = 512*2,
	HEIGHT = 512
};

//“G‚Ì”
enum ENEMY
{
	ENEMY_MAX = 10,
	ENEMY2_MAX = 5,
};

enum BULLES
{
	BULLET_MAX = 3
};

//ƒvƒŒƒCƒ„[î•ñ
struct Player
{
	float x, y;
	float size_x, size_y;

	float jump_power;
	float vx, vy;

	int hp;
	int atk, def;

	bool active;
	bool jumping;

	bool L, R;

	Color color;

};

struct Bullet
{
	float x, y;
	float r;
	bool active;
	bool L, R;

	Color color;
};

//“Gî•ñ
struct Enemy
{
	float x, y;
	float size_x, size_y;

	int hp;
	int atk, def;

	bool active;
	bool L, R;

	Color color;
};

extern Player player;
extern Bullet bullet[BULLET_MAX];
extern Enemy enemy[ENEMY_MAX];
extern Enemy enemy2[ENEMY2_MAX];
extern Enemy Boss;

void Init();
