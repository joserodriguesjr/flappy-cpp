#include <iostream>

#include "player.hpp"

#include "component/collision.hpp"
#include "component/input.hpp"
#include "component/physics.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"
#include "system/collision.hpp"
#include "system/render.hpp"

Player::Player(std::string name) : Entity(name) {
  const char *path = "platform/desktop/resources/flappy/flappy_red.png";
  Texture2D playerSprite = ResourceManager::getInstance().getTexture(path);

  addComponent<InputComponent, ICParams>(ICParams{});
  addComponent<TransformComponent, TCParams>(TCParams{100, 200, 999, 0});
  addComponent<PhysicsComponent, PCParams>(PCParams{1, 0, 0, false, true});
  addComponent<RenderComponent, RCParams>(RCParams{playerSprite, true, WHITE});
  addComponent<CollisionComponent, CCParams>(CCParams{0, 0, true});

  addSetupFunction("Reduce collision box", [&]() {
    auto *collision = getComponent<CollisionComponent>();

    collision->width = collision->width * 0.75;
    collision->height = collision->height * 0.75;
  });

  addEvent<CollisionSystem>([&](Entity *other) {
    auto physics = getComponent<PhysicsComponent>();

    if (!physics)
      return;

    if (other->name != "Player") {
      physics->movableY = false;
      std::cout << "Player collided with " << other->name << std::endl;
      removeComponent<CollisionComponent>();
      removeComponent<PhysicsComponent>();
    }
  });

  addEvent<RenderSystem>([&](Entity *other) {
    auto transform = getComponent<TransformComponent>();
    auto physics = getComponent<PhysicsComponent>();

    if (!(transform && physics))
      return;

    transform->rotation = physics->velocityY * 1;
  });
}