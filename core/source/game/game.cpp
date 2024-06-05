#include "game.h"
#include "constants.h"

void init_game(GameState *g, Server *svr, Floor *f, Player *p, Background *b,
               Score *s) {
  g->online = false;
  g->hosting = false;
  g->pause = true;
  g->started = false;
  g->gravity = GRAVITY;
  g->deltaTime = 0.0f;
  g->server = svr;
  g->floor = f;
  g->player = p;
  g->background = b;
  g->score = s;
}

int game_host(GameState *g, pthread_t *thread) {
  g->online = true;
  g->hosting = true;
  start_server();
  int result = pthread_create(thread, NULL, wait_for_client, NULL);
  return result;
}

int game_client(GameState *g, pthread_t *thread) {
  g->online = true;
  start_client();
  int result = pthread_create(thread, NULL, wait_for_server, NULL);
  return result;
}

void game_update_state(GameState *g, float deltaTime) {
  g->deltaTime = deltaTime;
}

void game_sounds(GameState *g, Sound deathSound, Sound backgroundMusic) {
  // Background Music
  {
    if (!IsSoundPlaying(backgroundMusic)) {
      SetSoundVolume(backgroundMusic, 0.05);
      PlaySound(backgroundMusic);
    }
  }

  // Death sound
  bool visible = g->player->color.a != 0;
  bool dead = !g->player->alive;
  if (dead && visible) {
    if (!IsSoundPlaying(deathSound)) {
      SetSoundVolume(deathSound, 0.5);
      PlaySound(deathSound);
    }
  }
}

void game_draw_pause_screen(GameState *g) {
  const char *text;
  if (g->online && !g->hosting)
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

void game_draw_buttons(void) {
  // Buttons
  DrawRectangle(5, GetScreenHeight() - 105, 245, 95, (Color){0, 0, 0, 100});
  DrawText("Spacebar - Jump", 10, GetScreenHeight() - 100, 20, WHITE);
  DrawText("R - Restart game", 10, GetScreenHeight() - 80, 20, WHITE);
  DrawText("H - Host server", 10, GetScreenHeight() - 60, 20, WHITE);
  DrawText("C - Connect to server", 10, GetScreenHeight() - 40, 20, WHITE);
}