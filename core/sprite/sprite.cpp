#include "sprite.hpp"

Texture2D *Sprite::loadSprites(Image image, int n_sprites) {
  Texture2D *textures = new Texture2D[n_sprites];
  float spriteWidth = image.width / n_sprites;
  float spriteHeight = image.height;

  for (int i = 0; i < n_sprites; i++) {
    Rectangle sourceRec = {i * spriteWidth, 0, spriteWidth, spriteHeight};
    Image subImage = Renderer::instance().cropImage(image, sourceRec);
    textures[i] = Renderer::instance().loadTexture2DFromImage(subImage);
    Renderer::instance().unloadImage(subImage);
  }
  return textures;
}

void Sprite::unloadSprites(Texture2D *textures, int n_sprites) {
  for (int i = 0; i < n_sprites; i++) {
    Renderer::instance().unloadTexture2D(textures[i]);
  }
  delete[] textures;
}