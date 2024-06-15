#pragma once

#include "componentInterface.hpp"

#include "interface/color.hpp"

struct RCParams {
  Texture2D texture;
  bool incline;
  Tint tint;
};

class RenderComponent : public ComponentInterface {
public:
  Texture2D texture;
  bool incline;
  Tint tint;

  RenderComponent(RCParams p)
      : texture(p.texture), incline(p.incline), tint(p.tint) {}
};