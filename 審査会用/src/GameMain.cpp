#include "lib\appEnv.hpp"
#include "GameMain.h"
#include "OBJECT.h"
#include "Player.h"
#include "main.h"

GameMain *GM;

GameMain::GameMain()// : Blues("res/29x29blues.png")
{
	Player.reset(new PLAYER());
	//Jump.reset(new CJump());

}

void GameMain::Update()
{
	Player->Update();
	//Jump->Update();
}

void GameMain::Draw()
{
	//
	app_env->setupDraw();
	//Player->Draw();
	//Jump->Draw();

	//
	app_env->update();
}

void GameMain::Main()
{
	Update();
	Draw();
}