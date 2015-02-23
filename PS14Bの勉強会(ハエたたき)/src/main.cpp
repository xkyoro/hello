
#include "number_draw.h"
#include "score.h"
#include "lib\random.hpp"
#include "hitBox.h"
#include "TimeGage.h"
#include <iostream>
#include <time.h>

enum GM{
	Title,
	GameMain,
	Result
};

int game_scene = Title;

//ゲーム時間の初期化
const int MaxTime = 10 * 60;

int isGameTime = MaxTime;


int main() {
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
	cNumber score;
	Random rand;
	Hae hae;
	//ランダムシード
	rand.setSeed(time(NULL));

	Font font("res/MeiryoConsolas.ttf");

	font.size(40);
	
	//ゲームスコア
	int val = 0;

	//マウスのポジション
	Vec2f mouse_pos(0.0, 0.0f);

	//武器(ハエたたき)の攻撃範囲
	Vec2f Box_size(100.0f, 100.0f);


	hae.size_x = 100;
	hae.size_y = 100;

	//被攻撃時
	bool hit = false;
	bool damage = false;

	const int count[2] = { 1 * 60, 2 * 60 };
	int hit_count = count[0];//haeに攻撃ヒット時に発生する無敵時間
	int next_move = count[1];//何事もなく次に行動開始するまでの時間

	int hi_score = 0;
	while (env.isOpen()) {

		//マウスポジションの取得
		mouse_pos = env.mousePosition();

		env.setupDraw();

		switch (game_scene)
		{
		case Title:
		{
			//スコアのロード
			scoreLoad(val,hi_score);

			//タイトル画面
			font.draw("開始", Vec2f(-40, -20), Color(1, 1, 1));
			
			//左クリックでゲーム開始
			if (env.isPushButton(Mouse::LEFT)){
				game_scene = GameMain;

				//ゲーム開始時にスコアの変更
				val = 0;

				//開始時に敵座標を取得
				hae.pos.x() = rand.fromFirstToLast(-WIDTH / 2 + hae.size_x, WIDTH / 2 - hae.size_x);
				hae.pos.y() = rand.fromFirstToLast(-HEIGHT / 2 + hae.size_y, HEIGHT / 2 - hae.size_y);
			}

			break;
		}
		case GameMain:
		{
			//haeにカーソルが重なったら
			hit = mouse_hit(mouse_pos, Box_size, hae);
			
			//haeを叩いたら
			if (env.isPushButton(Mouse::LEFT) && hit && !damage) { 
				++val;
				damage = true;
			}
			
			//haeがダメージを受けたら
			if (damage){
				damage = true;
				hit_count--;
			}
			else { next_move--; }
			
			//カウントが0になったら座標の変更と各フラグの初期化
			if (hit_count == 0 || next_move == 0){
				damage = false;
				hit_count = count[0];
				next_move = count[1];
				hae.pos.x() = rand.fromFirstToLast(-WIDTH / 2 + hae.size_x, WIDTH / 2 - hae.size_x);
				hae.pos.y() = rand.fromFirstToLast(-HEIGHT / 2 + hae.size_y, HEIGHT / 2 - hae.size_y);
			}

			//ハエとハエたたきの表示
			drawFillBox(hae.pos.x(), hae.pos.y(), hae.size_x, hae.size_y, Color(1, 0, 1));
			drawFillBox(mouse_pos.x() - Box_size.x() / 2, mouse_pos.y() - Box_size.y() / 2, Box_size.x(), Box_size.y(), Color(0, 1, 1));

			//時間制限の矩形表示
			TimeGage();

			//ゲーム時間の処理
			if (isGameTime == 0){
				game_scene = Result;
				isGameTime = MaxTime;
				damage = false;
			}
			else { isGameTime--; }

			break;
		}
		case Result:

			//ハイスコアの更新
			if (val > hi_score){
				scoreSave(val);
			}
			//終了画面
			font.draw("終了", Vec2f(-40, -20), Color(1, 1, 1));

			if (env.isPressButton(Mouse::LEFT)){ game_scene = Title; }
			break;
		}

		// TIPS: 数字、座標を指定して、その位置にスコアを表示する
		score.draw(val, Vec2f(0, HEIGHT / 2 - 50));

		if (env.isPushKey(GLFW_KEY_ESCAPE) && game_scene != GameMain){ return 0; }

		env.update();
	}
}


