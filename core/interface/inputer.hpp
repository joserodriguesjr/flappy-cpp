#pragma once

class Inputer {
public:
  static Inputer &instance();

  virtual bool IsPressed(int action) = 0;
  virtual ~Inputer() = default;
};

enum Actions {
  JUMP = 1,
  RESTART = 2,
  QUIT = 3,
};