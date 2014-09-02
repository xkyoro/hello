﻿
#pragma once

//
// 基本的な定義
//

// TIPS:std::cout をReleaseビルドで排除する
#ifdef DEBUG
#define DOUT std::cout
#else
#define DOUT 0 && std::cout
#endif

// TIPS:プリプロセッサを文字列として定義する
#define PREPRO_TO_STR(value) PREPRO_STR(value)
#define PREPRO_STR(value)    #value

// 符号無し整数の別名定義
typedef unsigned char  u_char;
typedef unsigned int   u_int;
typedef unsigned long  u_long;


// Windows特有の定義
#if defined (_MSC_VER)

// Eigenの16バイトアライメントは無効
#define EIGEN_DONT_ALIGN

// 文字リテラルをutf-8に
// FIXME:パス名に英数字以外を使うと読めない
#pragma execution_character_set("utf-8")

// TIPS:std::min std::maxを使うための定義
#define NOMINMAX

// TIPS:M_PIなどの定義を有効にする
#define _USE_MATH_DEFINES

// いくつかの余計な警告を表示しないようにする
#pragma warning (disable:4244)
#pragma warning (disable:4800)
#pragma warning (disable:4996)

// GLEWのリンク形式
#define GLEW_STATIC
// GLFWのリンク形式(Windows)
#define GLFW_DLL

#include <windows.h>

#endif
