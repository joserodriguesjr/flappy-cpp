#include "pipe.hpp"
#include "constants.h"
#include <cstdio>

PipeManager::PipeManager() : offset(300), gap(200), obstacleVelocity(250) {

  PipeManager::bottomPipeTexture =
      LoadTexture("resources/obstacles/bottomPipe.png");
  PipeManager::topPipeTexture = LoadTexture("resources/obstacles/topPipe.png");

  // PipeManager::incGap = inc_gap;
  // PipeManager::difMaxHeight = dif_max_height;
  // PipeManager::incDifMaxHeight = inc_dif_max_height;
  // PipeManager::incObstacleVelocity = inc_obstacle_velocity;

  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    Pipe pipe;
    _random_pipe(this, &pipe, i);
    PipeManager::pipes[i] = pipe;
  }
}

PipeManager::~PipeManager() {
  UnloadTexture(bottomPipeTexture);
  UnloadTexture(topPipeTexture);
}

void PipeManager::_random_pipe(PipeManager *pipeManager, Pipe *pipe, int i) {
  float topPipeHeight = GetRandomValue(0, GetScreenHeight() / 2);
  pipe->topPipeStart = (0 - GetScreenHeight()) + topPipeHeight;
  pipe->bottomPipeStart = topPipeHeight + PipeManager::gap;
  pipe->x = (GetScreenWidth() / 3 * 2) + (PipeManager::offset * i);
  pipe->jumped = false;
}

void PipeManager::movement(void *g) {
  GameState *gameState = (GameState *)g;

  if (!gameState->player->alive)
    return;

  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    // Atualizar posição dos tubos
    int newPosition = PipeManager::pipes[i].x -
                      PipeManager::obstacleVelocity * gameState->deltaTime;

    if (newPosition <= 0 && i != LAST_PIPE)
      PipeManager::pipes[i].x = 0;
    else
      PipeManager::pipes[i].x = newPosition;

    // TODO: Adicionar animacao para ele sumindo
    // Verifique se o tubo foi passado para gerar novo
    // Quando o cano chegar no eixo X = 0, ele ira se tornar o ultimo cano da
    // lista E um novo cano sera gerado em sua posicao da lista, com novos
    // valores
    if (PipeManager::pipes[i].x == 0) {
      PipeManager::pipes[LAST_PIPE].bottomPipeStart =
          PipeManager::pipes[i].bottomPipeStart;
      PipeManager::pipes[LAST_PIPE].topPipeStart =
          PipeManager::pipes[i].topPipeStart;
      PipeManager::pipes[LAST_PIPE].x = PipeManager::pipes[i].x;
      _random_pipe(this, &PipeManager::pipes[i], 0);
      PipeManager::pipes[i].x = GetScreenWidth() + (2 * PipeManager::offset);
    }

    // Validacao para canos perto do jogador
    bool pipeCloseToPlayer =
        PipeManager::pipes[i].x < (PLAYER_START_POSITION_X + 50) &&
        PipeManager::pipes[i].x > (PLAYER_START_POSITION_X - 50);
    if (pipeCloseToPlayer) {
      // Verifica se acertou cano para cada cano perto do jogador
      if (PipeManager::_pipe_collision(gameState, this,
                                       PipeManager::pipes[i])) {
        // Publish(EVENT_COLLISION, PIPE, gameState);
        Player::player_dead(gameState->player);
      }
      // Se player passou pelo cano, ganha pontos
      if (PipeManager::pipes[i].x <= PLAYER_START_POSITION_X &&
          PipeManager::pipes[i].jumped == false) {
        PipeManager::pipes[i].jumped = true;
        score_update(gameState->score);
      }
    }
  }
}

void PipeManager::render() {
  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    Pipe pipe = PipeManager::pipes[i];
    Vector2 topPipe = (Vector2){pipe.x, pipe.topPipeStart};
    Vector2 bottomPipe = (Vector2){pipe.x, pipe.bottomPipeStart};

    DrawTextureEx(PipeManager::topPipeTexture, topPipe, 0.0, 1.0, WHITE);
    DrawTextureEx(PipeManager::bottomPipeTexture, bottomPipe, 0.0, 1.0, WHITE);
  }
}

bool PipeManager::_pipe_collision(GameState *gameState,
                                  PipeManager *pipeManager, Pipe pipe) {
  Player *p = gameState->player;
  // Menos 20%
  float playerWidth = p->current.width - (p->current.width / 10 * 2);
  float playerHeight = p->current.height - (p->current.height / 10 * 2);

  // Offset para erro da posicao X
  float pipeX = pipe.x + 40;
  // Menos 20%
  float pipeWidth = PipeManager::topPipeTexture.width -
                    (PipeManager::topPipeTexture.width / 10 * 2);

  float topPipeY = pipe.topPipeStart + 20;
  float topPipeHeight = PipeManager::topPipeTexture.height;

  float bottomPipeY = pipe.bottomPipeStart + 30;
  float bottomPipeHeight = PipeManager::bottomPipeTexture.height;

  Rectangle player = {p->position.x, p->position.y, playerWidth, playerHeight};
  Rectangle bottomPipe = {pipeX, bottomPipeY, pipeWidth, bottomPipeHeight};
  Rectangle topPipe = {pipeX, topPipeY, pipeWidth, topPipeHeight};

  return (CheckCollisionRecs(bottomPipe, player) ||
          CheckCollisionRecs(topPipe, player));
}