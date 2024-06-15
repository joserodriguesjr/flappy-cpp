#pragma once

#include "component/collision.hpp"
#include "component/transform.hpp"
#include "system/systemInterface.hpp"

struct CSParams {};

class CollisionSystem : public SystemInterface {
public:
  CollisionSystem(CSParams p) {}

  void update(std::vector<std::unique_ptr<Entity>> &entities) override {
    for (size_t i = 0; i < entities.size(); ++i) {
      auto *entityA = entities[i].get();
      auto *collisionA = entityA->getComponent<CollisionComponent>();
      auto *transformA = entityA->getComponent<TransformComponent>();

      if (!(collisionA && transformA))
        continue;

      for (size_t j = i + 1; j < entities.size(); ++j) {
        auto *entityB = entities[j].get();
        auto *collisionB = entityB->getComponent<CollisionComponent>();
        auto *transformB = entityB->getComponent<TransformComponent>();

        if (!(collisionB && transformB))
          continue;

        if (!hasCollision(collisionA, transformA, collisionB, transformB))
          continue;

        entityA->runEvent<CollisionSystem>(entityB);
        entityB->runEvent<CollisionSystem>(entityA);
      }
    }
  }

private:
  bool hasCollision(CollisionComponent *collisionA,
                    TransformComponent *transformA,
                    CollisionComponent *collisionB,
                    TransformComponent *transformB) {

    bool collisionX = transformA->x + collisionA->width >= transformB->x &&
                      transformB->x + collisionB->width >= transformA->x;
    bool collisionY = transformA->y + collisionA->height >= transformB->y &&
                      transformB->y + collisionB->height >= transformA->y;

    return (collisionX && collisionY);
  }
};