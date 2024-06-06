#pragma once

#include "network/network.h"
#include "pipe/pipe.hpp"
#include "player/player.hpp"
#include "scenario/scenario.hpp"
#include "score/score.hpp"
#include "sound/sound.hpp"

// TODO: remove
// #define PLAYER_START_POSITION_X 300.0f
// #define PLAYER_START_POSITION_Y 400.0f
const unsigned int GRAVITY = 1400;
const int PLAYER_START_POSITION_X = 300;
const int PLAYER_START_POSITION_Y = 400;

class GameState {
private:
  GameState();
  Server *server;
  Scenario *scenario;
  Player *player;
  Score *score;
  PipeManager *pipeManager;
  SoundManager *soundManager;

public:
  bool online;
  bool hosting;
  bool pause;
  bool started;
  float gravity;
  float deltaTime;

  static GameState &instance();

  Server *getServer() const { return server; }
  void setServer(Server *svr) { server = svr; }

  Player *getPlayer() const { return player; }
  void setPlayer(Player *p) { player = p; }

  Scenario *getScenario() const { return scenario; }
  void setScenario(Scenario *scn) { scenario = scn; }

  Score *getScore() const { return score; }
  void setScore(Score *scr) { score = scr; }

  PipeManager *getPipeManager() const { return pipeManager; }
  void setPipeManager(PipeManager *pm) { pipeManager = pm; }

  SoundManager *getSoundManager() const { return soundManager; }
  void setSoundManager(SoundManager *sm) { soundManager = sm; }

  // void restartGame(Player *onlinePlayer);
  void restartGame();

  int host(pthread_t *thread);
  int client(pthread_t *thread);

  void update(float deltaTime);
  void sounds(Sound deathSound, Sound backgroundMusic);

  void movement();
  void render();

  void render_pause_screen();
  void render_buttons();
};
