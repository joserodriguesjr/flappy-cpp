#ifndef FLOOR_H
#define FLOOR_H

#include "raylib.h"

typedef struct Floor {
  Texture2D texture;
  float scrollSpeed;
  float scrollOffset;
} Floor;

void init_floor(Floor *f, Texture2D floorTexture);

void floor_movement(void *g, Floor *f);

void floor_animation(Floor *f);

#endif /* FLOOR_H */