#pragma once

#include "interface/color.hpp"
#include "interface/renderer.hpp"
#include "raylib.h"

class RaylibRenderer : public Renderer {
private:
  RaylibRenderer() = default;
  ~RaylibRenderer() = default;
  RaylibRenderer(const RaylibRenderer &) = delete;
  RaylibRenderer &operator=(const RaylibRenderer &) = delete;

public:
  static RaylibRenderer &instance() {
    static RaylibRenderer instance;
    return instance;
  }

  void init(int width, int height) override {
    InitWindow(width, height, "Game");
    InitAudioDevice();
  }

  void clear() override {
    BeginDrawing();
    ClearBackground(WHITE);
  }

  void draw() override {
    // Your drawing logic
    EndDrawing();
  }

  void close() override {
    CloseAudioDevice();
    CloseWindow();
  }

  int getScreenHeight(void) override { return GetScreenHeight(); };
  int getScreenWidth(void) override { return GetScreenWidth(); };

  int getRandomValue(int min, int max) override {
    return GetRandomValue(min, max);
  };

  Texture2D loadTexture2D(const char *texturePath) override {
    return LoadTexture(texturePath);
  };
  void unloadTexture2D(Texture2D texture) override { UnloadTexture(texture); };

  Image loadNewImage(const char *fileName) override {
    return LoadImage(fileName);
  };
  void unloadImage(Image image) override { UnloadImage(image); };

  Image cropImage(Image image, Rectangle rec) override {
    return ImageFromImage(image, rec);
  };
  Texture2D loadTexture2DFromImage(Image image) override {
    return LoadTextureFromImage(image);
  };

  void setFPS(int fps) override { SetTargetFPS(fps); }
  void drawFPS(int posX, int posY) override { DrawFPS(posX, posY); }
  float getDeltaTime() override { return GetFrameTime(); }

  virtual void drawTexture(Texture2D texture, int posX, int posY,
                           Tint tint) override {
    switch (tint.type) {
    case TintType::COLOR:
      DrawTexture(texture, posX, posY, tint.color);
      break;
    case TintType::HEX:
      break;
    }
  };

  virtual void drawTextureEx(Texture2D texture, Vector2 position,
                             float rotation, float scale, Tint tint) override {
    switch (tint.type) {
    case TintType::COLOR:
      DrawTextureEx(texture, position, rotation, scale, tint.color);
      break;
    case TintType::HEX:
      break;
    }
  };

  virtual void drawTextureRec(Texture2D texture, Rectangle source,
                              Vector2 position, Tint tint) override {
    switch (tint.type) {
    case TintType::COLOR:
      DrawTextureRec(texture, source, position, tint.color);
      break;
    case TintType::HEX:
      break;
    };
  }

  virtual void drawTexturePro(Texture2D texture, Rectangle source,
                              Rectangle dest, Vector2 origin, float rotation,
                              Tint tint) override {
    switch (tint.type) {
    case TintType::COLOR:
      DrawTexturePro(texture, source, dest, origin, rotation, tint.color);
      break;
    case TintType::HEX:
      break;
    };
  };

  virtual void drawRectangle(int posX, int posY, int width, int height,
                             Tint tint) override {
    switch (tint.type) {
    case TintType::COLOR:
      DrawRectangle(posX, posY, width, height, tint.color);
      break;
    case TintType::HEX:
      break;
    };
  };
  virtual void drawRectangleRec(Rectangle rec, Tint tint) override {
    switch (tint.type) {
    case TintType::COLOR:
      DrawRectangleRec(rec, tint.color);
      break;
    case TintType::HEX:
      break;
    };
  };

  virtual void drawText(const char *text, int posX, int posY, int fontSize,
                        Tint tint) override {
    switch (tint.type) {
    case TintType::COLOR:
      DrawText(text, posX, posY, fontSize, tint.color);
      break;
    case TintType::HEX:
      break;
    };
  };
  virtual int measureText(const char *text, int fontSize) override {
    return MeasureText(text, fontSize);
  };

  virtual bool checkCollisionRecs(Rectangle rec1, Rectangle rec2) override {
    return CheckCollisionRecs(rec1, rec2);
  };
};
