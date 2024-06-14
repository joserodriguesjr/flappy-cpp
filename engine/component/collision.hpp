#pragma once

#include "component.hpp"

struct CCParams {
  float width, height;
  bool useTexture;
};

class CollisionComponent : public ComponentInterface {
public:
  float width, height;
  bool useTexture;

  CollisionComponent(CCParams p)
      : width(p.width), height(p.height), useTexture(p.useTexture) {}
};
