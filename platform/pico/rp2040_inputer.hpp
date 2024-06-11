#pragma once

#include "pico/stdio.h"
#include "pico/stdlib.h"

#include "interface/inputer.hpp"

#define LEFT_BUTTON 6
#define RIGHT_BUTTON 7

class RP2040Inputer : public Inputer {
private:
  RP2040Inputer() = default;
  ~RP2040Inputer() = default;
  RP2040Inputer(const RP2040Inputer &) = delete;
  RP2040Inputer &operator=(const RP2040Inputer &) = delete;

public:
  static RP2040Inputer &instance() {
    static RP2040Inputer instance;
    return instance;
  }

  void init() override {
    stdio_init_all();

    gpio_init(LEFT_BUTTON);
    gpio_set_dir(LEFT_BUTTON, GPIO_IN);
    gpio_pull_up(LEFT_BUTTON);

    gpio_init(RIGHT_BUTTON);
    gpio_set_dir(RIGHT_BUTTON, GPIO_IN);
    gpio_pull_up(RIGHT_BUTTON);
  }

  bool isPressed(int key) override {
    if (key == RESTART) {
      return (!gpio_get(LEFT_BUTTON));
    } else if (key == JUMP) {
      return (!gpio_get(RIGHT_BUTTON));
    } else if (key == QUIT) {
      return false;
    } else
      return false;
  }
};
