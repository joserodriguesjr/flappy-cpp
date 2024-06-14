#include <iostream>

#include "player.hpp"

#include "component/collision.hpp"
#include "component/physics.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"
#include "system/collision.hpp"
#include "system/render.hpp"

Player::Player(std::string name) : Entity(name) {
  const char *playerSprite = "platform/desktop/resources/flappy/flappy_red.png";

  addComponent<TransformComponent, TCParams>(TCParams{100, 200, 999, 1});
  addComponent<PhysicsComponent, PCParams>(PCParams{1, 0, 0, false, true});
  addComponent<RenderComponent, RCParams>(RCParams{playerSprite, true, WHITE});
  addComponent<CollisionComponent, CCParams>(CCParams{0, 0, true});

  addEvent<CollisionSystem>([&](Entity *other) {
    auto physics = getComponent<PhysicsComponent>();
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

  addEvent<RenderSystem>([&](Entity *other) {
    auto transform = getComponent<TransformComponent>();
    auto physics = getComponent<PhysicsComponent>();
    transform->rotation = physics->velocityY * 1;
  });
}