#include "TimeGage.h"

void TimeGage(int x, int y){
	drawBox(x, y, 200, 30, 2, Color(1, 1, 1));
	drawFillBox(x, y, (isGameTime * 200) / MaxTime, 30, Color(0, 0, 1));
}