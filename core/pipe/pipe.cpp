#include "pipe.hpp"
#include "game/game.hpp"
#include "player/player.hpp"
#include "score/score.hpp"

PipeManager::PipeManager(PipeManagerConfig pmCfg)
    : bottomPipeTexture(renderer.loadTexture2D(pmCfg.bottomPipePath)),
      topPipeTexture(renderer.loadTexture2D(pmCfg.topPipePath)), offset(300),
      gap(200), obstacleVelocity(250) {

  // TODO: difficulty
  // PipeManager::incGap = inc_gap;
  // PipeManager::difMaxHeight = dif_max_height;
  // PipeManager::incDifMaxHeight = inc_dif_max_height;
  // PipeManager::incObstacleVelocity = inc_obstacle_velocity;

  PipeManager::fillPipes();
}

PipeManager::~PipeManager() {
  renderer.unloadTexture2D(bottomPipeTexture);
  renderer.unloadTexture2D(topPipeTexture);
}

void PipeManager::movement() {
  GameState &gameState = GameState::instance();

  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    // Atualizar posição dos tubos
    int newPosition = PipeManager::pipes[i].x -
                      PipeManager::obstacleVelocity * gameState.deltaTime;

    if (newPosition <= 0 && i != LAST_PIPE)
      PipeManager::pipes[i].x = 0;
    else
      PipeManager::pipes[i].x = newPosition;

    // Verifique se o tubo foi passado para gerar novo. Quando o cano chegar no
    // eixo X = 0, ele ira se tornar o ultimo cano da lista e um novo cano sera
    // gerado em sua posicao da lista, com novos valores
    if (PipeManager::pipes[i].x == 0) {
      PipeManager::pipes[LAST_PIPE].bottomPipeStart =
          PipeManager::pipes[i].bottomPipeStart;

      PipeManager::pipes[LAST_PIPE].topPipeStart =
          PipeManager::pipes[i].topPipeStart;

      PipeManager::pipes[LAST_PIPE].x = PipeManager::pipes[i].x;
      randomPipe(&PipeManager::pipes[i], 0);
      PipeManager::pipes[i].x =
          renderer.getScreenWidth() + (2 * PipeManager::offset);
    }

    // Validacao para canos perto do jogador
    bool pipeCloseToPlayer =
        PipeManager::pipes[i].x < (PLAYER_START_POSITION_X + 50) &&
        PipeManager::pipes[i].x > (PLAYER_START_POSITION_X - 50);

    if (pipeCloseToPlayer) {
      // Verifica se acertou cano para cada cano perto do jogador
      if (PipeManager::pipeCollision(PipeManager::pipes[i])) {
        // Publish(EVENT_COLLISION, PIPE, gameState);
        Player::player_dead(gameState.getPlayer());
      }
      // Se player passou pelo cano, ganha pontos
      if (PipeManager::pipes[i].x <= PLAYER_START_POSITION_X &&
          PipeManager::pipes[i].jumped == false) {
        PipeManager::pipes[i].jumped = true;
        gameState.getScore()->update();
      }
    }
  }
}

void PipeManager::render() {
  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    Pipe pipe = PipeManager::pipes[i];
    Vector2 topPipe = (Vector2){pipe.x, pipe.topPipeStart};
    Vector2 bottomPipe = (Vector2){pipe.x, pipe.bottomPipeStart};

    renderer.drawTextureEx(PipeManager::topPipeTexture, topPipe, 0.0, 1.0,
                           WHITE);
    renderer.drawTextureEx(PipeManager::bottomPipeTexture, bottomPipe, 0.0, 1.0,
                           WHITE);
  }
}

void PipeManager::fillPipes() {
  for (int i = 0; i < MAX_PIPE_COUNT; i++) {
    Pipe pipe;
    randomPipe(&pipe, i);
    PipeManager::pipes[i] = pipe;
  }
}

void PipeManager::randomPipe(Pipe *pipe, int i) {
  float topPipeHeight =
      renderer.getRandomValue(0, renderer.getScreenHeight() / 2);
  pipe->topPipeStart = (0 - renderer.getScreenHeight()) + topPipeHeight;
  pipe->bottomPipeStart = topPipeHeight + PipeManager::gap;
  pipe->x = (renderer.getScreenWidth() / 3 * 2) + (PipeManager::offset * i);
  pipe->jumped = false;
}

bool PipeManager::pipeCollision(Pipe pipe) {
  Player *p = GameState::instance().getPlayer();
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

  return (renderer.checkCollisionRecs(bottomPipe, player) ||
          renderer.checkCollisionRecs(topPipe, player));
}