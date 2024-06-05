#pragma once

#include "network/network.h"
// #include "pipe/pipe.hpp"
#include "player/player.hpp"
#include "scenario/scenario.hpp"
#include "score/score.h"

class GameState {
private:
public:
  bool online;
  bool hosting;
  bool pause;
  bool started;
  float gravity;
  float deltaTime;
  Server *server;
  Scenario *scenario;
  Player *player;
  Score *score;

  GameState(Server *svr, Scenario *scn, Player *p, Score *s);
  ~GameState();

  // void restartGame(PipeManager *pipeManager, Player *onlinePlayer);

  int host(pthread_t *thread);
  int client(pthread_t *thread);

  void update(float deltaTime);
  void sounds(Sound deathSound, Sound backgroundMusic);

  void render_pause_screen();
  void render_buttons();
};
