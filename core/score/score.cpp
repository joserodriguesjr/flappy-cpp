#include "score.hpp"
#include <cstdio>

Score::Score() : value(0), position({10, 10}), font(), color(WHITE) {
  Score::backgroundColor = GREEN;
  Score::backgroundColor.a = 100;
}

void Score::update() { Score::value += SCORE_VALUE; }

void Score::setValue(int value) { Score::value = value; }

void Score::render() {
  renderer.drawRectangle(Score::position.x - 5, Score::position.y, 185, 45,
                         Score::backgroundColor);

  char buffer[16];                       // Buffer to hold the formatted string
  sprintf(buffer, "%06d", Score::value); // Format the score value
  renderer.drawText(buffer, Score::position.x, Score::position.y, 50,
                    Score::color);
}
