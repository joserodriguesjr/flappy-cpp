#pragma once

#include "raylib.h"

const unsigned int SCORE_VALUE = 50;

class Score {
private:
  int value;
  Vector2 position;
  Font font;
  Color color;
  Color backgroundColor;

public:
  Score();

  void update();
  void setValue(int value);
  void render();
};
