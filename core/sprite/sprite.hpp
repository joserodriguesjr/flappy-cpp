#pragma once

#include "interface/renderer.hpp"

class Sprite {
public:
  static Texture2D *loadSprites(Image image, int spritesCount);
  static void unloadSprites(Texture2D *textures, int spritesCount);

  Sprite() = delete;
};
