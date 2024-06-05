#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define PLAYER_START_POSITION_X 300.0f
#define PLAYER_START_POSITION_Y 400.0f

#define FLOOR_HEIGHT 180

#define MAX_PIPE_COUNT 7
#define LAST_PIPE MAX_PIPE_COUNT - 1

#define SCORE_VALUE 50

// TODO: This need to come from external file (dificuldade.txt)
//  #define OBSTACLE_VELOCITY 4;
//  #define OBSTACLE_VELOCITY 15;
#define OBSTACLE_VELOCITYY 250.0f;

// Old Values before Delta time
// #define GRAVITY 0.5f
// #define PLAYER_JUMPSPEED 10.0f
// #define FLOOR_SCROLLSPEED 5.0f
// #define BUSHES_SCROLLSPEED 2.0f
// #define BUILDINGS_SCROLLSPEED 1.0f
// #define CLOUDS_SCROLLSPEED 0.5f

// After Delta time
#define GRAVITY 1400.0f
#define PLAYER_JUMPSPEED 500.0f

#define FLOOR_SCROLLSPEED 300.0f
#define BUSHES_SCROLLSPEED 120.0f
#define BUILDINGS_SCROLLSPEED 60.0f
#define CLOUDS_SCROLLSPEED 30.0f

#endif /* CONSTANTS_H */
