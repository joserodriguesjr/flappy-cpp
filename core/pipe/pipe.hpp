#pragma once

#include "game/game.hpp"
#include "interface/renderer.hpp"

const unsigned int MAX_PIPE_COUNT = 7;
const unsigned int LAST_PIPE = MAX_PIPE_COUNT - 1;

struct PipeManagerConfig {
  const char *bottomPipePath;
  const char *topPipePath;

  PipeManagerConfig(const char *bottomPipe, const char *topPipe)
      : bottomPipePath(bottomPipe), topPipePath(topPipe) {}
};

typedef struct Pipe {
  float topPipeStart;
  float bottomPipeStart;
  float x;
  // Se removido [jumped], irá contar pontos enquanto o jogador estiver no vão
  bool jumped;
} Pipe;

class PipeManager {
private:
  GameState &gameState = GameState::instance();

  Renderer &renderer = Renderer::instance();

  Texture2D bottomPipeTexture;
  Texture2D topPipeTexture;
  Pipe pipes[MAX_PIPE_COUNT];
  int offset;
  int gap;
  // int incGap;
  // int difMaxHeight;
  // int incDifMaxHeight;
  int obstacleVelocity;
  // int incObstacleVelocity;
  void randomPipe(Pipe *pipe, int i);
  bool pipeCollision(Pipe pipe);
  void updatePipePosition(Pipe &pipe);
  void handlePipeReset(Pipe &pipe);
  void checkPipeProximityToPlayer(Pipe &pipe);

public:
  PipeManager(PipeManagerConfig pmCfg);
  ~PipeManager();

  void movement();
  void render();
  void fillPipes();
};

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
