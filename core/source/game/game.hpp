#pragma once

#include <pthread.h>

class Player;
class Server;
class Scenario;
class Score;
class PipeManager;
class SoundManager;

const unsigned int GRAVITY = 1400;
const int PLAYER_START_POSITION_X = 300;
const int PLAYER_START_POSITION_Y = 400;

class GameState {
private:
  GameState();
  ~GameState();

  // Prevent copy construction and assignment
  GameState(const GameState &) = delete;
  GameState &operator=(const GameState &) = delete;

  Server *server = nullptr;
  Scenario *scenario = nullptr;
  Player *player = nullptr;
  Score *score = nullptr;
  PipeManager *pipeManager = nullptr;
  SoundManager *soundManager = nullptr;

public:
  bool online;
  bool hosting;
  bool pause;
  bool started;
  float deltaTime;

  static GameState &instance();

  Server *getServer() const { return server; }
  Scenario *getScenario() const { return scenario; }
  Player *getPlayer() const { return player; }
  Score *getScore() const { return score; }
  PipeManager *getPipeManager() const { return pipeManager; }
  SoundManager *getSoundManager() const { return soundManager; }

  void setServer(Server *svr) { server = svr; }
  void setScenario(Scenario *scn) { scenario = scn; }
  void setPlayer(Player *p) { player = p; }
  void setScore(Score *scr) { score = scr; }
  void setPipeManager(PipeManager *pm) { pipeManager = pm; }
  void setSoundManager(SoundManager *sm) { soundManager = sm; }

  // void restartGame(Player *onlinePlayer);
  void restartGame();

  int host(pthread_t *thread);
  int client(pthread_t *thread);

  void movement();
  void render();

  void render_pause_screen();
  void render_buttons();
};
