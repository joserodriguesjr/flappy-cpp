#pragma once

#include "component/collision.hpp"
#include "component/render.hpp"
#include "component/transform.hpp"
#include "resource/resource_manager.hpp"
#include "system/systemInterface.hpp"

struct RSParams {
  bool debug;
  bool showFPS;
  int width;
  float height;
};

class RenderSystem : public SystemInterface {
private:
  bool debug;
  bool showFPS;
  int width;
  float height;

  void drawCollisionBox(Renderer &renderer, TransformComponent *transform,
                        float width, float height, Tint tint, bool incline) {
    if (incline) {
      // Define the source and destination rectangles for rendering
      Rectangle source = {0, 0, width, height};

      // The destination position needs to consider the origin point correctly
      Rectangle dest = {transform->x + width / 2.0f,
                        transform->y + height / 2.0f, width, height};

      // Define the origin for rotation
      Vector2 origin = {width / 2, height / 2};

      // Draw the rotated rectangle (collision box)
      renderer.drawRectanglePro(dest, origin, transform->rotation, tint);
    } else {
      // Draw the rectangle without rotation
      renderer.drawRectangle(transform->x, transform->y, width, height, tint);
    }
  }

  void drawEntity(Renderer &renderer, TransformComponent *transform,
                  float width, float height, Tint tint, bool incline,
                  Texture2D texture) {
    if (incline) {
      // Define the source and destination rectangles for rendering
      Rectangle source = {0, 0, width, height};

      Rectangle dest = {transform->x + width / 2.0f,
                        transform->y + height / 2.0f, width, height};

      // Define the origin for rotation
      Vector2 origin = {width / 2, height / 2};

      // Render the texture with the calculated rotation
      renderer.drawTexturePro(texture, source, dest, origin,
                              transform->rotation, tint);

    } else {
      // Draw the rectangle without rotation
      renderer.drawTexture(texture, transform->x, transform->y, tint);
    }
  }

public:
  RenderSystem(RSParams p)
      : debug(p.debug), showFPS(p.showFPS), width(p.width), height(p.height) {
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

      if (debug) {
        auto *collision = entity->getComponent<CollisionComponent>();

        if (collision)
          drawCollisionBox(renderer, transform, collision->width,
                           collision->height, RED, render->incline);
        else
          drawCollisionBox(renderer, transform, render->texture.width,
                           render->texture.height, BLUE, render->incline);
      }

      drawEntity(renderer, transform, render->texture.width,
                 render->texture.height, render->tint, render->incline,
                 render->texture);
    }

    if (showFPS)
      renderer.drawFPS(10, 10);

    renderer.draw();
  }
};