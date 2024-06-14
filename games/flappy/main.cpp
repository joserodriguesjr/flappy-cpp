#include <iostream>

#include "component/collider.hpp"
#include "component/physics.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"
#include "core/engine.hpp"
#include "entity/entity.hpp"
#include "system/collider.hpp"
#include "system/input.hpp"
#include "system/physics.hpp"
#include "system/render.hpp"

// ScenarioConfig scnCfg(
//       "",
//       "platform/desktop/resources/scenario/bushes.png",
//       "platform/desktop/resources/scenario/buildings.png",
//       "platform/desktop/resources/scenario/clouds.png");

//   PipeManagerConfig
//   pmCfg("platform/desktop/resources/obstacles/bottomPipe.png",
//         "platform/desktop/resources/obstacles/topPipe.png");

int main() {
  GameEngine engine;

  engine.addSystem<PhysicsSystem, PSParams>(PSParams{9.8, 10});
  engine.addSystem<RenderSystem, RSParams>(RSParams{true, 1200, 800});
  engine.addSystem<InputSystem, ISParams>({});
  engine.addSystem<CollisionSystem, CSParams>({});

  const char *playerSprite = "platform/desktop/resources/flappy/flappy_red.png";
  Entity &player = engine.createEntity("Player");
  player.addComponent<TransformComponent, TCParams>(TCParams{100, 200, 999, 1});
  player.addComponent<PhysicsComponent, PCParams>(
      PCParams{1, 0, 0, false, true});
  player.addComponent<RenderComponent, RCParams>(
      RCParams{playerSprite, true, WHITE});
  player.addComponent<ColliderComponent, CCParams>(CCParams{0, 0, true});

  player.addEvent<CollisionSystem>([&](Entity *other) {
    auto physics = player.getComponent<PhysicsComponent>();
    physics->movableY = false;
    physics->velocityX = 0;
    physics->velocityY = 0;

    std::cout << "Player collided with " << other->name << std::endl;
    if (other->name == "Ground") {
      std::cout << "Player hit the ground!" << std::endl;
    } else if (other->name == "Roof") {
      std::cout << "Player hit the roof!" << std::endl;
    }
  });

  player.addEvent<RenderSystem>([&](Entity *other) {
    auto transform = player.getComponent<TransformComponent>();
    auto physics = player.getComponent<PhysicsComponent>();
    transform->rotation = physics->velocityY * 1;

    std::cout << "Player rotation = " << transform->rotation << std::endl;
  });

  const char *pipeSprite = "platform/desktop/resources/obstacles/topPipe.png";
  Entity &pipe = engine.createEntity("Pipe");
  pipe.addComponent<TransformComponent, TCParams>(TCParams{500, 200, 1});
  pipe.addComponent<PhysicsComponent, PCParams>(
      PCParams{1, -20, 0, true, false});
  pipe.addComponent<RenderComponent, RCParams>(
      RCParams{pipeSprite, false, WHITE});
  pipe.addComponent<ColliderComponent, CCParams>(CCParams{200, 500, true});

  const char *groundSprite =
      "platform/desktop/resources/scenario/floor_complete.png";
  Entity &ground = engine.createEntity("Ground");
  ground.addComponent<TransformComponent, TCParams>(TCParams{0, 650, 2});
  ground.addComponent<ColliderComponent, CCParams>(CCParams{1200, 1, false});
  ground.addComponent<RenderComponent, RCParams>(
      RCParams{groundSprite, false, WHITE});

  Entity &roof = engine.createEntity("Roof");
  roof.addComponent<TransformComponent, TCParams>(TCParams{0, 0, 0});
  roof.addComponent<ColliderComponent, CCParams>(CCParams{1200, 1, false});

  engine.run();

  return 0;
}
