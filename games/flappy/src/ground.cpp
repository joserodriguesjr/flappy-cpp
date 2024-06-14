#include "ground.hpp"

#include "component/collision.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"

Ground::Ground(std::string name) : Entity(name) {
  const char *groundSprite =
      "platform/desktop/resources/scenario/floor_complete.png";

  addComponent<TransformComponent, TCParams>(TCParams{0, 650, 2});
  addComponent<CollisionComponent, CCParams>(CCParams{1200, 1, false});
  addComponent<RenderComponent, RCParams>(RCParams{groundSprite, false, WHITE});
}
