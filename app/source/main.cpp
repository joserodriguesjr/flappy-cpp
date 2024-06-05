#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"

#include "constants.h"
#include "game/game.hpp"
#include "globals.h"
// #include "network/network.h"
#include "pipe/pipe.hpp"
#include "player/player.hpp"
// #include "pubsub/pubsub.h"
#include "scenario/scenario.hpp"
#include "score/score.h"

// TODO: add more players
// #define MAX_PLAYERS 4

// todo Singleton
void *global_gameState;
void *global_pipeManager;
void *global_player;
void *global_onlinePlayer;
void *global_server;

// TODO: add DEBUG INFO through args ---> int main( int argc, char **argv )
// TODO : use const
int main(int argc, char *argv[]) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FlappyInf");
  InitAudioDevice();

  Server server;
  Scenario scenario;

  // TODO: receive external configuration
  PipeManager pipeManager;

  Player player(&server.serverSocket, true);
  Player onlinePlayer(&server.serverSocket, false);

  Score score;
  init_score(&score);

  // TODO: Use gameState everywhere (headers, methods)
  GameState game(&server, &scenario, &player, &score);

  global_player = (void *)&player;
  global_onlinePlayer = (void *)&onlinePlayer;
  global_server = (void *)&server;
  global_pipeManager = (void *)&pipeManager;
  global_gameState = (void *)&game;

  // TODO: move to game ctor
  Sound deathSound = LoadSound("resources/audio/evil_laugh_edit.mp3");
  Sound backgroundMusic = LoadSound("resources/audio/bg_blackops.mp3");

  // Subscribe(EVENT_IN_NETWORK_MESSAGE, &handle_in_network_messages);
  // Subscribe(EVENT_OUT_NETWORK_MESSAGE, &handle_out_network_messages);
  // Subscribe(EVENT_KEY_PRESSED, &handle_key_pressed);

  int framesCounter = 0;
  int currentFrame = 0;
  pthread_t thread;
  //--------------------------------------------------------------------------------------

  // Main game loop
  SetTargetFPS(120);
  //--------------------------------------------------------------------------------------
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Host game when 'H' is pressed
    //----------------------------------------------------------------------------------
    // if (IsKeyPressed(KEY_H)) {
    //   // Publish(EVENT_KEY_PRESSED, K_HOST);
    //   restart_game(&game, &pipeManager, &onlinePlayer);
    //   int result = game_host(&game, &thread);
    //   if (result != 0) {
    //     fprintf(stderr, "Thread creation failed: %s\n", strerror(result));
    //     break;
    //   }
    // }
    //----------------------------------------------------------------------------------

    // Connect to host when 'C' is pressed
    //----------------------------------------------------------------------------------
    // if (IsKeyPressed(KEY_C)) {
    //   // Publish(EVENT_KEY_PRESSED, K_CONNECT);
    //   restart_game(&game, &pipeManager, &onlinePlayer);
    //   int result = game_client(&game, &thread);
    //   if (result != 0) {
    //     fprintf(stderr, "Thread creation failed: %s\n", strerror(result));
    //     break;
    //   }
    // }

    // Restart when 'R' is pressed (If online, only host can restart)
    //----------------------------------------------------------------------------------
    // if (IsKeyPressed(KEY_R) && (!game.online || game.hosting)) {
    //   if (game.hosting)
    //     Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_RESTART);
    //   restart_game(&game, &pipeManager, &onlinePlayer);
    // }
    //----------------------------------------------------------------------------------

    // Wait for player to start the game (If online, only host can start)
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_SPACE) && !game.started &&
        (!game.online || game.hosting)) {
      // if (game.hosting)
      // Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_START);
      game.pause = !game.pause;
      game.started = true;
    }
    //----------------------------------------------------------------------------------

    // States
    //----------------------------------------------------------------------------------
    // TODO: Configure states (Menu, score, difficulty)
    float deltaTime = GetFrameTime();
    game.update(deltaTime);
    //----------------------------------------------------------------------------------

    if (!game.pause) {
      // Sounds
      //----------------------------------------------------------------------------------
      // TODO: Coin, power ups
      game.sounds(deathSound, backgroundMusic);
      //----------------------------------------------------------------------------------

      // Update texture frame
      //----------------------------------------------------------------------------------
      player.updateSprite(&framesCounter, &currentFrame);
      if (game.online) {
        int framesCounterCopy = framesCounter;
        int currentFrameCopy = currentFrame;
        onlinePlayer.updateSprite(&framesCounterCopy, &currentFrameCopy);
      }
      //----------------------------------------------------------------------------------

      // Update positions
      //----------------------------------------------------------------------------------
      scenario.movement(&game);
      pipeManager.movement(&game);
      player.movement(&game);
      if (game.online)
        onlinePlayer.movement(&game);
      // Publish(EVENT_MOVEMENT, GRAVITY, &game);
      //----------------------------------------------------------------------------------
    }

    // Draw textures
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(WHITE);

    scenario.render();
    pipeManager.render();
    scenario.floor_render();
    player.animation(&player, deltaTime);
    if (game.online)
      onlinePlayer.animation(&onlinePlayer, deltaTime);
    score_animation(&score);
    game.render_buttons();
    if (game.pause)
      game.render_pause_screen();

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  //----------------------------------------------------------------------------------

  // De-Initialization
  //--------------------------------------------------------------------------------------
  // close_server();

  // todo: delete in NEW

  UnloadSound(backgroundMusic);
  UnloadSound(deathSound);

  CloseAudioDevice();
  CloseWindow();
  //--------------------------------------------------------------------------------------

  return 0;
}