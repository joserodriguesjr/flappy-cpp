#pragma once

#include "../entity/entity.hpp"
#include "../system/system.hpp"

#include <memory>
#include <string>
#include <vector>

class GameEngine {
private:
  std::vector<std::unique_ptr<System>> systems;
  std::vector<std::unique_ptr<Entity>> entities;

  void organizeZIndex();

public:
  // template <typename T, typename... Args> void addSystem(Args &&...args) {
  //   systems.emplace_back(make_unique<T>(std::forward<Args>(args)...));
  // }

  template <typename T, typename P> void addSystem(P params) {
    systems.emplace_back(make_unique<T>(params));
  }

  // todo: substitute to add entity with template
  Entity &createEntity(std::string name);

  void run();
};
