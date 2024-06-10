#include "player.hpp"
#include "game/game.hpp"
#include "scenario/scenario.hpp"
#include "sprite/sprite.hpp"

Player::Player(const char *spritePath, int *sockfd, bool local)
    : velocity({0, 0}), jumpSpeed(PLAYER_JUMPSPEED), spinDegree(0),
      tiltAngle(0), sockfd(sockfd), local(local), alive(true) {

  Image spriteImage = renderer.loadNewImage(spritePath);
  Player::textures = Sprite::loadSprites(spriteImage, NUMBER_SPRITES);
  Player::current = Player::textures[0];
  renderer.unloadImage(spriteImage);

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

Player::~Player() { Sprite::unloadSprites(Player::textures, NUMBER_SPRITES); }

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

  if (inputer.isPressed(JUMP)) {
    Player::velocity.y = -Player::jumpSpeed;
  }

  Player::velocity.y += GRAVITY * gameState.deltaTime;
  Player::position.y += Player::velocity.y * gameState.deltaTime;

  bool hitFloor =
      Player::position.y >= (renderer.getScreenHeight() - FLOOR_HEIGHT);
  if (hitFloor)
    Player::alive = false;
}

void Player::render() {
  if (Player::alive) {
    // Tilt angle calculation based on velocity
    Player::tiltAngle = Player::velocity.y * 0.07f;

    // Define the source and destination rectangles for rendering
    Rectangle source = {0, 0, static_cast<float>(Player::current.width),
                        static_cast<float>(Player::current.height)};
    Rectangle dest = {Player::position.x, Player::position.y,
                      static_cast<float>(Player::current.width),
                      static_cast<float>(Player::current.height)};

    // Define the origin for rotation
    Vector2 origin = {static_cast<float>(Player::current.width / 2),
                      static_cast<float>(Player::current.height / 2)};

    // Render the texture with the calculated tilt angle
    renderer.drawTexturePro(Player::current, source, dest, origin,
                            Player::tiltAngle, Player::color);
  } else {
    GameState &gameState = GameState::instance();
    float deltaTime = gameState.deltaTime;

    if ((Player::position.y) < (renderer.getScreenHeight() - FLOOR_HEIGHT)) {
      Player::velocity.y += GRAVITY * deltaTime;
      Player::position.y += Player::velocity.y * deltaTime;
    }

    // Define the source and destination rectangles for rendering
    Rectangle source = {0, 0, static_cast<float>(Player::current.width),
                        static_cast<float>(Player::current.height)};
    Rectangle dest = {Player::position.x, Player::position.y,
                      static_cast<float>(Player::current.width),
                      static_cast<float>(Player::current.height)};

    // Define the origin for rotation (no rotation for falling)
    Vector2 origin = {static_cast<float>(Player::current.width / 2),
                      static_cast<float>(Player::current.height / 2)};

    // Render the texture without any tilt angle
    renderer.drawTexturePro(Player::current, source, dest, origin,
                            Player::tiltAngle, Player::color);
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
