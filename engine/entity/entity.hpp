#pragma once

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "component/componentInterface.hpp"
#include "utils/memory.hpp"

class Entity {
public:
  Entity(std::string name) : name(name) {}
  std::string name;

  /**
   *  @brief  Add a component to entity.
   *
   *  Use like this inside your class that inherits from Entity:
   *  addComponent<Component, ComponentParams>(ComponentParams{});
   */
  template <typename T, typename P> void addComponent(P params) {
    components[typeid(T)] = make_unique<T>(params);
  }

  /**
   *  @brief  Retrieve the component from entity.
   *
   *  Use like this inside your class that inherits from Entity:
   *  auto component = getComponent<Component>();
   */
  template <typename T> T *getComponent() {
    auto it = components.find(typeid(T));
    return it != components.end() ? dynamic_cast<T *>(it->second.get())
                                  : nullptr;
  }

  /**
   *  @brief  Remove the component from entity.
   *
   *  Use like this inside your class that inherits from Entity:
   *  removeComponent<Component>();
   */
  template <typename T> void removeComponent() { components.erase(typeid(T)); }

  /**
   *  @brief  Add a function to be run before the game starts.
   *
   *  Use like this inside your class that inherits from Entity:
   *    addSetupFunction("function-name", [&]() {});
   */
  void addSetupFunction(std::string setupName,
                        std::function<void(void)> setupFn) {
    setupFunctions[setupName] = setupFn;
  }

  /**
   *  @brief  Add an event to be run at the end of the system update.
   *
   *  Use like this inside your class that inherits from Entity:
   *    addDeferredEvent<System>([&](Entity *other) {});
   */
  template <typename T>
  void addDeferredEvent(std::function<void(Entity *)> event) {
    deferredEvents[typeid(T)] = event;
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<ComponentInterface>>
      components;
  std::unordered_map<std::type_index, std::function<void(Entity *)>>
      deferredEvents;
  std::unordered_map<std::string, std::function<void(void)>> setupFunctions;

  friend class SystemInterface;
  friend class GameEngine;

  // todo: can be null
  /**
   *  @brief  Run the event.
   *
   */
  template <typename T> void runDeferredEvent(Entity *other) {
    auto it = deferredEvents.find(typeid(T));
    if (it != deferredEvents.end()) {
      it->second(other);
    }
  }

  /**
   *  @brief  Run the setup functions.
   *
   */
  void runSetupFunctions() {
    for (auto setupFn : setupFunctions) {
      setupFn.second();
    }
  }
};
