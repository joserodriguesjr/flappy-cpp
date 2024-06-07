#include "scenario.hpp"
#include "game/game.hpp"

Scenario::Scenario(ScenarioConfig scnCfg)
    : floorTexture(renderer.loadTexture2D(scnCfg.floorPath)),
      floorScrollSpeed(FLOOR_SCROLLSPEED), floorScrollOffset(0.0f),
      bushesTexture(renderer.loadTexture2D(scnCfg.bushesPath)),
      bushesScrollSpeed(BUSHES_SCROLLSPEED), bushesScrollOffset(0.0f),
      buildingsTexture(renderer.loadTexture2D(scnCfg.buildingsPath)),
      buildingsScrollSpeed(BUILDINGS_SCROLLSPEED), buildingsScrollOffset(0.0f),
      cloudsTexture(renderer.loadTexture2D(scnCfg.cloudsPath)),
      cloudsScrollSpeed(CLOUDS_SCROLLSPEED), cloudsScrollOffset(0.0f) {}

Scenario::~Scenario() {
  renderer.unloadTexture2D(floorTexture);
  renderer.unloadTexture2D(bushesTexture);
  renderer.unloadTexture2D(buildingsTexture);
  renderer.unloadTexture2D(cloudsTexture);
}

void Scenario::movement() {
  GameState &game = GameState::instance();

  // If the offset is greater than the texture width, reset it to create a
  // looping effect

  Scenario::floorScrollOffset += Scenario::floorScrollSpeed * game.deltaTime;
  if (Scenario::floorScrollOffset >= Scenario::floorTexture.width)
    Scenario::floorScrollOffset = 0.0f;

  Scenario::bushesScrollOffset += Scenario::bushesScrollSpeed * game.deltaTime;
  if (Scenario::bushesScrollOffset >= Scenario::bushesTexture.width)
    Scenario::bushesScrollOffset = 0.0f;

  Scenario::buildingsScrollOffset +=
      Scenario::buildingsScrollSpeed * game.deltaTime;
  if (Scenario::buildingsScrollOffset >= Scenario::buildingsTexture.width)
    Scenario::buildingsScrollOffset = 0.0f;

  Scenario::cloudsScrollOffset += Scenario::cloudsScrollSpeed * game.deltaTime;
  if (Scenario::cloudsScrollOffset >= Scenario::cloudsTexture.width)
    Scenario::cloudsScrollOffset = 0.0f;
}

void Scenario::render() {
  float cloudsHeight = 0;
  float buildingsHeight = 285;
  float bushesHeight = 380;

  // Clouds
  renderer.drawTextureEx(Scenario::cloudsTexture,
                         (Vector2){-Scenario::cloudsScrollOffset, cloudsHeight},
                         0.0f, 1.0f, WHITE);
  renderer.drawTextureEx(
      Scenario::cloudsTexture,
      (Vector2){Scenario::cloudsTexture.width - Scenario::cloudsScrollOffset,
                cloudsHeight},
      0.0f, 1.0f, WHITE);

  // Buildings
  renderer.drawTextureEx(
      Scenario::buildingsTexture,
      (Vector2){-Scenario::buildingsScrollOffset, buildingsHeight}, 0.0f, 1.0f,
      WHITE);
  renderer.drawTextureEx(Scenario::buildingsTexture,
                         (Vector2){Scenario::buildingsTexture.width -
                                       Scenario::buildingsScrollOffset,
                                   buildingsHeight},
                         0.0f, 1.0f, WHITE);

  // Bushes
  renderer.drawTextureEx(Scenario::bushesTexture,
                         (Vector2){-Scenario::bushesScrollOffset, bushesHeight},
                         0.0f, 1.0f, WHITE);
  renderer.drawTextureEx(
      Scenario::bushesTexture,
      (Vector2){Scenario::bushesTexture.width - Scenario::bushesScrollOffset,
                bushesHeight},
      0.0f, 1.0f, WHITE);
}

void Scenario::renderFloor() {
  // Floor needs to be rendered after the pipe to crop the bottom texture

  renderer.drawTextureEx(
      Scenario::floorTexture,
      (Vector2){-Scenario::floorScrollOffset,
                static_cast<float>(renderer.getScreenHeight() -
                                   Scenario::floorTexture.height)},
      0.0f, 1.0f, WHITE);
  renderer.drawTextureEx(
      Scenario::floorTexture,
      (Vector2){Scenario::floorTexture.width - Scenario::floorScrollOffset,
                static_cast<float>(renderer.getScreenHeight() -
                                   Scenario::floorTexture.height)},
      0.0f, 1.0f, WHITE);
}
