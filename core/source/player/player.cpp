#include "player.hpp"
#include "constants.h"
#include "network/network.h"
#include "pubsub/pubsub.h"
#include "sprite/sprite.hpp"
#include <cstdio>

const unsigned int NUMBER_SPRITES = 3;
const unsigned int FRAMES_SPEED = 6;
const unsigned int PLAYER_JUMPSPEED = 500;

typedef struct GameState {
  bool online;
  bool hosting;
  float gravity;
  float deltaTime;
  Server *server;
  Player *player;
} GameState;

Player::Player(int *sockfd, bool local)
    : sockfd(sockfd), local(local), velocity({0, 0}),
      jumpSpeed(PLAYER_JUMPSPEED), alive(true), spinDegree(0), tiltAngle(0) {

  Player::spriteImage = LoadImage("resources/flappy/flappy_mov_red_big.png");
  Player::textures = Sprite::load_textures(Player::spriteImage, NUMBER_SPRITES);
  Player::current = Player::textures[0];
  Color color = WHITE;

  if (!local) {
    Player::position =
        (Vector2){PLAYER_START_POSITION_X - 50, PLAYER_START_POSITION_Y};
    color.a /= 2;
    Player::color = color;
  } else {
    Player::position =
        (Vector2){PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y};
    Player::color = color;
  }
}

Player::~Player() {
  UnloadImage(Player::spriteImage);
  Sprite::unload_textures(Player::textures, NUMBER_SPRITES);
}

void Player::updateSprite(int *framesCounter, int *currentFrame) {
  if (!Player::alive)
    return;

  (*framesCounter)++;
  if (*framesCounter >= (60 / FRAMES_SPEED)) {
    *framesCounter = 0;
    (*currentFrame)++;
    if (*currentFrame > 2)
      *currentFrame = 0;

    Player::current = Player::textures[*currentFrame];
  }
}

void Player::movement(void *g) {
  if (!Player::alive)
    return;

  GameState *gameState = (GameState *)g;

  if (IsKeyPressed(KEY_SPACE)) {
    Player::velocity.y = -Player::jumpSpeed;
    // Publish(EVENT_KEY_PRESSED, K_SPACEBAR);
    // if (Player::local)
    // Player::player_jump(this);
  }

  // TODO: Change to pubsub if have more objects
  Player::velocity.y += gameState->gravity * gameState->deltaTime;
  Player::position.y += Player::velocity.y * gameState->deltaTime;

  bool hit_floor = Player::position.y >= (GetScreenHeight() - FLOOR_HEIGHT);
  if (hit_floor)
    player_dead(this);
  // Publish(EVENT_COLLISION, GROUND, gameState);
}

// TODO: Just fall, no spinning
void Player::animation(Player *p, float deltaTime) {
  if (Player::alive) {
    float tiltAngle = Player::velocity.y * 8 * deltaTime;
    Rectangle source = {0, 0, static_cast<float>(Player::current.width),
                        static_cast<float>(Player::current.height)};
    Rectangle dest = {Player::position.x, Player::position.y,
                      static_cast<float>(Player::current.width),
                      static_cast<float>(Player::current.height)};
    Vector2 origin = {static_cast<float>(Player::current.width / 2),
                      static_cast<float>(Player::current.height / 2)};
    DrawTexturePro(Player::current, source, dest, origin, tiltAngle,
                   Player::color);
  } else {
    // Transparency
    if (Player::color.a <= 5)
      Player::color.a = 0;
    else
      Player::color.a -= 2.5;

    // Spinning
    // TODO: Correct spinning speed
    Player::tiltAngle = (Player::velocity.y - Player::spinDegree) * 8;
    if (Player::tiltAngle <= -90 && Player::tiltAngle > -180) {
      Player::spinDegree += 2;
    } else if (Player::tiltAngle <= -180 && Player::tiltAngle > -270) {
      Player::spinDegree += 6;
    } else if (Player::tiltAngle <= -270 && Player::tiltAngle > -360) {
      Player::spinDegree += 18;
    } else if (Player::tiltAngle <= -360) {
      Player::spinDegree += 24;
    }

    Rectangle source = {0, 0, static_cast<float>(Player::current.width),
                        static_cast<float>(Player::current.height)};
    Rectangle dest = {Player::position.x,
                      Player::position.y - Player::spinDegree,
                      static_cast<float>(Player::current.width),
                      static_cast<float>(Player::current.height)};
    Vector2 origin = {static_cast<float>(Player::current.width / 2),
                      static_cast<float>(Player::current.height / 2)};
    DrawTexturePro(Player::current, source, dest, origin, Player::tiltAngle,
                   Player::color);
    Player::spinDegree++;
  }
}

void Player::player_jump(void *p) {
  Player *player = (Player *)p;
  player->velocity.y = -player->jumpSpeed;
}

void Player::player_dead(Player *p) {
  if (p->local)
    p->alive = false;
}