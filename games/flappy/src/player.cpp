#include <iostream>
#include <vector>

#include "component/animation.hpp"
#include "player.hpp"
#include "sprite.hpp"

#include "component/collision.hpp"
#include "component/input.hpp"
#include "component/physics.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"

#include "system/collision.hpp"
#include "system/render.hpp"

Player::Player(std::string name) : Entity(name) {
  const char *path = "platform/desktop/resources/flappy/flappy_mov_red_big.png";
  Image playerImage = ResourceManager::getInstance().getImage(path);
  std::vector<Texture2D> textures = Sprite::loadSprites(playerImage, 3);

  addComponent<InputComponent, ICParams>(ICParams{});
  addComponent<TransformComponent, TCParams>(TCParams{100, 200, 999, 0});
  addComponent<PhysicsComponent, PCParams>(PCParams{1, 0, 0, false, true});
  addComponent<RenderComponent, RCParams>(RCParams{textures[0], true, WHITE});
  addComponent<CollisionComponent, CCParams>(CCParams{0, 0, true});
  addComponent<AnimationComponent, ACParams>(ACParams{textures, 3, 0});

  /**
   *  @brief Reduce player's hitbox.
   */
  addSetupFunction("Reduce collision box", [&]() {
    auto *collision = getComponent<CollisionComponent>();

    collision->width = collision->width * 0.75;
    collision->height = collision->height * 0.75;
  });

  /**
   *  @brief Stop player when hit something.
   */
  addDeferredEvent<CollisionSystem>([&](Entity *other) {
    auto physics = getComponent<PhysicsComponent>();

    if (!physics)
      return;

    if (other->name != "Player") {
      std::cout << "Player collided with " << other->name << std::endl;

      removeComponent<CollisionComponent>();
      removeComponent<PhysicsComponent>();
      removeComponent<AnimationComponent>();
      removeComponent<InputComponent>();
    }
  });

  /**
   *  @brief Rotate player based on Y axis velocity.
   */
  addDeferredEvent<RenderSystem>([&](Entity *_) {
    auto transform = getComponent<TransformComponent>();
    auto physics = getComponent<PhysicsComponent>();

    if (!(transform && physics))
      return;

    transform->rotation = physics->velocityY * 0.8;
  });
}