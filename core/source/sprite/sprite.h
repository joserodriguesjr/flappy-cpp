#ifndef SPRITE_H
#define SPRITE_H

#include <stdlib.h>

#include "raylib.h"

Texture2D *load_textures(Image image, int n_sprites);

void unload_textures(Texture2D *textures, int n_sprites);

#endif /* SPRITE_H */
