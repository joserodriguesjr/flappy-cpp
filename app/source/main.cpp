// #include <pthread.h>
#include <raylib.h>

#include "interface/inputer.hpp"
#include "interface/renderer.hpp"

#ifdef DESKTOP
#include "platform/raylib/rl_inputer.hpp"
#include "platform/raylib/rl_renderer.hpp"
#elif defined(ESP32)
#include "esp32/esp32_renderer.hpp"
// Include others files
#endif

#include "game/game.hpp"

#include "network/network.h"
#include "pipe/pipe.hpp"
#include "player/player.hpp"
#include "scenario/scenario.hpp"
#include "score/score.hpp"
// #include "sound/sound.hpp"
// #include "pubsub/pubsub.h"

int main(int argc, char *argv[]) {
  // Choosing platform specific
  //--------------------------------------------------------------------------------------
  Renderer *renderer = nullptr;
  Inputer *inputer = nullptr;

#ifdef DESKTOP
  RaylibRenderer raylibRenderer;
  RaylibInputer raylibInputer;
  renderer = &raylibRenderer;
  inputer = &raylibInputer;
#elif defined(ESP32)
  // ESP32Renderer esp32Renderer;
  // ESP32Inputer esp32Inputer;
  // renderer = &esp32Renderer;
  // inputer = &esp32Inputer;
#endif
  //--------------------------------------------------------------------------------------

  // Initialization
  //--------------------------------------------------------------------------------------
  renderer->Init(1200, 800);
  // InitAudioDevice();

  // TODO: receive external configuration
  Server server;
  Scenario scenario;
  Player player(&server.serverSocket, true);
  Score score;
  PipeManager pipeManager;
  // SoundManager soundManager;
  // Player onlinePlayer(&server.serverSocket, false);

  GameState &game = GameState::instance();
  game.setServer(&server);
  game.setScenario(&scenario);
  game.setPlayer(&player);
  game.setScore(&score);
  game.setPipeManager(&pipeManager); // TODO: refactor to objectManager
  // game.setSoundManager(&soundManager);

  // Subscribe(EVENT_IN_NETWORK_MESSAGE, &handle_in_network_messages);
  // Subscribe(EVENT_OUT_NETWORK_MESSAGE, &handle_out_network_messages);
  // Subscribe(EVENT_KEY_PRESSED, &handle_key_pressed);

  pthread_t thread;
  //--------------------------------------------------------------------------------------

  // Main game loop
  SetTargetFPS(120);
  //--------------------------------------------------------------------------------------
  // Detect window close button or ESC key
  while (!inputer->IsPressed(QUIT)) {
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
    if (inputer->IsPressed(RESTART) && (!game.online || game.hosting)) {
      // if (game.hosting)
      //   Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_RESTART);
      game.restartGame();
    }
    //----------------------------------------------------------------------------------

    // Wait for player to start the game (If online, only host can start)
    //----------------------------------------------------------------------------------
    if (inputer->IsPressed(JUMP) && !game.started &&
        (!game.online || game.hosting)) {
      // if (game.hosting)
      // Publish(EVENT_OUT_NETWORK_MESSAGE, NM_GAME_START);
      game.pause = !game.pause;
      game.started = true;
    }
    //----------------------------------------------------------------------------------

    // States
    //----------------------------------------------------------------------------------
    game.deltaTime = GetFrameTime();
    //----------------------------------------------------------------------------------

    if (!game.pause) {
      // Sounds
      //----------------------------------------------------------------------------------
      // game.getSoundManager()->play();
      //----------------------------------------------------------------------------------

      // Update texture frame
      //----------------------------------------------------------------------------------
      player.updateSprite();
      // if (game.online)
      // onlinePlayer.updateSprite();
      //----------------------------------------------------------------------------------

      // Update positions
      //----------------------------------------------------------------------------------
      if (player.alive) {
        game.getScenario()->movement();
        game.getPipeManager()->movement();
        game.getPlayer()->movement();
      }
      // if (game.online)
      //   onlinePlayer.movement();
      // Publish(EVENT_MOVEMENT, GRAVITY, &game);
      //----------------------------------------------------------------------------------
    }

    // Draw textures
    //----------------------------------------------------------------------------------
    renderer->Clear();

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

    renderer->Draw();
    //----------------------------------------------------------------------------------
  }
  //----------------------------------------------------------------------------------

  // De-Initialization
  //--------------------------------------------------------------------------------------
  // close_server();

  // todo: delete in NEW

  // CloseAudioDevice();
  renderer->Close();

  //--------------------------------------------------------------------------------------

  return 0;
}