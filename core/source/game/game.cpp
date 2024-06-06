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

#define PLAYER_START_POSITION_Y 400.0f

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

void GameState::render_pause_screen() {
  const char *text;
  if (GameState::online && !GameState::hosting)
    text = "Wait for host to start";
  else
    text = "Press space to start";
  // Draw centered text
  int fontSize = 50;

  // Calculate text width and height
  float textWidth = MeasureText(text, fontSize);
  float textHeight = fontSize;

  // Calculate centered position
  float x = (GetScreenWidth() - textWidth) / 2;
  float y = (GetScreenHeight() - textHeight) / 2;
  y -= 100;

  // Draw black rectangle behind text
  Rectangle bgRect = {x - 5, y - 5, textWidth + 10, textHeight + 10};

  DrawRectangleRec(bgRect, (Color){0, 0, 0, 100});
  DrawText(text, x, y, fontSize, WHITE);
}

void GameState::render_buttons() {
  // Buttons
  DrawRectangle(5, GetScreenHeight() - 105, 245, 95, (Color){0, 0, 0, 100});
  DrawText("Spacebar - Jump", 10, GetScreenHeight() - 100, 20, WHITE);
  DrawText("R - Restart game", 10, GetScreenHeight() - 80, 20, WHITE);
  DrawText("H - Host server", 10, GetScreenHeight() - 60, 20, WHITE);
  DrawText("C - Connect to server", 10, GetScreenHeight() - 40, 20, WHITE);
}