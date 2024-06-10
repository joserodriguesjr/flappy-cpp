#include "game/game.hpp"
#include "interface/inputer.hpp"
#include "interface/renderer.hpp"
#include "pipe/pipe.hpp"
#include "player/player.hpp"
#include "scenario/scenario.hpp"
#include "score/score.hpp"

int main(void) {
#ifdef DESKTOP
  ScenarioConfig scnCfg(
      "platform/desktop/resources/scenario/floor_complete.png",
      "platform/desktop/resources/scenario/bushes.png",
      "platform/desktop/resources/scenario/buildings.png",
      "platform/desktop/resources/scenario/clouds.png");

  const char *spritePath =
      "platform/desktop/resources/flappy/flappy_mov_red_big.png";

  PipeManagerConfig pmCfg("platform/desktop/resources/obstacles/bottomPipe.png",
                          "platform/desktop/resources/obstacles/topPipe.png");

#elif defined(PICO)
  // ScenarioConfig scnCfg();

  // const char *spritePath = "";

  // PipeManagerConfig pmCfg();

  // dummy files just to test
  ScenarioConfig scnCfg(".png", ".png", ".png", ".png");

  const char *spritePath = ".png";

  PipeManagerConfig pmCfg(".png", ".png");
#endif

  Renderer &renderer = Renderer::instance();
  Inputer &inputer = Inputer::instance();

  inputer.init();
  renderer.init(1200, 800);

  Scenario scenario(scnCfg);
  Player player(spritePath, nullptr, true);
  Score score;
  PipeManager pipeManager(pmCfg);

  GameState &game = GameState::instance();
  game.setScenario(&scenario);
  game.setPlayer(&player);
  game.setScore(&score);
  game.setPipeManager(&pipeManager);

  renderer.setFPS(60);
  // Detect window close button or ESC key
  //--------------------------------------------------------------------------------------
  while (!inputer.isPressed(QUIT)) {

    // Restart when 'R' is pressed
    //----------------------------------------------------------------------------------
    if (inputer.isPressed(RESTART))
      game.restartGame();
    //----------------------------------------------------------------------------------

    // Wait for player to start the game
    //----------------------------------------------------------------------------------
    if (inputer.isPressed(JUMP) && !game.started) {
      game.pause = !game.pause;
      game.started = true;
    }
    //----------------------------------------------------------------------------------

    // Movement logic
    //----------------------------------------------------------------------------------
    if (!game.pause) {
      if (player.alive) {
        game.deltaTime = renderer.getDeltaTime();
        player.updateSprite();
        player.movement();
        pipeManager.movement();
        scenario.movement();
      }
    }
    //----------------------------------------------------------------------------------

    // Draw textures
    //----------------------------------------------------------------------------------
    renderer.clear();

    scenario.render();
    pipeManager.render();
    scenario.renderFloor();
    player.render();
    score.render();
    game.renderButtons();
    if (game.pause)
      game.renderPauseScreen();

    renderer.draw();
    //----------------------------------------------------------------------------------
  }
  renderer.close();
}