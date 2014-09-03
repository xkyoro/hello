﻿
//
// アプリの実行環境
//

#include "appEnv.hpp"
#include <iostream>


// width, height 生成時のサイズ
// full_screen   true: フルスクリーン
// dynamic_size  true: ウインドウサイズにあわせて画面を変更
AppEnv::AppEnv(const int width, const int height,
               const bool full_screen, const bool dynamic_size) :
  dynamic_window_size_(dynamic_size),
  window_(width, height, false, full_screen),
  window_size_(width, height),
  current_window_size_(window_size_),
  viewport_ofs_(0, 0),
  viewport_size_(width, height),
  bg_color_(0, 0, 0, 0),
  key_page_(0),
  mouse_left_press_(false),
  mouse_right_press_(false),
  mouse_pos_(0, 0),
  mouse_last_pos_(0, 0),
  mouse_current_pos_(0, 0),
  buttons_page_(0)
{
  DOUT << "AppEnv()" << std::endl;

  // Windowを画面の中央へ移動
  const auto* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(window_(), (video_mode->width - width) / 2, (video_mode->height - height) / 2);

  // GLFWのハンドルに自分自身を登録
  glfwSetWindowUserPointer(window_(), this);

  // ウインドウのサイズ変更
  glfwSetWindowSizeCallback(window_(), changeWindowSize);
    
  // キーが押された時に呼ばれる関数を登録
  glfwSetCharCallback(window_(), createCharaInfo);
  glfwSetKeyCallback(window_(), createKeyInfo);

  // マウスイベント
  glfwSetMouseButtonCallback(window_(), mouseButtonCallback);
  glfwSetCursorPosCallback(window_(), mouseMoveCallback);

  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);

  // Windowの表示開始
  glfwShowWindow(window_());

  if (full_screen) {
    // フルスクリーンはモニタによって解像度がまちまちなので、viewportで補正
    int width, height;
    glfwGetFramebufferSize(window_(), &width, &height);
    DOUT << "framebuffer size:" << width << "," << height << std::endl;

    dynamicViewport(width, height);
  }
}

AppEnv::~AppEnv() {
  DOUT << "~AppEnv()" << std::endl;
}


// アプリウインドウが開いてるならtrueを返す
bool AppEnv::isOpen() {
  return !glfwWindowShouldClose(window_());
}

// 描画準備
void AppEnv::setupDraw() {
  glViewport(viewport_ofs_.x(), viewport_ofs_.y(),
             viewport_size_.x(), viewport_size_.y());
    
  // ウインドウの内容を指定色で消去
  glClearColor(bg_color_.red(), bg_color_.green(), bg_color_.blue(), bg_color_.alpha());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // 半透明描画指示
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // 裏面は描画しない
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  // 深度テスト禁止
  glDisable(GL_DEPTH_TEST);

  // ライティング禁止
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  // 透視変換行列を作成
  auto matrix = camera_2d_(current_window_size_);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(matrix.first.data());

  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(matrix.second.data());
}

// アプリウインドウの更新
// 1. OpenGLの描画内容をウインドウに表示
// 2. キーやマウスイベントのポーリング
void AppEnv::update() {
  // GLFWへ描画指示
  glfwSwapBuffers(window_());

  // 入力(キー＆ボタン)の再初期化
  switchInputBuffer();
    
  glfwPollEvents();
}
  
// 入力(キー＆ボタン)の再初期化
void AppEnv::flushInput() {
  switchInputBuffer();
  switchInputBuffer();
}
  
// ウィンドウサイズを返す
const Vec2f& AppEnv::viewSize() const { return window_size_; }

// ウインドウの位置を変更
// pos 新しい位置
void AppEnv::windowPosition(const Vec2i& pos) {
  glfwSetWindowPos(window_(), pos.x(), pos.y());
}

// ウインドウの位置を取得
Vec2i AppEnv::windowPosition() {
  int x_pos;
  int y_pos;
  glfwGetWindowPos(window_(), &x_pos, &y_pos);
    
  return Vec2i(x_pos, y_pos);
}


// 背景色の変更
// color 色
void AppEnv::bgColor(const Color& color) { bg_color_ = color; }

  
// 押されたキーを取得
// 'A'とか'a'とか(押されてないときは0)
// キーリピート付き
u_int AppEnv::getPushedKey() const { return pushed_key_; }

  
// 当該キーが押されているならtrueを返す
// key 'A'とか'7'とか
// SOURCE:include/GLFW/glfw3.h 271〜396
bool AppEnv::isPressKey(const int key) {
  return press_keys_.find(key) != press_keys_.cend();
}
  
// 当該キーが押された瞬間trueを返す
// key 'A'とか'7'とか
// SOURCE:include/GLFW/glfw3.h 271〜396
bool AppEnv::isPushKey(const int key) {
  const auto& keys = push_keys_[key_page_ ^ 1];
  return keys.find(key) != keys.cend();
}

// 当該キーが離された瞬間trueを返す
bool AppEnv::isPullKey(const int key) {
  const auto& keys = pull_keys_[key_page_ ^ 1];
  return keys.find(key) != keys.cend();
}

  
// マウスのカーソル位置を返す
const Vec2f& AppEnv::mousePosition() const { return mouse_current_pos_; }

// 当該ボタンが押されているならtrueを返す
// button Mouse::LEFT
//        Mouse::Right
bool AppEnv::isPressButton(const int button) {
  return press_buttons_.find(button) != press_buttons_.cend();
}
  
// 当該ボタンが押された瞬間trueを返す
// button Mouse::LEFT
//        Mouse::RIGHT
bool AppEnv::isPushButton(const int button) {
  const auto& buttons = push_buttons_[buttons_page_ ^ 1];
  return buttons.find(button) != buttons.cend();
}

// 当該ボタンが離された瞬間trueを返す
// button Mouse::LEFT
//        Mouse::RIGHT
bool AppEnv::isPullButton(const int button) {
  const auto& buttons = pull_buttons_[buttons_page_ ^ 1];
  return buttons.find(button) != buttons.cend();
}

  
// キーが押された時に呼び出される
void AppEnv::createCharaInfo(GLFWwindow* window, const u_int chara) {
  auto* const obj = static_cast<AppEnv*>(glfwGetWindowUserPointer(window));
    
  obj->pushed_key_ = chara;
}

void AppEnv::createKeyInfo(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
  auto* const obj = static_cast<AppEnv*>(glfwGetWindowUserPointer(window));

  // キーのpush,press,pull情報を生成
  switch (action) {
  case GLFW_PRESS:
    obj->push_keys_[obj->key_page_].insert(std::set<int>::value_type(key));
    obj->press_keys_.insert(std::set<int>::value_type(key));
    break;

  case GLFW_RELEASE:
    obj->pull_keys_[obj->key_page_].insert(std::set<int>::value_type(key));
    obj->press_keys_.erase(key);
    break;
  }
}

void AppEnv::changeWindowSize(GLFWwindow* window, const int width, const int height) {
  // ウインドウサイズの変更をアプリに伝える
  auto* const obj = static_cast<AppEnv*>(glfwGetWindowUserPointer(window));
  if (obj->dynamic_window_size_) {
    // 描画サイズは固定(アスペクト比固定)
    obj->dynamicViewport(width, height);
  }
  else {
    // Windowのサイズと描画サイズは一致
    obj->current_window_size_ << width, height;
    obj->viewport_size_ << width, height;
  }
}


void AppEnv::mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
  auto* const obj = static_cast<AppEnv*>(glfwGetWindowUserPointer(window));

  // ボタン入力情報を生成
  switch (action) {
  case GLFW_PRESS:
    obj->push_buttons_[obj->buttons_page_].insert(std::set<int>::value_type(button));
    obj->press_buttons_.insert(std::set<int>::value_type(button));
    break;

  case GLFW_RELEASE:
    obj->pull_buttons_[obj->buttons_page_].insert(std::set<int>::value_type(button));
    obj->press_buttons_.erase(button);
    break;
  }
    
  double x_pos, y_pos;
  glfwGetCursorPos(obj->window_(), &x_pos, &y_pos);

  // TIPS:位置はmouseMoveCallbackで更新される
#if 0
  obj->mouse_current_pos_ = screenPosition(Vec2f(x_pos, y_pos), obj->current_window_size_);
  // TIPS:Yは上下が逆
  obj->mouse_current_pos_.y() = -obj->mouse_current_pos_.y();
#endif
    
  switch (button) {
  case GLFW_MOUSE_BUTTON_LEFT:
    obj->mouse_left_press_ = (action == GLFW_PRESS) ? true : false;
    obj->mouse_pos_ << x_pos, y_pos;
    break;

  case GLFW_MOUSE_BUTTON_RIGHT:
    obj->mouse_right_press_ = (action == GLFW_PRESS) ? true : false;
    obj->mouse_pos_ << x_pos, y_pos;
    break;
  }
}

void AppEnv::mouseMoveCallback(GLFWwindow* window, const double x_pos, const double y_pos) {
  auto* const obj = static_cast<AppEnv*>(glfwGetWindowUserPointer(window));
    
  obj->mouse_current_pos_ = screenPosition(Vec2f(x_pos - obj->viewport_ofs_.x(), y_pos - obj->viewport_ofs_.y()),
                                           obj->current_window_size_,
                                           Vec2f(obj->viewport_size_.x(), obj->viewport_size_.y()));
  // TIPS:Yは上下が逆
  obj->mouse_current_pos_.y() = -obj->mouse_current_pos_.y();

  if (!obj->mouse_left_press_ && !obj->mouse_right_press_) return;

  obj->mouse_last_pos_ = obj->mouse_pos_;
  obj->mouse_pos_ << x_pos, y_pos;
}

// 画面中央が(0, 0)の座標を計算
Vec2f AppEnv::screenPosition(const Vec2f& pos, const Vec2f& window, const Vec2f& viewport) {
  // ウインドウサイズと描画サイズの違いも考慮する
  Vec2f screen_rate(window.x() / viewport.x(), window.y() / viewport.y());
  Vec2f view_pos(pos - viewport / 2.0f);
  return Vec2f(view_pos.x() * screen_rate.x(), view_pos.y() * screen_rate.y());
}

// 入力バッファを切り替える
void AppEnv::switchInputBuffer() {
  pushed_key_ = 0;
  key_page_ ^= 1;

  push_keys_[key_page_].clear();
  pull_keys_[key_page_].clear();

  buttons_page_ ^= 1;

  push_buttons_[buttons_page_].clear();
  pull_buttons_[buttons_page_].clear();
}

// 動的Viewport(アスペクト比固定)
void AppEnv::dynamicViewport(const int width, const int height) {
  // 描画サイズは固定(アスペクト比固定)
  float view_width  = window_size_.x();
  float view_height = window_size_.y();

  // アスペクト比から縦に揃えるか横に揃えるか決める
  float view_aspect   = view_height / view_width;
  float window_aspect = float(height) / float(width);
  if (view_aspect < window_aspect) {
    int window_width  = width;
    int window_height = width * view_aspect;

    // 上下に余白が入る
    viewport_ofs_  << 0, (height - window_height) / 2;
    viewport_size_ << window_width, window_height;
  }
  else {
    int window_width  = height / view_aspect;
    int window_height = height;

    // 左右に余白が入る
    viewport_ofs_  << (width - window_width) / 2, 0;
    viewport_size_ << window_width, window_height;
  }
}
  
