#include "scenario.hpp"
#include "game/game.hpp"
#include "raylib.h"

// Scenario::Scenario() {
//   Scenario::floorTexture =
//   LoadTexture("resources/scenario/floor_complete.png");
//   Scenario::floorScrollSpeed = FLOOR_SCROLLSPEED;
//   Scenario::floorScrollOffset = 0.0f;

//   Scenario::bushesTexture = LoadTexture("resources/scenario/bushes.png");
//   Scenario::bushesScrollSpeed = BUSHES_SCROLLSPEED;
//   Scenario::bushesScrollOffset = 0.0f;

//   Scenario::buildingsTexture =
//   LoadTexture("resources/scenario/buildings.png");
//   Scenario::buildingsScrollSpeed = BUILDINGS_SCROLLSPEED;
//   Scenario::buildingsScrollOffset = 0.0f;

//   Scenario::cloudsTexture = LoadTexture("resources/scenario/clouds.png");
//   Scenario::cloudsScrollSpeed = CLOUDS_SCROLLSPEED;
//   Scenario::cloudsScrollOffset = 0.0f;
// }

Scenario::Scenario()
    : floorScrollSpeed(FLOOR_SCROLLSPEED), floorScrollOffset(0.0f),
      bushesScrollSpeed(BUSHES_SCROLLSPEED), bushesScrollOffset(0.0f),
      buildingsScrollSpeed(BUILDINGS_SCROLLSPEED), buildingsScrollOffset(0.0f),
      cloudsScrollSpeed(CLOUDS_SCROLLSPEED), cloudsScrollOffset(0.0f) {

  floorTexture = LoadTexture("resources/scenario/floor_complete.png");
  bushesTexture = LoadTexture("resources/scenario/bushes.png");
  buildingsTexture = LoadTexture("resources/scenario/buildings.png");
  cloudsTexture = LoadTexture("resources/scenario/clouds.png");
}

Scenario::~Scenario() {
  UnloadTexture(floorTexture);
  UnloadTexture(bushesTexture);
  UnloadTexture(buildingsTexture);
  UnloadTexture(cloudsTexture);
}

void Scenario::movement(void *g) {
  GameState *game = (GameState *)g;

  if (!game->player->alive)
    return;

  // If the offset is greater than the texture width, reset it to create a
  // looping effect

  Scenario::floorScrollOffset += Scenario::floorScrollSpeed * game->deltaTime;
  if (Scenario::floorScrollOffset >= Scenario::floorTexture.width)
    Scenario::floorScrollOffset = 0.0f;

  Scenario::bushesScrollOffset += Scenario::bushesScrollSpeed * game->deltaTime;
  if (Scenario::bushesScrollOffset >= Scenario::bushesTexture.width)
    Scenario::bushesScrollOffset = 0.0f;

  Scenario::buildingsScrollOffset +=
      Scenario::buildingsScrollSpeed * game->deltaTime;
  if (Scenario::buildingsScrollOffset >= Scenario::buildingsTexture.width)
    Scenario::buildingsScrollOffset = 0.0f;

  Scenario::cloudsScrollOffset += Scenario::cloudsScrollSpeed * game->deltaTime;
  if (Scenario::cloudsScrollOffset >= Scenario::cloudsTexture.width)
    Scenario::cloudsScrollOffset = 0.0f;
}

void Scenario::render() {
  float cloudsHeight = 0;
  float buildingsHeight = 285;
  float bushesHeight = 380;

  // Clouds
  DrawTextureEx(Scenario::cloudsTexture,
                (Vector2){-Scenario::cloudsScrollOffset, cloudsHeight}, 0.0f,
                1.0f, WHITE);
  DrawTextureEx(
      Scenario::cloudsTexture,
      (Vector2){Scenario::cloudsTexture.width - Scenario::cloudsScrollOffset,
                cloudsHeight},
      0.0f, 1.0f, WHITE);

  // Buildings
  DrawTextureEx(Scenario::buildingsTexture,
                (Vector2){-Scenario::buildingsScrollOffset, buildingsHeight},
                0.0f, 1.0f, WHITE);
  DrawTextureEx(Scenario::buildingsTexture,
                (Vector2){Scenario::buildingsTexture.width -
                              Scenario::buildingsScrollOffset,
                          buildingsHeight},
                0.0f, 1.0f, WHITE);

  // Bushes
  DrawTextureEx(Scenario::bushesTexture,
                (Vector2){-Scenario::bushesScrollOffset, bushesHeight}, 0.0f,
                1.0f, WHITE);
  DrawTextureEx(
      Scenario::bushesTexture,
      (Vector2){Scenario::bushesTexture.width - Scenario::bushesScrollOffset,
                bushesHeight},
      0.0f, 1.0f, WHITE);
}

void Scenario::floor_render() {
  // Floor needs to be rendered after the pipe to crop the bottom texture

  DrawTextureEx(Scenario::floorTexture,
                (Vector2){-Scenario::floorScrollOffset,
                          static_cast<float>(GetScreenHeight() -
                                             Scenario::floorTexture.height)},
                0.0f, 1.0f, WHITE);
  DrawTextureEx(
      Scenario::floorTexture,
      (Vector2){Scenario::floorTexture.width - Scenario::floorScrollOffset,
                static_cast<float>(GetScreenHeight() -
                                   Scenario::floorTexture.height)},
      0.0f, 1.0f, WHITE);
}
