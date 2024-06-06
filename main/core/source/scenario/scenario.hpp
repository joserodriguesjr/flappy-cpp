#pragma once

#include "interface/renderer.hpp"

const float FLOOR_HEIGHT = 180;

const float FLOOR_SCROLLSPEED = 300;
const float BUSHES_SCROLLSPEED = 120;
const float BUILDINGS_SCROLLSPEED = 60;
const float CLOUDS_SCROLLSPEED = 30;

struct ScenarioConfig {
  const char *floorPath;
  const char *bushesPath;
  const char *buildingsPath;
  const char *cloudsPath;
};

class Scenario {
private:
  Renderer &renderer = Renderer::instance();
  Texture2D floorTexture;
  float floorScrollSpeed;
  float floorScrollOffset;
  Texture2D bushesTexture;
  float bushesScrollSpeed;
  float bushesScrollOffset;
  Texture2D buildingsTexture;
  float buildingsScrollSpeed;
  float buildingsScrollOffset;
  Texture2D cloudsTexture;
  float cloudsScrollSpeed;
  float cloudsScrollOffset;

public:
  Scenario(ScenarioConfig scnCfg);
  ~Scenario();

  void movement();
  void render();
  void renderFloor();
};
