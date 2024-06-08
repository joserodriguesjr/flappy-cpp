#pragma once

#include "interface/renderer.hpp"

class Sprite {
public:
  static Texture2D *loadSprites(Image image, int n_sprites);
  static void unloadSprites(Texture2D *textures, int n_sprites);

  Sprite() = delete;
};
