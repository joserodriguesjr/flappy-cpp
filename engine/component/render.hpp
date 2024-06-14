#pragma once

#include "component.hpp"

#include "../core/interface/renderer.hpp"
#include "interface/color.hpp"

struct RCParams {
  const char *path;
  bool incline;
  Tint tint;
};

class RenderComponent : public ComponentInterface {
public:
  const char *path;
  bool incline;
  Tint tint;
  Texture2D texture;

  RenderComponent(RCParams p)
      : path(p.path), incline(p.incline), tint(p.tint),
        texture(Renderer::instance().loadTexture2D(path)) {}
};