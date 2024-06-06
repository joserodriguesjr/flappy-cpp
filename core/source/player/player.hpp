#pragma once

#include "raylib.h"

const unsigned int NUMBER_SPRITES = 3;
const unsigned int FRAMES_SPEED = 6;
const unsigned int PLAYER_JUMPSPEED = 500;

class Player {
private:
public:
  Texture2D *textures;
  Texture2D current;
  Vector2 position;
  Vector2 velocity;
  float jumpSpeed;
  int spinDegree;
  float tiltAngle;
  Color color;
  bool alive;
  int *sockfd;
  bool local;

  Player(int *sockfd, bool local);
  ~Player();

  void updateSprite();
  void movement();
  void render();

  static void player_jump(void *p);
  static void player_dead(Player *p);
};