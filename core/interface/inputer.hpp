#pragma once

class Inputer {
public:
  static Inputer &instance();
  virtual ~Inputer(){};

  virtual void init() = 0;
  virtual bool isPressed(int action) = 0;
};

enum Actions {
  JUMP = 1,
  RESTART = 2,
  QUIT = 3,
};