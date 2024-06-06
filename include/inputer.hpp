#pragma once

class Inputer {
public:
  virtual bool IsPressed(int action) = 0;
  virtual ~Inputer() = default;
};

enum Actions {
  JUMP = 1,
  RESTART = 2,
  QUIT = 3,
};