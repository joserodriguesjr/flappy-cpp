#pragma once

#include "interface/inputer.hpp"

class ESP32Inputer : public Inputer {
private:
  ESP32Inputer() = default;
  ~ESP32Inputer() = default;
  ESP32Inputer(const ESP32Inputer &) = delete;
  ESP32Inputer &operator=(const ESP32Inputer &) = delete;

public:
  static ESP32Inputer &instance() {
    static ESP32Inputer instance;
    return instance;
  }

  bool IsPressed(int key) override {
    if (key == RESTART) {
      // todo
    } else if (key == JUMP) {
      // todo
    } else if (key == QUIT) {
      // todo
    } else
      return false;
  }
};
