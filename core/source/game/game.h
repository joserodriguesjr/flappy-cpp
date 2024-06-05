#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "network/network.h"
#include "player/player.h"
#include "scenario/background.hpp"
#include "scenario/floor.hpp"
#include "score/score.h"

typedef struct GameState {
  bool online;
  bool hosting;
  bool pause;
  bool started;
  float gravity;
  float deltaTime;
  Server *server;
  Floor *floor;
  Player *player;
  Background *background;
  Score *score;
} GameState;

void init_game(GameState *g, Server *svr, Floor *f, Player *p, Background *b,
               Score *s);

int game_host(GameState *g, pthread_t *thread);
int game_client(GameState *g, pthread_t *thread);

void game_update_state(GameState *g, float deltaTime);
void game_sounds(GameState *g, Sound deathSound, Sound backgroundMusic);

void game_draw_pause_screen(GameState *g);
void game_draw_buttons(void);

#endif /* GAMESTATE_H */