#ifndef SCORE_H
#define SCORE_H

#include "raylib.h"

typedef struct Score {
  int value;
  Vector2 position;
  Font font;
  Color color;
  Color backgroundColor;
} Score;

void init_score(Score *score);
void score_update(Score *score);
void score_animation(Score *score);

#endif // SCORE_H