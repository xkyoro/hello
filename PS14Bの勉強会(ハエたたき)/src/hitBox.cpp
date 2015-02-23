#include "hitBox.h"


bool mouse_hit(Vec2f mouse_pos, Vec2f size, Hae hae){
	if (mouse_pos.x() - size.x() / 2 < hae.pos.x() + hae.size_x
		&& mouse_pos.x() + size.x() / 2 > hae.pos.x()
		&& mouse_pos.y() - size.y() / 2 < hae.pos.y() + hae.size_y
		&& mouse_pos.y() + size.y() / 2 > hae.pos.y()){
		return true;
	}
	else return false;
}
