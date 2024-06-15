#pragma once

#include "../core/interface/renderer.hpp"
#include "component/physics.hpp"
#include "component/transform.hpp"
#include "system/systemInterface.hpp"

struct PSParams {
  float gravity;
  float timeScaleFactor;
};

class PhysicsSystem : public SystemInterface {
public:
  PhysicsSystem(PSParams p)
      : gravity(p.gravity), timeScaleFactor(p.timeScaleFactor){};

  void update(std::vector<std::unique_ptr<Entity>> &entities) override {
    Renderer &renderer = Renderer::instance();
    float dt;

    for (auto &entityPtr : entities) {
      auto *entity = entityPtr.get();
      auto *physics = entity->getComponent<PhysicsComponent>();
      auto *transform = entity->getComponent<TransformComponent>();

      if (!(physics && transform))
        continue;

      dt = renderer.getDeltaTime() * timeScaleFactor;

      if (physics->movableY) {
        physics->velocityY += gravity * physics->mass * dt;
        transform->y += physics->velocityY * dt;
      }

      if (physics->movableX) {
        transform->x += physics->velocityX * dt;
      }
    }
  }

private:
  float gravity;
  float timeScaleFactor;
};