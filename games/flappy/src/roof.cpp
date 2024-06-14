#include "roof.hpp"

#include "component/collision.hpp"
#include "component/transform.hpp"

Roof::Roof(std::string name) : Entity(name) {
  addComponent<TransformComponent, TCParams>(TCParams{0, 0, 0});
  addComponent<CollisionComponent, CCParams>(CCParams{1200, 1, false});
}
