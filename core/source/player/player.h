#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <stdbool.h>

#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

typedef struct Player {
  Texture2D *textures;
  Texture2D current;
  Vector2 position;
  Vector2 velocity;
  float jumpSpeed;
  bool alive;
  int spinDegree;
  float tiltAngle;
  Color color;
  int *sockfd;
  bool local;
} Player;

void init_player(Player *p, Image playerImage, int *sockfd, bool local);

void deload_player(Player *p);

void player_online(void *g, Player *p);

void player_update_frame(Player *p, int *framesCounter, int *currentFrame);

void player_movement(void *g, Player *p);

void player_animation(Player *p, float deltaTime);

void player_update_position(Player *p, float deltaTime);

void player_jump(void *p);

void player_gravity(Player *p, float gravity, float deltaTime);

bool player_hits_floor(Player *p);

void player_dead(Player *p);

#endif /* PLAYER_H */