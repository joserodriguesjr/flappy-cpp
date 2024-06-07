#include "game/game.hpp"
#include "pipe/pipe.hpp"
#include "player/player.hpp"
#include "score/score.hpp"

GameState::GameState()
    : online(false), hosting(false), pause(true), started(false), deltaTime(0) {
}

GameState::~GameState() {}

GameState &GameState::instance() {
  static GameState INSTANCE;
  return INSTANCE;
}

void GameState::restartGame() {
  GameState::player->reset();
  // GameState::onlinePlayer->reset();

  GameState::score->setValue(0);
  GameState::pause = true;
  GameState::started = false;

  // TODO: Send pipe info to client
  pipeManager->fillPipes();
}

// int GameState::host(pthread_t *thread) {
//   GameState::online = true;
//   GameState::hosting = true;
//   start_server();
//   int result = pthread_create(thread, NULL, wait_for_client, NULL);
//   return result;
// }

// int GameState::client(pthread_t *thread) {
//   GameState::online = true;
//   start_client();
//   int result = pthread_create(thread, NULL, wait_for_server, NULL);
//   return result;
// }

void GameState::renderPauseScreen() {
  const char *text;
  if (GameState::online && !GameState::hosting)
    text = "Wait for host to start";
  else
    text = "Press space to start";
  // Draw centered text
  int fontSize = 50;

  // Calculate text width and height
  float textWidth = renderer.measureText(text, fontSize);
  float textHeight = fontSize;

  // Calculate centered position
  float x = (renderer.getScreenWidth() - textWidth) / 2;
  float y = (renderer.getScreenHeight() - textHeight) / 2;
  y -= 100;

  // Draw black rectangle behind text
  Rectangle bgRect = {x - 5, y - 5, textWidth + 10, textHeight + 10};

  renderer.drawRectangleRec(bgRect, (Color){0, 0, 0, 100});
  renderer.drawText(text, x, y, fontSize, WHITE);
}

void GameState::renderButtons() {
  // Buttons
  renderer.drawRectangle(5, renderer.getScreenHeight() - 105, 245, 95,
                         (Color){0, 0, 0, 100});
  renderer.drawText("Spacebar - Jump", 10, renderer.getScreenHeight() - 100, 20,
                    WHITE);
  renderer.drawText("R - Restart game", 10, renderer.getScreenHeight() - 80, 20,
                    WHITE);
  renderer.drawText("H - Host server", 10, renderer.getScreenHeight() - 60, 20,
                    WHITE);
  renderer.drawText("C - Connect to server", 10,
                    renderer.getScreenHeight() - 40, 20, WHITE);
}