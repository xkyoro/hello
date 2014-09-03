﻿
#pragma once

// 
// OpenGL拡張
//

#include "defines.hpp"


// 初期化
// false: 拡張機能は使えない
bool initGlExt();

// 画面更新がモニタと同期可能か調べる(OpenGLの初期化後に呼び出す事)
bool isVsyncSwap();

// モニタとの同期間隔を設定
// sync インターバル間隔(0で同期しない)
bool VsyncSwapInterval(int sync);

