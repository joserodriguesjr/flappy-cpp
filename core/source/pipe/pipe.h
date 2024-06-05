#ifndef PIPES_H
#define PIPES_H

#include "constants.h"
#include "game/game.h"
#include "raylib.h"

typedef struct Pipe {
  float topPipeStart;
  float bottomPipeStart;
  float x;
  bool jumped;
} Pipe;

typedef struct PipeManager {
  Pipe pipes[MAX_PIPE_COUNT];
  Texture2D bottomPipeTexture;
  Texture2D topPipeTexture;
  int offset;
  int gap;
  int incGap;
  int difMaxHeight;
  int incDifMaxHeight;
  int obstacleVelocity;
  int incObstacleVelocity;
} PipeManager;

// TODO: Implementar parametros dentro do pipeManager
// ★ gap: indica o espaço livre inicial nos obstáculos para o jogador passar (em
// pixels) ★ inc_gap: indica o quanto o gap deve ser reduzido a cada incremento
// de dificuldade. (em pixels) ★ dif_max_altura: indica a diferença máxima de
// altura inicial entre obstáculos consecutivos. (em pixels) ★
// inc_dif_max_altura: indica o quanto a dif_max_altura deve ser incrementada a
// cada aumento de dificuldade. (em pixels) ★ vel_obstaculos: indica a
// velocidade inicial dos obstáculos em relação ao personagem.(em pixels) ★
// inc_vel_obstaculos: indica o quanto a velocidade dos obstáculos deve ser
// incrementada a cada aumento de dificuldade. (empixels)

void init_pipe_manager(PipeManager *pipeManager, Texture2D bottomPipeTexture,
                       Texture2D topPipeTexture);

void _random_pipe(PipeManager *pipeManager, Pipe *pipe, int i);

void pipe_movement(void *gameState, PipeManager *pipeManager);

void pipe_animation(PipeManager *pipeManager);

bool _pipe_collision(GameState *gameState, PipeManager *pipeManager, Pipe pipe);

#endif // PIPE_H