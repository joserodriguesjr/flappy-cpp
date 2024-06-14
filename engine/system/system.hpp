#pragma once

#include "../entity/entity.hpp"
#include <vector>

class SystemInterface {
public:
  virtual void update(std::vector<std::unique_ptr<Entity>> &entities) = 0;
  // template <typename T, typename P> void callback(P params) {
  //   systems.emplace_back(make_unique<T>(params));
  // }
  virtual ~SystemInterface() = default;
};