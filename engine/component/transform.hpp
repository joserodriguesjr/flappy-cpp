#pragma once

#include "component.hpp"

struct TCParams {
  float x, y, z;
  float rotation;
  float scaleX, scaleY, scaleZ;
};

class TransformComponent : public ComponentInterface {
public:
  float x, y, z;
  float rotation;
  float scaleX, scaleY, scaleZ;

  TransformComponent(TCParams p)
      : x(p.x), y(p.y), z(p.z), rotation(p.rotation), scaleX(p.scaleX),
        scaleY(p.scaleY), scaleZ(p.scaleZ) {}
};