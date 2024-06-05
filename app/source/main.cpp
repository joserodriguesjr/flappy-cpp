#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"

#include "constants.h"
#include "game/game.h"
#include "globals.h"
#include "network/network.h"
#include "pipe/pipe.h"
#include "player/player.h"
#include "pubsub/pubsub.h"
#include "scenario/background.hpp"
#include "scenario/floor.hpp"
#include "score/score.h"

// TODO: add more players
// #define MAX_PLAYERS 4

// todo Singleton
void *global_gameState;
void *global_pipeManager;
void *global_player;
void *global_onlinePlayer;
void *global_server;

void restart_game(GameState *gameState, PipeManager *pipeManager,
                  Player *onlinePlayer) {
  // TODO: Criar metodos para reiniciar os objetos do player e cano
  gameState->player->alive = true;
  gameState->player->position.y = PLAYER_START_POSITION_Y;
  gameState->player->velocity = (Vector2){0.0f, 0.0f};
  gameState->player->spinDegree = 0;
  gameState->player->tiltAngle = 0;
  gameState->player->color.a = 255;

  onlinePlayer->position.y = PLAYER_START_POSITION_Y;
  onlinePlayer->velocity = (Vector2){0.0f, 0.0f};
  onlinePlayer->spinDegree = 0;
  onlinePlayer->tiltAngle = 0;

  gameState->score->value = 0;
  gameState->pause = true;
  gameState->started = false;

  // TODO: Send pipe info to client
  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    Pipe pipe;
    _random_pipe(pipeManager, &pipe, i);
    pipeManager->pipes[i] = pipe;
  }
}

// TODO: add DEBUG INFO through args ---> int main( int argc, char **argv )
// TODO : use const
int main(int argc, char *argv[]) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FlappyInf");
  InitAudioDevice();

  Server server;

  Texture2D bushesTexture = LoadTexture("resources/scenario/bushes.png");
  Texture2D buildingsTexture = LoadTexture("resources/scenario/buildings.png");
  Texture2D cloudsTexture = LoadTexture("resources/scenario/clouds.png");
  Background background;
  init_background(&background, bushesTexture, buildingsTexture, cloudsTexture);

  Texture2D floorTexture =
      LoadTexture("resources/obstacles/floor_complete.png");
  Floor floor;
  init_floor(&floor, floorTexture);

  // TODO: receive external configuration
  Texture2D bottomPipeTexture =
      LoadTexture("resources/obstacles/bottomPipe.png");
  Texture2D topPipeTexture = LoadTexture("resources/obstacles/topPipe.png");
  PipeManager pipeManager;
  init_pipe_manager(&pipeManager, bottomPipeTexture, topPipeTexture);

  Image playerImage = LoadImage("resources/flappy/flappy_mov_red_big.png");
  Player player;
  Player onlinePlayer;
  init_player(&player, playerImage, &server.serverSocket, true);
  init_player(&onlinePlayer, playerImage, &server.serverSocket, false);

  Score score;
  init_score(&score);

  // TODO: Use gameState everywhere (headers, methods)
  GameState game;
  init_game(&game, &server, &floor, &player, &background, &score);

  global_player = (void *)&player;
  global_onlinePlayer = (void *)&onlinePlayer;
  global_server = (void *)&server;
  global_pipeManager = (void *)&pipeManager;
  global_gameState = (void *)&game;

  Sound deathSound = LoadSound("resources/audio/evil_laugh_edit.mp3");
  Sound backgroundMusic = LoadSound("resources/audio/bg_blackops.mp3");

  Subscribe(EVENT_IN_NETWORK_MESSAGE, &handle_in_network_messages);
  Subscribe(EVENT_OUT_NETWORK_MESSAGE, &handle_out_network_messages);
  Subscribe(EVENT_KEY_PRESSED, &handle_key_pressed);

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
    if (IsKeyPressed(KEY_H)) {
      // Publish(EVENT_KEY_PRESSED, K_HOST);
      restart_game(&game, &pipeManager, &onlinePlayer);
      int result = game_host(&game, &thread);
      if (result != 0) {
        fprintf(stderr, "Thread creation failed: %s\n", strerror(result));
        break;
      }
    }
    //----------------------------------------------------------------------------------

    // Connect to host when 'C' is pressed
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_C)) {
      // Publish(EVENT_KEY_PRESSED, K_CONNECT);
      restart_game(&game, &pipeManager, &onlinePlayer);
      int result = game_client(&game, &thread);
      if (result != 0) {
        fprintf(stderr, "Thread creation failed: %s\n", strerror(result));
        break;
      }
    }

    // Restart when 'R' is pressed (If online, only host can restart)
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_R) && (!game.online || game.hosting)) {
      if (game.hosting)
        Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_RESTART);
      restart_game(&game, &pipeManager, &onlinePlayer);
    }
    //----------------------------------------------------------------------------------

    // Wait for player to start the game (If online, only host can start)
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_SPACE) && !game.started &&
        (!game.online || game.hosting)) {
      if (game.hosting)
        Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_START);
      game.pause = !game.pause;
      game.started = true;
    }
    //----------------------------------------------------------------------------------

    // States
    //----------------------------------------------------------------------------------
    // TODO: Configure states (Menu, score, difficulty)
    float deltaTime = GetFrameTime();
    game_update_state(&game, deltaTime);
    //----------------------------------------------------------------------------------

    if (!game.pause) {
      // Sounds
      //----------------------------------------------------------------------------------
      // TODO: Coin, power ups
      game_sounds(&game, deathSound, backgroundMusic);
      //----------------------------------------------------------------------------------

      // Update texture frame
      //----------------------------------------------------------------------------------
      player_update_frame(&player, &framesCounter, &currentFrame);
      if (game.online) {
        int framesCounterCopy = framesCounter;
        int currentFrameCopy = currentFrame;
        player_update_frame(&onlinePlayer, &framesCounterCopy,
                            &currentFrameCopy);
      }
      //----------------------------------------------------------------------------------

      // Update positions
      //----------------------------------------------------------------------------------
      background_movement(&game, &background);
      pipe_movement(&game, &pipeManager);
      floor_movement(&game, &floor);
      player_movement(&game, &player);
      if (game.online)
        player_movement(&game, &onlinePlayer);
      // Publish(EVENT_MOVEMENT, GRAVITY, &game);
      //----------------------------------------------------------------------------------
    }

    // Draw textures
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(WHITE);

    background_animation(&background);
    pipe_animation(&pipeManager);
    floor_animation(&floor);
    player_animation(&player, deltaTime);
    if (game.online)
      player_animation(&onlinePlayer, deltaTime);
    score_animation(&score);
    game_draw_buttons();
    if (game.pause)
      game_draw_pause_screen(&game);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  //----------------------------------------------------------------------------------

  // De-Initialization
  //--------------------------------------------------------------------------------------
  close_server();

  UnloadTexture(bushesTexture);
  UnloadTexture(buildingsTexture);
  UnloadTexture(cloudsTexture);
  UnloadTexture(floorTexture);
  UnloadTexture(bottomPipeTexture);
  UnloadTexture(topPipeTexture);
  UnloadImage(playerImage);
  deload_player(&player);

  UnloadSound(backgroundMusic);
  UnloadSound(deathSound);

  CloseAudioDevice();
  CloseWindow();
  //--------------------------------------------------------------------------------------

  return 0;
}