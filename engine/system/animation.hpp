#pragma once

#include "component/animation.hpp"
#include "component/render.hpp"
#include "raylib.h"

#include "system/systemInterface.hpp"

struct ASParams {};

class AnimationSystem : public SystemInterface {
public:
  AnimationSystem(ASParams p){};

  void update(std::vector<std::unique_ptr<Entity>> &entities) override {
    for (auto &entityPtr : entities) {
      auto *entity = entityPtr.get();
      auto render = entity->getComponent<RenderComponent>();
      auto animation = entity->getComponent<AnimationComponent>();

      if (!(render && animation))
        continue;

      framesCounter++;
      if (framesCounter >= 10) {
        framesCounter = 0;
        animation->currentFrame++;
        if (animation->currentFrame > animation->spriteNumber - 1)
          animation->currentFrame = 0;

        render->texture = animation->textures[animation->currentFrame];
      }
    }
  }

private:
  int framesCounter;
};
