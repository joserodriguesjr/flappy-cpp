#pragma once

#include "component/collider.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"
#include "system/system.hpp"

struct CSParams {};

class CollisionSystem : public SystemInterface {
public:
  CollisionSystem(CSParams p) {}

  void update(std::vector<std::unique_ptr<Entity>> &entities) override {
    for (size_t i = 0; i < entities.size(); ++i) {
      auto *entityA = entities[i].get();
      auto *colliderA = entityA->getComponent<ColliderComponent>();
      auto *transformA = entityA->getComponent<TransformComponent>();

      if (!(colliderA && transformA))
        continue;

      for (size_t j = i + 1; j < entities.size(); ++j) {
        auto *entityB = entities[j].get();
        auto *colliderB = entityB->getComponent<ColliderComponent>();
        auto *transformB = entityB->getComponent<TransformComponent>();

        if (!(colliderB && transformB))
          continue;

        if (colliderA->useTexture) {
          auto *renderA = entityA->getComponent<RenderComponent>();
          colliderA->width = renderA->texture.width;
          colliderA->height = renderA->texture.height;
        }

        if (colliderB->useTexture) {
          auto *renderA = entityB->getComponent<RenderComponent>();
          colliderB->width = renderA->texture.width;
          colliderB->height = renderA->texture.height;
        }

        if (!hasCollision(colliderA, transformA, colliderB, transformB))
          continue;

        entityA->runEvent<CollisionSystem>(entityB);
        entityB->runEvent<CollisionSystem>(entityA);
      }
    }
  }

private:
  bool hasCollision(ColliderComponent *colliderA,
                    TransformComponent *transformA,
                    ColliderComponent *colliderB,
                    TransformComponent *transformB) {

    bool collisionX = transformA->x + colliderA->width >= transformB->x &&
                      transformB->x + colliderB->width >= transformA->x;
    bool collisionY = transformA->y + colliderA->height >= transformB->y &&
                      transformB->y + colliderB->height >= transformA->y;

    return (collisionX && collisionY);
  }
};