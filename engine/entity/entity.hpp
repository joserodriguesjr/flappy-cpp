#pragma once

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "component/componentInterface.hpp"
#include "utils/memory.hpp"

class Entity {
private:
  std::unordered_map<std::type_index, std::unique_ptr<ComponentInterface>>
      components;
  std::unordered_map<std::type_index, std::function<void(Entity *)>> events;
  std::unordered_map<std::string, std::function<void(void)>> setupFunctions;

public:
  Entity(std::string name) : name(name) {}
  std::string name;

  template <typename T, typename P> void addComponent(P params) {
    components[typeid(T)] = make_unique<T>(params);
  }

  template <typename T> T *getComponent() {
    auto it = components.find(typeid(T));
    return it != components.end() ? dynamic_cast<T *>(it->second.get())
                                  : nullptr;
  }

  template <typename T> void removeComponent() { components.erase(typeid(T)); }

  void addSetupFunction(std::string setupName,
                        std::function<void(void)> setupFn) {
    setupFunctions[setupName] = setupFn;
  }

  void runSetupFunctions() {
    for (auto setupFn : setupFunctions) {
      setupFn.second();
    }
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
};
