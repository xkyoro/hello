#pragma once

#include "lib\appEnv.hpp"


//“Gî•ñ
struct Hae
{
	Vec2f pos;
	int size_x, size_y;
};

bool mouse_hit(Vec2f mouse_pos, Vec2f size, Hae hae);