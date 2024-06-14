#pragma once

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "../component/component.hpp"
#include "../utils/memory.hpp"
#include "component/transform.hpp"

class Entity {
private:
  std::unordered_map<std::type_index, std::unique_ptr<ComponentInterface>>
      components;
  std::unordered_map<std::type_index, std::function<void(Entity *)>> events;

public:
  std::string name;
  Entity(std::string name) : name(name) {}

  template <typename T, typename P> void addComponent(P params) {
    components[typeid(T)] = make_unique<T>(params);
  }

  template <typename T> T *getComponent() {
    auto it = components.find(typeid(T));
    return it != components.end() ? dynamic_cast<T *>(it->second.get())
                                  : nullptr;
  }

  template <typename T> void addEvent(std::function<void(Entity *)> event) {
    events[typeid(T)] = event;
  }

  // todo: can be null
  template <typename T> void runEvent(Entity *other) {
    auto it = events.find(typeid(T));
    if (it != events.end()) {
      it->second(other);
    }
  }

  static bool compareByZIndex(const std::unique_ptr<Entity> &a,
                              const std::unique_ptr<Entity> &b) {
    TransformComponent *transformA = a->getComponent<TransformComponent>();
    TransformComponent *transformB = b->getComponent<TransformComponent>();
    return (transformA && transformB) ? (transformA->z < transformB->z) : false;
  }
};
