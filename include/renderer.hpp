#pragma once

class Renderer {
public:
  virtual void Init(int width, int height) = 0;
  virtual void Clear() = 0;
  virtual void Draw() = 0;
  virtual void Close() = 0;
  virtual ~Renderer() = default;
};
