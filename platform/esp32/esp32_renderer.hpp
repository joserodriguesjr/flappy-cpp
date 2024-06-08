#pragma once

#include "interface/renderer.hpp"

class ESP32Renderer : public Renderer {
private:
  ESP32Renderer() = default;
  ~ESP32Renderer() = default;
  ESP32Renderer(const ESP32Renderer &) = delete;
  ESP32Renderer &operator=(const ESP32Renderer &) = delete;

public:
  static ESP32Renderer &instance() {
    static ESP32Renderer instance;
    return instance;
  }

  void init(int width, int height) override {
    // todo
  }

  void clear() override {
    // todo
  }

  void draw() override {
    // todo
  }

  void close() override {
    // todo
  }

  int getScreenHeight(void) override {
    // todo
  };
  int getScreenWidth(void) override {
    // todo
  };

  int getRandomValue(int min, int max) override {
    // todo
  };

  Texture2D loadTexture2D(const char *texturePath) override {
    // todo
  };
  void unloadTexture2D(Texture2D texture) override {
    // todo
  };

  Image loadNewImage(const char *fileName) override {
    // todo
  };
  void unloadImage(Image image) override {
    // todo
  };

  Image cropImage(Image image, Rectangle rec) override {
    // todo
  };
  Texture2D loadTexture2DFromImage(Image image) override {
    // todo
  };

  void setFPS(int fps) override {
    // todo
  }
  float getDeltaTime() override {
    // todo
  }

  virtual void drawTexture(Texture2D texture, int posX, int posY,
                           Color tint) override {
    // todo
  };

  virtual void drawTextureEx(Texture2D texture, Vector2 position,
                             float rotation, float scale, Color tint) override {
    // todo
  };

  virtual void drawTextureRec(Texture2D texture, Rectangle source,
                              Vector2 position, Color tint) override {
    // todo
  };

  virtual void drawTexturePro(Texture2D texture, Rectangle source,
                              Rectangle dest, Vector2 origin, float rotation,
                              Color tint) override {
    // todo
  };

  virtual void drawRectangle(int posX, int posY, int width, int height,
                             Color color) override {
    // todo
  };
  virtual void drawRectangleRec(Rectangle rec, Color color) override {
    // todo
  };

  virtual void drawText(const char *text, int posX, int posY, int fontSize,
                        Color color) override {
    // todo
  };
  virtual int measureText(const char *text, int fontSize) override {
    // todo
  };

  virtual bool checkCollisionRecs(Rectangle rec1, Rectangle rec2) override {
    // todo
  };
};
