
#include "pipe.hpp"

#include "component/collision.hpp"
#include "component/physics.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"

Pipe::Pipe(std::string name) : Entity(name) {
  const char *pipeSprite = "platform/desktop/resources/obstacles/topPipe.png";

  addComponent<TransformComponent, TCParams>(TCParams{500, 200, 1});
  addComponent<PhysicsComponent, PCParams>(PCParams{1, -20, 0, true, false});
  addComponent<RenderComponent, RCParams>(RCParams{pipeSprite, false, WHITE});
  addComponent<CollisionComponent, CCParams>(CCParams{200, 500, true});
}