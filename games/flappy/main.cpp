#include "core/engine.hpp"
#include "system/animation.hpp"
#include "system/collision.hpp"
#include "system/input.hpp"
#include "system/physics.hpp"
#include "system/render.hpp"

#include "ground.hpp"
#include "pipe.hpp"
#include "player.hpp"
#include "roof.hpp"

int main() {
  GameEngine engine;

  engine.addSystem<PhysicsSystem, PSParams>(PSParams{9.8, 10});
  engine.addSystem<RenderSystem, RSParams>(RSParams{true, true, 1200, 800});
  engine.addSystem<InputSystem, ISParams>({});
  engine.addSystem<CollisionSystem, CSParams>({});
  engine.addSystem<AnimationSystem, ASParams>({});

  engine.addEntity<Player>("Player");
  engine.addEntity<Ground>("Ground");
  engine.addEntity<Pipe>("Pipe");
  engine.addEntity<Roof>("Roof");

  engine.run();
}
