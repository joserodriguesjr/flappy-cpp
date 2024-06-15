#include "ground.hpp"

#include "component/collision.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"
#include "resource/resource_manager.hpp"

Ground::Ground(std::string name) : Entity(name) {
  const char *path = "platform/desktop/resources/scenario/floor_complete.png";
  Texture2D groundSprite = ResourceManager::getInstance().getTexture(path);

  addComponent<TransformComponent, TCParams>(TCParams{0, 650, 2});
  addComponent<CollisionComponent, CCParams>(CCParams{0, 0, true});
  addComponent<RenderComponent, RCParams>(RCParams{groundSprite, false, WHITE});
}
