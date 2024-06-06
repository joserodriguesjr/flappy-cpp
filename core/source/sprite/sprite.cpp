#include "sprite.hpp"

Texture2D *Sprite::loadTextures(Image image, int n_sprites) {
  Texture2D *textures = new Texture2D[n_sprites];
  float spriteWidth = image.width / n_sprites;
  float spriteHeight = image.height;

  for (int i = 0; i < n_sprites; i++) {
    Rectangle sourceRec = {i * spriteWidth, 0, spriteWidth, spriteHeight};
    Image subImage = ImageFromImage(image, sourceRec);
    textures[i] = LoadTextureFromImage(subImage);
    UnloadImage(subImage);
  }
  return textures;
}

void Sprite::unloadTextures(Texture2D *textures, int n_sprites) {
  for (int i = 0; i < n_sprites; i++) {
    UnloadTexture(textures[i]);
  }
  delete[] textures;
}