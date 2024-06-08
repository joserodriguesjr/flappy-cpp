#include "pipe.hpp"
#include "game/game.hpp"
#include "player/player.hpp"
#include "score/score.hpp"

PipeManager::PipeManager(PipeManagerConfig pmCfg)
    : bottomPipeTexture(renderer.loadTexture2D(pmCfg.bottomPipePath)),
      topPipeTexture(renderer.loadTexture2D(pmCfg.topPipePath)), offset(300),
      gap(200), obstacleVelocity(250) {

  PipeManager::fillPipes();
}

PipeManager::~PipeManager() {
  renderer.unloadTexture2D(bottomPipeTexture);
  renderer.unloadTexture2D(topPipeTexture);
}

void PipeManager::movement() {
  for (auto &pipe : pipes) {
    updatePipePosition(pipe);
    handlePipeReset(pipe);
    checkPipeProximityToPlayer(pipe);
  }
}

void PipeManager::updatePipePosition(Pipe &pipe) {
  int newPosition = pipe.x - obstacleVelocity * gameState.deltaTime;

  if (newPosition <= 0 && &pipe != &pipes[LAST_PIPE]) {
    pipe.x = 0;
  } else {
    pipe.x = newPosition;
  }
}

void PipeManager::handlePipeReset(Pipe &pipe) {
  if (pipe.x == 0) {
    pipes[LAST_PIPE].bottomPipeStart = pipe.bottomPipeStart;
    pipes[LAST_PIPE].topPipeStart = pipe.topPipeStart;
    pipes[LAST_PIPE].x = pipe.x;

    randomPipe(&pipe, 0);
    pipe.x = renderer.getScreenWidth() + (2 * offset);
  }
}

void PipeManager::checkPipeProximityToPlayer(Pipe &pipe) {
  bool pipeCloseToPlayer = pipe.x < (PLAYER_START_POSITION_X + 50) &&
                           pipe.x > (PLAYER_START_POSITION_X - 50);

  if (pipeCloseToPlayer) {
    if (pipeCollision(pipe)) {
      Player::player_dead(gameState.getPlayer());
    }

    if (pipe.x <= PLAYER_START_POSITION_X && !pipe.jumped) {
      pipe.jumped = true;
      gameState.getScore()->update();
    }
  }
}

void PipeManager::render() {
  for (auto &pipe : pipes) {
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