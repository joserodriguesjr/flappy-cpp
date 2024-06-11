#pragma once

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "st7789.hpp"

#include "interface/renderer.hpp"
#include <cstdlib>
#include <ctime>

#define LCD_WIDTH 240
#define LCD_HEIGHT 320

class RP2040Renderer : public Renderer {
private:
  RP2040Renderer() = default;
  ~RP2040Renderer() = default;
  RP2040Renderer(const RP2040Renderer &) = delete;
  RP2040Renderer &operator=(const RP2040Renderer &) = delete;

public:
  static RP2040Renderer &instance() {
    static RP2040Renderer instance;
    return instance;
  }

  void init(int width, int height) override {
    const struct st7789_config lcd_config = {
        .spi = PICO_DEFAULT_SPI_INSTANCE,
        .gpio_din = 3,
        .gpio_clk = 2,
        .gpio_cs = 5,
        .gpio_dc = 1,
        .gpio_rst = 0,
        .gpio_bl = 4,
    };
    st7789_init(&lcd_config, LCD_WIDTH, LCD_HEIGHT);
  }

  void clear() override { st7789_fill(WHITE); }

  void draw() override {
    // todo
  }

  void close() override { ; }

  int getScreenHeight(void) override { return LCD_HEIGHT; };
  int getScreenWidth(void) override { return LCD_WIDTH; };

  int getRandomValue(int min, int max) override {
    static bool first = true;
    // seeding for the first time only!
    if (first) {
      srand(time(NULL));
      first = false;
    }
    return min + rand() % ((max + 1) - min);
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
