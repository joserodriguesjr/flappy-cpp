// #include <pthread.h>

#include "game/game.hpp"
#include "interface/inputer.hpp"
#include "interface/renderer.hpp"
// #include "multiplayer/multiplayer.h"
#include "pipe/pipe.hpp"
#include "player/player.hpp"
#include "scenario/scenario.hpp"
#include "score/score.hpp"
// #include "sound/sound.hpp"

int main(int argc, char *argv[]) {
  Renderer &renderer = Renderer::instance();
  Inputer &inputer = Inputer::instance();

#ifdef DESKTOP
  ScenarioConfig scnCfg = {.floorPath = "resources/scenario/floor_complete.png",
                           .bushesPath = "resources/scenario/bushes.png",
                           .buildingsPath = "resources/scenario/buildings.png",
                           .cloudsPath = "resources/scenario/clouds.png"};

  const char *spritePath = "resources/flappy/flappy_mov_red_big.png";

  PipeManagerConfig pmCfg = {.bottomPipePath =
                                 "resources/obstacles/bottomPipe.png",
                             .topPipePath = "resources/obstacles/topPipe.png"};

#elif defined(ESP32)
// resources configuration
#endif

  renderer.Init(1200, 800);

  // Server server;
  Scenario scenario(scnCfg);
  Player player(spritePath, nullptr, true);
  // Player onlinePlayer(spritePath, &server.serverSocket, false);
  Score score;
  PipeManager pipeManager(pmCfg);
  // SoundManager soundManager;

  GameState &game = GameState::instance();
  // game.setServer(&server);
  game.setScenario(&scenario);
  game.setPlayer(&player);
  game.setScore(&score);
  game.setPipeManager(&pipeManager);
  // game.setSoundManager(&soundManager);

  // Subscribe(EVENT_IN_NETWORK_MESSAGE, &handle_in_network_messages);
  // Subscribe(EVENT_OUT_NETWORK_MESSAGE, &handle_out_network_messages);
  // Subscribe(EVENT_KEY_PRESSED, &handle_key_pressed);

  // pthread_t thread;

  renderer.SetFPS(60);
  // Detect window close button or ESC key
  //--------------------------------------------------------------------------------------
  while (!inputer.IsPressed(QUIT)) {

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
    if (inputer.IsPressed(RESTART) && (!game.online || game.hosting)) {
      // if (game.hosting)
      //   Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_RESTART);
      game.restartGame();
    }
    //----------------------------------------------------------------------------------

    // Wait for player to start the game (If online, only host can start)
    //----------------------------------------------------------------------------------
    if (inputer.IsPressed(JUMP) && !game.started &&
        (!game.online || game.hosting)) {
      // if (game.hosting)
      // Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_START);
      game.pause = !game.pause;
      game.started = true;
    }
    //----------------------------------------------------------------------------------

    // Movement logic
    //----------------------------------------------------------------------------------
    if (!game.pause) {
      // soundManager.play();

      if (player.alive) {
        game.deltaTime = renderer.GetDeltaTime();
        player.updateSprite();
        player.movement();
        pipeManager.movement();
        scenario.movement();
      }

      // if (game.online) {
      //   onlinePlayer.updateSprite();
      //   onlinePlayer.movement();
      // }
    }
    //----------------------------------------------------------------------------------

    // Draw textures
    //----------------------------------------------------------------------------------
    renderer.Clear();

    scenario.render();
    pipeManager.render();
    scenario.renderFloor();
    player.render();
    // if (game.online)
    //   onlinePlayer.render();
    score.render();
    game.renderButtons();
    if (game.pause)
      game.renderPauseScreen();

    renderer.Draw();
    //----------------------------------------------------------------------------------
  }
  // close_server();
  renderer.Close();

  return 0;
}