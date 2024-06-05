#pragma once

#include "raylib.h"
#include <stdlib.h>

class Sprite {
public:
  static Texture2D *load_textures(Image image, int n_sprites);
  static void unload_textures(Texture2D *textures, int n_sprites);
};
