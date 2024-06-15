#pragma once

#include "entity/entity.hpp"
#include <vector>

class SystemInterface {
public:
  virtual void update(std::vector<std::unique_ptr<Entity>> &entities) = 0;

  virtual ~SystemInterface() = default;

protected:
  template <typename T>
  void runEntityDeferredEvent(Entity *entity, Entity *other) {
    entity->runDeferredEvent<T>(other);
  }
};