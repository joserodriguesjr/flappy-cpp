#include "score.hpp"

Score::Score()
    : value(0), position({10, 10}), font(GetFontDefault()), color(WHITE) {
  Score::backgroundColor = GREEN;
  Score::backgroundColor.a = 100;
}

void Score::update() { Score::value += SCORE_VALUE; }

void Score::setValue(int value) { Score::value = value; }

void Score::render() {
  DrawRectangle(Score::position.x - 5, Score::position.y, 185, 45,
                Score::backgroundColor);
  DrawText(TextFormat("%06d", Score::value), Score::position.x,
           Score::position.y, 50, Score::color);
}
