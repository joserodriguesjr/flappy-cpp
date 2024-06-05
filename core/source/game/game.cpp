#include "game/game.hpp"

const unsigned int GRAVITY = 1400;

GameState::GameState(Server *svr, Scenario *scn, Player *p, Score *s)
    : online(false), hosting(false), pause(true), started(false),
      gravity(GRAVITY), deltaTime(0), server(svr), scenario(scn), player(p),
      score(s) {}

GameState::~GameState() {}

// #define PLAYER_START_POSITION_X 300.0f
// #define PLAYER_START_POSITION_Y 400.0f

// void GameState::restartGame(PipeManager *pipeManager, Player *onlinePlayer) {
//   // TODO: Criar metodos para reiniciar os objetos do player e cano
//   GameState::player->alive = true;
//   GameState::player->position.y = PLAYER_START_POSITION_Y;
//   GameState::player->velocity = (Vector2){0.0f, 0.0f};
//   GameState::player->spinDegree = 0;
//   GameState::player->tiltAngle = 0;
//   GameState::player->color.a = 255;

//   onlinePlayer->position.y = PLAYER_START_POSITION_Y;
//   onlinePlayer->velocity = (Vector2){0.0f, 0.0f};
//   onlinePlayer->spinDegree = 0;
//   onlinePlayer->tiltAngle = 0;

//   GameState::score->value = 0;
//   GameState::pause = true;
//   GameState::started = false;

//   // TODO: Send pipe info to client
//   for (int i = 0; i < MAX_PIPE_COUNT; i++) {
//     Pipe pipe;
//     pipeManager->_random_pipe(pipeManager, &pipe, i);
//     pipeManager->pipes[i] = pipe;
//   }
// }

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

void GameState::update(float deltaTime) { GameState::deltaTime = deltaTime; }

void GameState::sounds(Sound deathSound, Sound backgroundMusic) {
  // Background Music
  {
    if (!IsSoundPlaying(backgroundMusic)) {
      SetSoundVolume(backgroundMusic, 0.05);
      PlaySound(backgroundMusic);
    }
  }

  // Death sound
  bool visible = GameState::player->color.a != 0;
  bool dead = !GameState::player->alive;
  if (dead && visible) {
    if (!IsSoundPlaying(deathSound)) {
      SetSoundVolume(deathSound, 0.5);
      PlaySound(deathSound);
    }
  }
}

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