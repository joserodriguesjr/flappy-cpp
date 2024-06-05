#pragma once

#include "raylib.h"
#include <stdbool.h>

class Player {
private:
public:
  Image spriteImage;
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

  void updateSprite(int *framesCounter, int *currentFrame);
  void movement(void *g);
  void animation(Player *p, float deltaTime);

  static void player_jump(void *p);
  static void player_dead(Player *p);
};