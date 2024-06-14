#pragma once

#include "component.hpp"

struct PCParams {
  float mass, velocityX, velocityY;
  bool movableX, movableY;
};

class PhysicsComponent : public ComponentInterface {
public:
  float mass;
  float velocityX, velocityY;
  bool movableX, movableY;
  PhysicsComponent(PCParams p)
      : mass(p.mass), velocityX(p.velocityX), velocityY(p.velocityY),
        movableX(p.movableX), movableY(p.movableY) {}
};