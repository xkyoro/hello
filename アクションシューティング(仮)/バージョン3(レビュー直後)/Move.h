#pragma once

#include "Variable.h"

//キー入力
bool isLeftKey(AppEnv&);
bool isRightKey(AppEnv&);

//横移動処理
int PlayerMove(AppEnv&);

//ジャンプ処理
void Jump(AppEnv&);

//プレイヤー移動まとめ
void MoveUpdate(AppEnv&);