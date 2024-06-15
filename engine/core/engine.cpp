#include <algorithm>

#include "component/collision.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"
#include "engine.hpp"

#include "../core/interface/renderer.hpp"

void GameEngine::run() {
  Renderer::instance().setFPS(60);

  organizeZIndex();
  changeCollisionTextures();
  runEntitiesSetup();

  while (true) {
    for (auto &system : systems) {
      system->update(entities);
    }
  }
}

bool compareByZIndex(const std::unique_ptr<Entity> &a,
                     const std::unique_ptr<Entity> &b) {
  TransformComponent *transformA = a->getComponent<TransformComponent>();
  TransformComponent *transformB = b->getComponent<TransformComponent>();
  return (transformA && transformB) ? (transformA->z < transformB->z) : false;
}

void GameEngine::organizeZIndex() {
  std::sort(
      entities.begin(), entities.end(),
      [](const std::unique_ptr<Entity> &a, const std::unique_ptr<Entity> &b) {
        return compareByZIndex(a, b);
      });
}

void GameEngine::changeCollisionTextures() {
  for (auto &entityPtr : entities) {
    Entity *entity = entityPtr.get();
    auto *render = entity->getComponent<RenderComponent>();
    auto *collision = entity->getComponent<CollisionComponent>();

    if (!(render && collision))
      continue;

    if (!collision->useTexture)
      continue;

    collision->width = render->texture.width;
    collision->height = render->texture.height;
  }
}

void GameEngine::runEntitiesSetup() {
  for (auto &entityPtr : entities) {
    Entity *entity = entityPtr.get();
    entity->runSetupFunctions();
  }
}
