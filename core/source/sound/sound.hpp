#pragma once

#include "raylib.h"

// TODO: Coin, power ups
class SoundManager {
private:
  Sound backgroundMusic;
  Sound deathSound;
  void playBackgroundMusic();
  void playDeathSound();

public:
  SoundManager();
  ~SoundManager();

  void play();
};
