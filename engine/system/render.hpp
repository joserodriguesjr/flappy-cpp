#pragma once

#include "component/render.hpp"
#include "component/transform.hpp"
#include "system.hpp"
#include <vector>

struct RSParams {
  bool debug;
  int width;
  float height;
};

class RenderSystem : public System {
private:
  bool debug;
  int width;
  float height;

public:
  RenderSystem(RSParams p) : debug(p.debug), width(p.width), height(p.height) {
    Renderer::instance().init(width, height);
  }

  ~RenderSystem() { Renderer::instance().close(); }

  void update(std::vector<std::unique_ptr<Entity>> &entities) override {
    Renderer &renderer = Renderer::instance();
    renderer.clear();

    for (auto &entityPtr : entities) {
      Entity *entity = entityPtr.get();
      auto *render = entity->getComponent<RenderComponent>();
      auto *transform = entity->getComponent<TransformComponent>();

      if (!(render && transform))
        continue;

      entity->runEvent<RenderSystem>(entity);

      if (debug)
        renderer.drawRectangle(transform->x, transform->y,
                               render->texture.width, render->texture.height,
                               RED);

      if (render->incline) {
        // Define the source and destination rectangles for rendering
        Rectangle source = {0, 0, static_cast<float>(render->texture.width),
                            static_cast<float>(render->texture.height)};

        Rectangle dest = {transform->x, transform->y,
                          static_cast<float>(render->texture.width),
                          static_cast<float>(render->texture.height)};

        // Define the origin for rotation
        Vector2 origin = {static_cast<float>(render->texture.width / 2),
                          static_cast<float>(render->texture.height / 2)};

        // Render the texture with the calculated tilt angle
        renderer.drawTexturePro(render->texture, source, dest, origin,
                                transform->rotation, render->tint);

      } else {
        renderer.drawTexture(render->texture, transform->x, transform->y,
                             render->tint);
      }
    }

    if (debug)
      renderer.drawFPS(10, 10);

    renderer.draw();
  }
};