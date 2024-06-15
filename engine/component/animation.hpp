#pragma once

#include "componentInterface.hpp"

#include "interface/color.hpp"
#include <vector>

struct ACParams {
  std::vector<Texture2D> textures;
  int spriteNumber;
  int currentFrame;
};

class AnimationComponent : public ComponentInterface {
public:
  std::vector<Texture2D> textures;
  int spriteNumber;
  int currentFrame;

  AnimationComponent(ACParams p)
      : textures(p.textures), spriteNumber(p.spriteNumber),
        currentFrame(p.currentFrame) {}
};