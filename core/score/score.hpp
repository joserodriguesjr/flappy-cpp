#pragma once

#include "interface/color.hpp"
#include "interface/renderer.hpp"

const unsigned int SCORE_VALUE = 50;

class Score {
private:
  Renderer &renderer = Renderer::instance();

  int value;
  Vector2 position;
  Font font;
  Tint color;
  Tint backgroundColor;

public:
  Score();

  void update();
  void setValue(int value);
  void render();
};
