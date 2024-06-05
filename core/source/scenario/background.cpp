#include "background.hpp"
#include "constants.h"
#include "game/game.h"

void init_background(Background *b, Texture2D bushesTexture,
                     Texture2D buildingsTexture, Texture2D cloudsTexture) {
  b->bushesTexture = bushesTexture;
  b->bushesScrollSpeed = BUSHES_SCROLLSPEED;
  b->bushesScrollOffset = 0.0f;
  b->buildingsTexture = buildingsTexture;
  b->buildingsScrollSpeed = BUILDINGS_SCROLLSPEED;
  b->buildingsScrollOffset = 0.0f;
  b->cloudsTexture = cloudsTexture;
  b->cloudsScrollSpeed = CLOUDS_SCROLLSPEED;
  b->cloudsScrollOffset = 0.0f;
}

void background_movement(void *g, Background *b) {
  GameState *game = (GameState *)g;

  // If the offset is greater than the texture width, reset it to create a
  // looping effect
  if (game->player->alive) {
    b->bushesScrollOffset += b->bushesScrollSpeed * game->deltaTime;
    if (b->bushesScrollOffset >= b->bushesTexture.width) {
      b->bushesScrollOffset = 0.0f;
    }

    b->buildingsScrollOffset += b->buildingsScrollSpeed * game->deltaTime;
    if (b->buildingsScrollOffset >= b->buildingsTexture.width) {
      b->buildingsScrollOffset = 0.0f;
    }

    b->cloudsScrollOffset += b->cloudsScrollSpeed * game->deltaTime;
    if (b->cloudsScrollOffset >= b->cloudsTexture.width) {
      b->cloudsScrollOffset = 0.0f;
    }
  }
}

void background_animation(Background *b) {
  float cloudsHeight = 0;
  float buildingsHeight = 285;
  float bushesHeight = 380;

  DrawTextureEx(b->cloudsTexture,
                (Vector2){-b->cloudsScrollOffset, cloudsHeight}, 0.0f, 1.0f,
                WHITE);
  DrawTextureEx(
      b->cloudsTexture,
      (Vector2){b->cloudsTexture.width - b->cloudsScrollOffset, cloudsHeight},
      0.0f, 1.0f, WHITE);

  DrawTextureEx(b->buildingsTexture,
                (Vector2){-b->buildingsScrollOffset, buildingsHeight}, 0.0f,
                1.0f, WHITE);
  DrawTextureEx(b->buildingsTexture,
                (Vector2){b->buildingsTexture.width - b->buildingsScrollOffset,
                          buildingsHeight},
                0.0f, 1.0f, WHITE);

  DrawTextureEx(b->bushesTexture,
                (Vector2){-b->bushesScrollOffset, bushesHeight}, 0.0f, 1.0f,
                WHITE);
  DrawTextureEx(
      b->bushesTexture,
      (Vector2){b->bushesTexture.width - b->bushesScrollOffset, bushesHeight},
      0.0f, 1.0f, WHITE);
}