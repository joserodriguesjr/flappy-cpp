#pragma once

#include "interface/renderer.hpp"

const unsigned int NUMBER_SPRITES = 3;
const unsigned int FRAMES_SPEED = 6;
const unsigned int PLAYER_JUMPSPEED = 500;

class Player {
private:
  Renderer &renderer = Renderer::instance();
  Texture2D *textures;
  Vector2 velocity;
  float jumpSpeed;
  int spinDegree;
  float tiltAngle;
  int *sockfd;
  bool local;
  Color color;

public:
  Texture2D current;
  Vector2 position;
  bool alive;

  Player(const char *spritePath, int *sockfd, bool local);
  ~Player();

  void updateSprite();
  void movement();
  void render();
  void reset();

  // TODO: FIX THIS
  static void player_jump(void *p);
  static void player_dead(Player *p);
};