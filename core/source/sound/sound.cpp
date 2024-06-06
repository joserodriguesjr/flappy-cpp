#include "sound/sound.hpp"
#include "game/game.hpp"
#include "player/player.hpp"

SoundManager::SoundManager()
    : backgroundMusic(LoadSound("resources/audio/bg_blackops.mp3")),
      deathSound(LoadSound("resources/audio/evil_laugh_edit.mp3")) {}

SoundManager::~SoundManager() {
  UnloadSound(backgroundMusic);
  UnloadSound(deathSound);
}

void SoundManager::playBackgroundMusic() {
  if (!IsSoundPlaying(backgroundMusic)) {
    SetSoundVolume(backgroundMusic, 0.05);
    PlaySound(backgroundMusic);
  }
}

void SoundManager::playDeathSound() {
  if (!IsSoundPlaying(deathSound)) {
    SetSoundVolume(deathSound, 0.5);
    PlaySound(deathSound);
  }
}

void SoundManager::play() {
  GameState &gameState = GameState::instance();

  playBackgroundMusic();

  bool dead = !gameState.getPlayer()->alive;
  if (dead)
    playDeathSound();
}