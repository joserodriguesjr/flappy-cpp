#include "player.h"
#include "constants.h"
#include "network/network.h"
#include "pubsub/pubsub.h"
#include "sprite/sprite.h"

#define NUMBER_SPRITES 3
#define FRAMES_SPEED 6
typedef struct GameState {
  bool online;
  bool hosting;
  float gravity;
  float deltaTime;
  Server *server;
  Player *player;
} GameState;

void init_player(Player *p, Image spriteImage, int *sockfd, bool local) {
  Texture2D *textures = load_textures(spriteImage, NUMBER_SPRITES);
  Color color = WHITE;
  p->textures = textures;
  p->current = textures[0];
  p->velocity = (Vector2){0.0f, 0.0f};
  p->jumpSpeed = PLAYER_JUMPSPEED;
  p->alive = true;
  p->spinDegree = 0;
  p->tiltAngle = 0;
  p->sockfd = sockfd;
  p->local = local;
  if (!local) {
    p->position =
        (Vector2){PLAYER_START_POSITION_X - 50, PLAYER_START_POSITION_Y};
    color.a /= 2;
    p->color = color;
  } else {
    p->position = (Vector2){PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y};
    p->color = color;
  }
}

void deload_player(Player *p) { unload_textures(p->textures, NUMBER_SPRITES); }

void player_update_frame(Player *p, int *framesCounter, int *currentFrame) {
  if (p->alive) {
    (*framesCounter)++;
    if (*framesCounter >= (60 / FRAMES_SPEED)) {
      *framesCounter = 0;
      (*currentFrame)++;
      if (*currentFrame > 2)
        *currentFrame = 0;

      p->current = p->textures[*currentFrame];
    }
  }
}

void player_movement(void *g, Player *p) {
  GameState *gameState = (GameState *)g;

  if (p->alive) {
    if (IsKeyPressed(KEY_SPACE))
      Publish(EVENT_KEY_PRESSED, K_SPACEBAR);

    // TODO: Change to pubsub if have more objects
    player_gravity(p, gameState->gravity, gameState->deltaTime);
    player_update_position(p, gameState->deltaTime);

    if (player_hits_floor(p))
      player_dead(p);
    // Publish(EVENT_COLLISION, GROUND, gameState);
  }
}

void player_animation(Player *p, float deltaTime) {
  if (p->alive) {
    float tiltAngle = p->velocity.y * 8 * deltaTime;
    Rectangle source = {0, 0, static_cast<float>(p->current.width),
                        static_cast<float>(p->current.height)};
    Rectangle dest = {p->position.x, p->position.y,
                      static_cast<float>(p->current.width),
                      static_cast<float>(p->current.height)};
    Vector2 origin = {static_cast<float>(p->current.width / 2),
                      static_cast<float>(p->current.height / 2)};
    DrawTexturePro(p->current, source, dest, origin, tiltAngle, p->color);
  } else {
    // Transparency
    if (p->color.a <= 5)
      p->color.a = 0;
    else
      p->color.a -= 2.5;

    // Spinning
    // TODO: Correct spinning speed
    p->tiltAngle = (p->velocity.y - p->spinDegree) * 8;
    if (p->tiltAngle <= -90 && p->tiltAngle > -180) {
      p->spinDegree += 2;
    } else if (p->tiltAngle <= -180 && p->tiltAngle > -270) {
      p->spinDegree += 6;
    } else if (p->tiltAngle <= -270 && p->tiltAngle > -360) {
      p->spinDegree += 18;
    } else if (p->tiltAngle <= -360) {
      p->spinDegree += 24;
    }

    Rectangle source = {0, 0, static_cast<float>(p->current.width),
                        static_cast<float>(p->current.height)};
    Rectangle dest = {p->position.x, p->position.y - p->spinDegree,
                      static_cast<float>(p->current.width),
                      static_cast<float>(p->current.height)};
    Vector2 origin = {static_cast<float>(p->current.width / 2),
                      static_cast<float>(p->current.height / 2)};
    DrawTexturePro(p->current, source, dest, origin, p->tiltAngle, p->color);
    p->spinDegree++;
  }
}

void player_update_position(Player *p, float deltaTime) {
  p->position.y += p->velocity.y * deltaTime;
}

void player_jump(void *p) {
  Player *player = (Player *)p;
  player->velocity.y = -player->jumpSpeed;
}

void player_gravity(Player *p, float gravity, float deltaTime) {
  p->velocity.y += gravity * deltaTime;
}

bool player_hits_floor(Player *p) {
  return (p->position.y >= (GetScreenHeight() - FLOOR_HEIGHT));
}

void player_dead(Player *p) {
  if (p->local)
    p->alive = false;
}