#include "score.h"
#include "constants.h"

void init_score(Score *score) {
  score->value = 0;
  score->position = (Vector2){10, 10};
  score->font = GetFontDefault();
  score->color = WHITE;
  score->backgroundColor = GREEN;
  score->backgroundColor.a = 100;
}

void score_update(Score *score) { score->value += SCORE_VALUE; }

void score_animation(Score *score) {
  DrawRectangle(score->position.x - 5, score->position.y, 185, 45,
                score->backgroundColor);
  DrawText(TextFormat("%06d", score->value), score->position.x,
           score->position.y, 50, score->color);
}
