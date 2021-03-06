#pragma once
#include <memory>
#include <vector>
#include "OBJECT.h"
#include "lib\appEnv.hpp"


class GameMain :public COBJECT
{
public:
	GameMain();
	~GameMain(){}

	//Texture Blues;

	std::unique_ptr<COBJECT> Player;
	//std::unique_ptr<COBJECT> Jump;

	void Draw();
	void Update();
	void Main();
};

extern GameMain *GM;