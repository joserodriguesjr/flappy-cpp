#pragma once

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

  void Init(int width, int height) override {
    InitWindow(width, height, "Game");
    InitAudioDevice();
  }

  void Clear() override {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  }

  void Draw() override {
    // Your drawing logic
    EndDrawing();
  }

  void Close() override {
    CloseAudioDevice();
    CloseWindow();
  }

  Texture2D LoadTexture2D(const char *texturePath) override {
    return LoadTexture(texturePath);
  };
  void UnloadTexture2D(Texture2D texture) override { UnloadTexture(texture); };

  Image LoadNewImage(const char *fileName) override {
    return LoadImage(fileName);
  };
  void UnloadImage_(Image image) override { UnloadImage(image); };

  Image CropImage(Image image, Rectangle rec) override {
    return ImageFromImage(image, rec);
  };
  Texture2D LoadTexture2DFromImage(Image image) override {
    return LoadTextureFromImage(image);
  };

  void SetFPS(int fps) override { SetTargetFPS(fps); }

  float GetDeltaTime() override { return GetFrameTime(); }
};
