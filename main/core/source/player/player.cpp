#include "player.hpp"
#include "game/game.hpp"
#include "scenario/scenario.hpp"
#include "sprite/sprite.hpp"
// #include "network/network.h"
// #include "pubsub/pubsub.h"

Player::Player(const char *spritePath, int *sockfd, bool local)
    : velocity({0, 0}), jumpSpeed(PLAYER_JUMPSPEED), spinDegree(0),
      tiltAngle(0), sockfd(sockfd), local(local), alive(true) {

  Image spriteImage = renderer.LoadNewImage(spritePath);
  Player::textures = Sprite::loadTextures(spriteImage, NUMBER_SPRITES);
  Player::current = Player::textures[0];
  UnloadImage(spriteImage);

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

Player::~Player() { Sprite::unloadTextures(Player::textures, NUMBER_SPRITES); }

void Player::updateSprite() {
  static int framesCounter, currentFrame;

  framesCounter++;
  if (framesCounter >= (60 / FRAMES_SPEED)) {
    framesCounter = 0;
    (currentFrame)++;
    if (currentFrame > 2)
      currentFrame = 0;

    Player::current = Player::textures[currentFrame];
  }
}

void Player::movement() {
  GameState &gameState = GameState::instance();

  if (IsKeyPressed(KEY_SPACE)) {
    Player::velocity.y = -Player::jumpSpeed;
    // Publish(EVENT_KEY_PRESSED, K_SPACEBAR);
    // if (Player::local)
    // Player::player_jump(this);
  }

  Player::velocity.y += GRAVITY * gameState.deltaTime;
  Player::position.y += Player::velocity.y * gameState.deltaTime;

  bool hit_floor = Player::position.y >= (GetScreenHeight() - FLOOR_HEIGHT);
  if (hit_floor)
    player_dead(this);
  // Publish(EVENT_COLLISION, GROUND, gameState);
}

// TODO: Just fall, no spinning
void Player::render() {
  if (Player::alive) {
    float tiltAngle = Player::velocity.y * 0.07;
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

void Player::reset() {
  Player::alive = true;
  Player::position.y = PLAYER_START_POSITION_Y;
  Player::velocity = (Vector2){0.0f, 0.0f};
  Player::spinDegree = 0;
  Player::tiltAngle = 0;
  Player::color.a = 255;
}

void Player::player_jump(void *p) {
  Player *player = (Player *)p;
  player->velocity.y = -player->jumpSpeed;
}

void Player::player_dead(Player *p) {
  if (p->local)
    p->alive = false;
}