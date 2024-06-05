#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"

typedef struct Background {
  Texture2D bushesTexture;
  float bushesScrollSpeed;
  float bushesScrollOffset;
  Texture2D buildingsTexture;
  float buildingsScrollSpeed;
  float buildingsScrollOffset;
  Texture2D cloudsTexture;
  float cloudsScrollSpeed;
  float cloudsScrollOffset;
} Background;

void init_background(Background *b, Texture2D bushesTexture,
                     Texture2D buildingsTexture, Texture2D cloudsTexture);

void background_movement(void *g, Background *b);

void background_animation(Background *b);

#endif /* BACKGROUND_H */