#pragma once

#include "component.hpp"

struct CCParams {
  float width, height;
  bool useTexture;
};

class ColliderComponent : public IComponent {
public:
  float width, height;
  bool useTexture;

  ColliderComponent(CCParams p)
      : width(p.width), height(p.height), useTexture(p.useTexture) {}
};
