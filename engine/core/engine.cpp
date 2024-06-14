#include "engine.hpp"
#include "../core/interface/renderer.hpp"
#include <algorithm>

void GameEngine::organizeZIndex() {
  std::sort(
      entities.begin(), entities.end(),
      [](const std::unique_ptr<Entity> &a, const std::unique_ptr<Entity> &b) {
        return Entity::compareByZIndex(a, b);
      });
}

void GameEngine::run() {
  Renderer::instance().setFPS(60);

  organizeZIndex();

  while (true) {
    for (auto &system : systems) {
      system->update(entities);
    }
  }
}
