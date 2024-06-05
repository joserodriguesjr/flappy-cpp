#include "sprite.h"

Texture2D *load_textures(Image image, int n_sprites)
{
    Texture2D tmpTexture = LoadTextureFromImage(image);
    Rectangle frameRec = {0.0f, 0.0f, tmpTexture.width / n_sprites, tmpTexture.height};
    Texture2D *textures = (Texture2D *)malloc(n_sprites * sizeof(Texture2D));

    for (int i = 0; i < n_sprites; i++)
    {
        Image croppedImage = ImageFromImage(image, frameRec);
        Texture2D frameTexture = LoadTextureFromImage(croppedImage);
        UnloadImage(croppedImage);
        textures[i] = frameTexture;
        frameRec.x = (i + 1) * (tmpTexture.width / n_sprites);
    }
    UnloadTexture(tmpTexture);
    return textures;
}

void unload_textures(Texture2D *textures, int n_sprites)
{
    for (int i = 0; i < n_sprites; i++)
    {
        UnloadTexture(textures[i]);
    }
    free(textures);
}