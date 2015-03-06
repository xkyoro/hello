//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\random.hpp"
#include <time.h>
#include <iostream>


enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

enum ENEMY{ ENEMY_MAX = 50 };

struct Enemy
{
	float x, y;
	float size_x, size_y;
	float vx, vy;
	bool active;
	bool Hit_On;
	int HP;
	int ATK;
	int DEF;
	Color color;

}enemy[ENEMY_MAX];

//プロトタイプ宣言
void Enemy_Loop(Random&);


//初期化関数
void Init(Random& random)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].size_x = 30.0f;
		enemy[i].size_y = 30.0f;
		enemy[i].x = random.fromFirstToLast(0.0f - WIDTH / 2, WIDTH / 2 - enemy[i].size_x);
		enemy[i].y = random.fromFirstToLast(0.0f - HEIGHT / 2, HEIGHT / 2 - enemy[i].size_y);
		enemy[i].active = true;
		enemy[i].Hit_On = false;
		enemy[i].HP = 10;
		enemy[i].ATK = 2;
		enemy[i].DEF = 1;
		enemy[i].color.red() = 1.0f;
		enemy[i].color.green() = 0.0f;
		enemy[i].color.blue() = 0.0f;
	}
}

//敵の描画処理
void Enemy_Draw(){
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].active){
			drawFillBox(enemy[i].x, enemy[i].y, enemy[i].size_x, enemy[i].size_y, enemy[i].color);
		}
	}
}

//マウス追従の矩形のあたり判定
void Mouse_Hit(AppEnv& env,Vec2f mouse_pos,Vec2f mouse_size){

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].active)
		{
			if (mouse_pos.x() + mouse_size.x() / 2 >= enemy[i].x
				&&mouse_pos.x() - mouse_size.x() / 2 <= enemy[i].x + enemy[i].size_x
				&&mouse_pos.y() + mouse_size.y() / 2 >= enemy[i].y
				&&mouse_pos.y() - mouse_size.y() / 2 <= enemy[i].y + enemy[i].size_y)
			{
				enemy[i].color.green() = 1;
				enemy[i].Hit_On = true;
			}
			else
			{
				enemy[i].color.green() = 0;
				enemy[i].Hit_On = false;
			}
		}
	}
}

//Clickで攻撃
void Attack_Click(AppEnv& env, Vec2f& mouse_pos)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		std::cout << enemy[i].Hit_On << std::endl;
		if (enemy[i].Hit_On && env.isPushButton(Mouse::LEFT))
		{
			enemy[i].HP -= 1;
			enemy[i].color.red() -= 0.1;
			enemy[i].color.blue() += 0.1;
		}

		if (enemy[i].HP <= 0)
		{
			enemy[i].active = false;
		}
	}
}

// 
// メインプログラム
// 
int main() 
{
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
	Random random;
	random.setSeed(time(NULL));

	
	
	Init(random);
	
	

	while (env.isOpen()) 
	{
		Vec2f mouse_pos = env.mousePosition();
		Vec2f mouse_size(20.0f, 20.0f);

		Mouse_Hit(env, mouse_pos, mouse_size);

		Attack_Click(env, mouse_pos);

		Enemy_Loop(random);

		
		env.setupDraw();


		//敵の描画
		Enemy_Draw();
		
		//マウス追従の矩形
		drawFillBox(mouse_pos.x() - mouse_size.x() / 2, mouse_pos.y() - mouse_size.y() / 2,
			        mouse_size.x(), mouse_size.y(),
					Color(1, 1, 1));

		env.update();
		
	}
}

//再描画関数
void Enemy_Loop(Random& random){
	for (int ene[2] = {}; ene[0] < ENEMY_MAX; ++ene[0])
	{

		//敵同士のあたり判定
		if (enemy[ene[1]].x - 1 < enemy[ene[0]].x + enemy[ene[0]].size_x + 1
			&& enemy[ene[1]].x + enemy[ene[1]].size_x + 1 > enemy[ene[0]].x - 1
			&& enemy[ene[1]].y - 1 < enemy[ene[0]].y + enemy[ene[0]].size_y + 1
			&& enemy[ene[1]].y + enemy[ene[1]].size_y + 1 > enemy[ene[0]].y - 1
			&& ene[1] != ene[0])
		{

			//敵の場所を再度初期化
			enemy[ene[1]].x = random.fromFirstToLast(0.0f - WIDTH / 2, WIDTH / 2 - enemy[ene[1]].size_x);
			enemy[ene[1]].y = random.fromFirstToLast(0.0f - HEIGHT / 2, HEIGHT / 2 - enemy[ene[1]].size_y);
		}

		//敵全部が１体１体あたり判定をみるための処理
		if (ene[0] >= ENEMY_MAX - 1)
		{
			if (ene[1] < ENEMY_MAX){
				ene[0] = 0;
				ene[1] += 1;
				
			}
		}
	}
}