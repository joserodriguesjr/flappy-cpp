#pragma once

#include "../core/interface/inputer.hpp"
#include "component/input.hpp"
#include "component/physics.hpp"
#include "component/transform.hpp"
#include "system/systemInterface.hpp"

// enum class Key { Up, Down, Left, Right };

struct ISParams {};

class InputSystem : public SystemInterface {
public:
  InputSystem(ISParams p){};

  void update(std::vector<std::unique_ptr<Entity>> &entities) override {
    for (auto &entityPtr : entities) {
      auto *entity = entityPtr.get();
      auto *input = entity->getComponent<InputComponent>();
      auto *physics = entity->getComponent<PhysicsComponent>();
      auto *transform = entity->getComponent<TransformComponent>();

      if (!(input && physics && transform))
        continue;

      handleInput(physics, transform);
    }
  }

  void handleInput(PhysicsComponent *physics, TransformComponent *transform) {
    Inputer &inputer = Inputer::instance();

    if (inputer.isPressed(JUMP))
      physics->velocityY = -30;
  }
};
