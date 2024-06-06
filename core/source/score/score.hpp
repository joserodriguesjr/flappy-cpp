#pragma once

#include "interface/renderer.hpp"

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
