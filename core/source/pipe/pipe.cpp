#include "pipe.h"
#include "constants.h"

void init_pipe_manager(PipeManager *pipeManager, Texture2D bottomPipeTexture,
                       Texture2D topPipeTexture) {
  const int GAP = 200;
  const int OBSTACLE_VELOCITY = OBSTACLE_VELOCITYY;

  pipeManager->bottomPipeTexture = bottomPipeTexture;
  pipeManager->topPipeTexture = topPipeTexture;
  pipeManager->offset = 300;

  pipeManager->gap = GAP;
  // pipeManager->incGap = inc_gap;
  // pipeManager->difMaxHeight = dif_max_height;
  // pipeManager->incDifMaxHeight = inc_dif_max_height;
  pipeManager->obstacleVelocity = OBSTACLE_VELOCITY;
  // pipeManager->incObstacleVelocity = inc_obstacle_velocity;

  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    Pipe pipe;
    _random_pipe(pipeManager, &pipe, i);
    pipeManager->pipes[i] = pipe;
  }
}

void _random_pipe(PipeManager *pipeManager, Pipe *pipe, int i) {
  float topPipeHeight = GetRandomValue(0, GetScreenHeight() / 2);
  pipe->topPipeStart = (0 - GetScreenHeight()) + topPipeHeight;
  pipe->bottomPipeStart = topPipeHeight + pipeManager->gap;
  pipe->x = (GetScreenWidth() / 3 * 2) + (pipeManager->offset * i);
  pipe->jumped = false;
}

void pipe_movement(void *g, PipeManager *pipeManager) {
  GameState *gameState = (GameState *)g;

  if (gameState->player->alive) {
    for (int i = 0; i < MAX_PIPE_COUNT; i++) {
      // Atualizar posição dos tubos
      int newPosition = pipeManager->pipes[i].x -
                        pipeManager->obstacleVelocity * gameState->deltaTime;

      if (newPosition <= 0 && i != LAST_PIPE)
        pipeManager->pipes[i].x = 0;
      else
        pipeManager->pipes[i].x = newPosition;

      // TODO: Adicionar animacao para ele sumindo
      // Verifique se o tubo foi passado para gerar novo
      // Quando o cano chegar no eixo X = 0, ele ira se tornar o ultimo cano da
      // lista E um novo cano sera gerado em sua posicao da lista, com novos
      // valores
      if (pipeManager->pipes[i].x == 0) {
        pipeManager->pipes[LAST_PIPE].bottomPipeStart =
            pipeManager->pipes[i].bottomPipeStart;
        pipeManager->pipes[LAST_PIPE].topPipeStart =
            pipeManager->pipes[i].topPipeStart;
        pipeManager->pipes[LAST_PIPE].x = pipeManager->pipes[i].x;
        _random_pipe(pipeManager, &pipeManager->pipes[i], 0);
        pipeManager->pipes[i].x = GetScreenWidth() + (2 * pipeManager->offset);
      }

      // Validacao para canos perto do jogador
      bool pipeCloseToPlayer =
          pipeManager->pipes[i].x < (PLAYER_START_POSITION_X + 50) &&
          pipeManager->pipes[i].x > (PLAYER_START_POSITION_X - 50);
      if (pipeCloseToPlayer) {
        // Verifica se acertou cano para cada cano perto do jogador
        if (_pipe_collision(gameState, pipeManager, pipeManager->pipes[i])) {
          // Publish(EVENT_COLLISION, PIPE, gameState);
          player_dead(gameState->player);
        }
        // Se player passou pelo cano, ganha pontos
        if (pipeManager->pipes[i].x <= PLAYER_START_POSITION_X &&
            pipeManager->pipes[i].jumped == false) {
          pipeManager->pipes[i].jumped = true;
          score_update(gameState->score);
        }
      }
    }
  }
}

void pipe_animation(PipeManager *pipeManager) {
  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    Pipe pipe = pipeManager->pipes[i];
    Vector2 topPipe = (Vector2){pipe.x, pipe.topPipeStart};
    Vector2 bottomPipe = (Vector2){pipe.x, pipe.bottomPipeStart};

    DrawTextureEx(pipeManager->topPipeTexture, topPipe, 0.0, 1.0, WHITE);
    DrawTextureEx(pipeManager->bottomPipeTexture, bottomPipe, 0.0, 1.0, WHITE);
  }
}

bool _pipe_collision(GameState *gameState, PipeManager *pipeManager,
                     Pipe pipe) {
  Player *p = gameState->player;
  // Menos 20%
  float playerWidth = p->current.width - (p->current.width / 10 * 2);
  float playerHeight = p->current.height - (p->current.height / 10 * 2);

  // Offset para erro da posicao X
  float pipeX = pipe.x + 40;
  // Menos 20%
  float pipeWidth = pipeManager->topPipeTexture.width -
                    (pipeManager->topPipeTexture.width / 10 * 2);

  float topPipeY = pipe.topPipeStart + 20;
  float topPipeHeight = pipeManager->topPipeTexture.height;

  float bottomPipeY = pipe.bottomPipeStart + 30;
  float bottomPipeHeight = pipeManager->bottomPipeTexture.height;

  Rectangle player = {p->position.x, p->position.y, playerWidth, playerHeight};
  Rectangle bottomPipe = {pipeX, bottomPipeY, pipeWidth, bottomPipeHeight};
  Rectangle topPipe = {pipeX, topPipeY, pipeWidth, topPipeHeight};

  return (CheckCollisionRecs(bottomPipe, player) ||
          CheckCollisionRecs(topPipe, player));
}