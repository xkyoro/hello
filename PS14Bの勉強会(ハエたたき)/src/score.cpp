
#include "score.h"


void scoreSave(const int score) {
  std::ofstream fstr("res/score.txt");
  if (fstr) { fstr << score; }
}

void scoreLoad(int& score ,int& hi_score){
	std::ifstream fstr("res/score.txt");
	if (fstr){ fstr >> score; }
	hi_score = score;
}
