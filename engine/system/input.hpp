#pragma once

#include "../core/interface/inputer.hpp"
#include "component/physics.hpp"
#include "system.hpp"

// enum class Key { Up, Down, Left, Right };

struct ISParams {};

class InputSystem : public System {
public:
  InputSystem(ISParams p){};

  void update(std::vector<std::unique_ptr<Entity>> &entities) override {
    for (auto &entityPtr : entities) {
      auto *entity = entityPtr.get();
      auto *physics = entity->getComponent<PhysicsComponent>();

      if (!physics)
        continue;

      handleInput(physics);
    }
  }

  void handleInput(PhysicsComponent *physics) {
    Inputer &inputer = Inputer::instance();

    if (inputer.isPressed(JUMP))
      physics->velocityY = -30;
  }
};
