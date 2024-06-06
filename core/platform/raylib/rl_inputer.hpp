#pragma once

#include "interface/inputer.hpp"
#include "raylib.h"
#include <cstdio>

class RaylibInputer : public Inputer {
public:
  bool IsPressed(int key) override {
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
