#include "sprite.hpp"

Texture2D *Sprite::loadSprites(Image image, int spritesCount) {
  Texture2D *textures = new Texture2D[spritesCount];
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

void Sprite::unloadSprites(Texture2D *textures, int spritesCount) {
  for (int i = 0; i < spritesCount; i++) {
    Renderer::instance().unloadTexture2D(textures[i]);
  }
  delete[] textures;
}