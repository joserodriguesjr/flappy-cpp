#pragma once

#include "interface/inputer.hpp"
#include "raylib.h"

class RaylibInputer : public Inputer {
private:
  RaylibInputer() = default;
  ~RaylibInputer() = default;
  RaylibInputer(const RaylibInputer &) = delete;
  RaylibInputer &operator=(const RaylibInputer &) = delete;

public:
  static RaylibInputer &instance() {
    static RaylibInputer instance;
    return instance;
  }

  void init() override { ; }

  bool isPressed(int key) override {
    if (key == RESTART)
      return IsKeyPressed(KEY_R);
    else if (key == JUMP)
      return IsKeyPressed(KEY_SPACE);
    else if (key == QUIT)
      return WindowShouldClose();
    else
      return false;
  }
};
