﻿
#pragma once

//
// アプリの実行環境
//

#include "defines.hpp"
#include <array>
#include <set>
#include "glfwWindow.hpp"
#include "vector.hpp"
#include "camera2D.hpp"
#include "graph.hpp"
#include "audio.hpp"
#include "os.hpp"


// マウスボタンの省略名を定義
enum Mouse {
  LEFT  = GLFW_MOUSE_BUTTON_LEFT,
  RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
};


class AppEnv {
  // OS固有処理
  Os os_;
  
  // 描画ウィンドウ
  GlfwWindow window_;

  // 描画領域のサイズをWindowのサイズと連動する
  bool dynamic_window_size_;

  // 生成時のウィンドウサイズ
  Vec2f window_size_;
  
  // 現在のウィンドウサイズ
  Vec2f current_window_size_;

  Vec2i viewport_ofs_;
  Vec2i viewport_size_;
  
  
  // 2D座標変換用カメラ
  Camera2D camera_2d_;

  Color bg_color_;

  
  // キー入力関連
  u_int pushed_key_;

  std::array<std::set<int>, 2> push_keys_;
  std::array<std::set<int>, 2> pull_keys_;
  std::set<int> press_keys_;
  int key_page_;

  // マウス関連
  bool  mouse_left_press_;
  bool  mouse_right_press_;
  Vec2f mouse_pos_;
  Vec2f mouse_last_pos_;
  Vec2f mouse_current_pos_;

  std::array<std::set<int>, 2> push_buttons_;
  std::array<std::set<int>, 2> pull_buttons_;
  std::set<int> press_buttons_;
  int buttons_page_;

  // サウンド関連
  Audio audio_;
  
  
public:
  // width, height 生成時のサイズ
  // full_screen   true: フルスクリーン
  // dynamic_size  true: ウインドウサイズにあわせて画面を変更
  AppEnv(const int width, const int height,
         const bool full_screen = false, const bool dynamic_size = false);

  ~AppEnv();

  // このクラスはコピー禁止
  AppEnv(const AppEnv&) = delete;
  AppEnv& operator=(const AppEnv&) = delete;


  // アプリウインドウが開いてるならtrueを返す
  bool isOpen();

  // 描画準備
  void setupDraw();

  // アプリウインドウの更新
  // 1. OpenGLの描画内容をウインドウに表示
  // 2. キーやマウスイベントのポーリング
  void update();
  
  // 入力(キー＆ボタン)の再初期化
  void flushInput();
  
  // ウィンドウサイズを返す
  const Vec2f& viewSize() const;

  // ウインドウの位置を変更
  // pos 新しい位置
  void windowPosition(const Vec2i& pos);

  // ウインドウの位置を取得
  Vec2i windowPosition();


  // 背景色の変更
  // color 色
  void bgColor(const Color& color);

  
  // 押されたキーを取得
  // 'A'とか'a'とか(押されてないときは0)
  // キーリピート付き
  u_int getPushedKey() const;

  
  // 当該キーが押されているならtrueを返す
  // key 'A'とか'7'とか
  // SOURCE:include/GLFW/glfw3.h 271〜396
  bool isPressKey(const int key);
  
  // 当該キーが押された瞬間trueを返す
  // key 'A'とか'7'とか
  // SOURCE:include/GLFW/glfw3.h 271〜396
  bool isPushKey(const int key);

  // 当該キーが離された瞬間trueを返す
  bool isPullKey(const int key);

  
  // マウスのカーソル位置を返す
  const Vec2f& mousePosition() const;

  // 当該ボタンが押されているならtrueを返す
  // button Mouse::LEFT
  //        Mouse::Right
  bool isPressButton(const int button);
  
  // 当該ボタンが押された瞬間trueを返す
  // button Mouse::LEFT
  //        Mouse::RIGHT
  bool isPushButton(const int button);

  // 当該ボタンが離された瞬間trueを返す
  // button Mouse::LEFT
  //        Mouse::RIGHT
  bool isPullButton(const int button);

  
private:
  // キーが押された時に呼び出される
  static void createCharaInfo(GLFWwindow* window, const u_int chara);

  static void createKeyInfo(GLFWwindow* window,
                            const int key, const int scancode, const int action, const int mods);

  static void changeWindowSize(GLFWwindow* window, const int width, const int height);

  
  static void mouseButtonCallback(GLFWwindow* window,
                                  const int button, const int action, const int mods);

  static void mouseMoveCallback(GLFWwindow* window,
                                const double x_pos, const double y_pos);

  // 画面中央が(0, 0)の座標を計算
  static Vec2f screenPosition(const Vec2f& pos, const Vec2f& window, const Vec2f& viewport);

  // 入力バッファを切り替える
  void switchInputBuffer();

  // 動的Viewport(アスペクト比固定)
  void dynamicViewport(const int width, const int height);
  
};
