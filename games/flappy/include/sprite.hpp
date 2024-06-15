#pragma once

#include <vector>

#include "interface/renderer.hpp"

class Sprite {
public:
  Sprite() = delete;

  static std::vector<Texture2D> loadSprites(Image image, int spritesCount) {
    std::vector<Texture2D> textures(spritesCount);
    float spriteWidth = image.width / spritesCount;
    float spriteHeight = image.height;

    for (int i = 0; i < spritesCount; i++) {
      Rectangle sourceRec = {i * spriteWidth, 0, spriteWidth, spriteHeight};
      Image subImage = Renderer::instance().cropImage(image, sourceRec);
      textures[i] = Renderer::instance().loadTexture2DFromImage(subImage);
      Renderer::instance().unloadImage(subImage);
    }
    return textures;
  }

  static void unloadSprites(std::vector<Texture2D> &textures) {
    for (auto &texture : textures) {
      Renderer::instance().unloadTexture2D(texture);
    }
    // Vector destructor will automatically free memory when textures goes out
    // of scope
  }
};
