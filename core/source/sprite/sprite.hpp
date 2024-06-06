#pragma once

#include "raylib.h"

class Sprite {
public:
  static Texture2D *loadTextures(Image image, int n_sprites);
  static void unloadTextures(Texture2D *textures, int n_sprites);
};
