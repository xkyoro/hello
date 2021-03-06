#pragma once
#include "lib\appEnv.hpp"
#include "lib\utils.hpp"
#include "main.h"
#include "GameMain.h"
#include "OBJECT.h"

class PLAYER :public COBJECT
{
public:
	PLAYER();
	~PLAYER(){}

	Texture b;

	void JUMP(int& c, Texture& m, float& T, float& T2, float& a_x, float& a_y, int& count, bool D);
	void JUMPING(float& jp, bool& D);
	void DUSH(bool& D);
	void ACTION();
	void Update();
};