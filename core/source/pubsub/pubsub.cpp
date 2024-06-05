#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "network/network.h"
#include "player/player.h"
#include "pubsub.h"

#define MAX_SUBSCRIBERS 10

typedef struct GameState {
  bool online;
  bool hosting;
  bool pause;
  bool started;
  float gravity;
  float deltaTime;
  Server *server;
  Player *player;
} GameState;

typedef struct PipeManager PipeManager;
void restart_game(GameState *gameState, PipeManager *pipeManager,
                  Player *onlinePlayer);

typedef struct {
  SubscriberCallback callback;
  char eventType[50];
} Subscriber;

// Array to store subscribers
static Subscriber subscribers[MAX_SUBSCRIBERS];
static int numSubscribers = 0;

// Function to subscribe to a specific event type with a callback function
void Subscribe(const char *eventType, SubscriberCallback callback) {
  // Ensure we haven't reached the maximum number of subscribers
  if (numSubscribers < MAX_SUBSCRIBERS) {
    // Add the subscriber to the array
    subscribers[numSubscribers].callback = callback;
    strncpy(subscribers[numSubscribers].eventType, eventType,
            sizeof(subscribers[numSubscribers].eventType));
    numSubscribers++;
  }
}

// Function to publish an event with optional data
// void Publish(const char *eventType, const char *eventData, void
// *additionalData, void *additionalData2)
void Publish(const char *eventType, const char *eventData) {
  // Iterate through subscribers and notify those interested in the event type
  for (int i = 0; i < numSubscribers; ++i) {
    if (strcmp(subscribers[i].eventType, eventType) == 0) {
      // Call the subscriber's callback function with the event data and
      // additional data subscribers[i].callback(eventData, additionalData,
      // additionalData2);
      subscribers[i].callback(eventData);
    }
  }
}

void handle_in_network_messages(const char *eventData) {
  if (strcmp(eventData, NM_PLAYER_JUMP) == 0) {
    player_jump(global_onlinePlayer);
  }

  else if (strcmp(eventData, NM_GAME_START) == 0) {
    GameState *gameState = (GameState *)global_gameState;
    gameState->pause = !gameState->pause;
    gameState->started = true;
  }

  else if (strcmp(eventData, NM_GAME_RESTART) == 0) {
    GameState *gameState = (GameState *)global_gameState;
    PipeManager *pipeManager = (PipeManager *)global_pipeManager;
    Player *onlinePlayer = (Player *)global_onlinePlayer;
    restart_game(gameState, pipeManager, onlinePlayer);
  }
}

void handle_out_network_messages(const char *eventData) {
  if (strcmp(eventData, NM_PLAYER_JUMP) == 0) {
    GameState *gameState = (GameState *)global_gameState;
    char message[] = NM_PLAYER_JUMP;
    ssize_t bytesSent = -1;

    // If client, send message to host
    if (!gameState->hosting)
      bytesSent = send(((Server *)global_server)->serverSocket, message,
                       sizeof(message), 0);

    // If host, send message  to client
    if (gameState->hosting && gameState->server->clientSocket != 0)
      bytesSent = send(((Server *)global_server)->clientSocket, message,
                       sizeof(message), 0);

    if (bytesSent == -1) {
      printf("Errpr");
      perror("Send failed");
    };
  }

  else if (strcmp(eventData, NM_GAME_START) == 0) {
    char message[] = NM_GAME_START;
    ssize_t bytesSent = -1;

    // Send message from host to client
    bytesSent = send(((Server *)global_server)->clientSocket, message,
                     sizeof(message), 0);

    if (bytesSent == -1) {
      printf("Errpr");
      perror("Send failed");
    };
  }

  else if (strcmp(eventData, NM_GAME_RESTART) == 0) {
    char message[] = NM_GAME_RESTART;
    ssize_t bytesSent = -1;

    // Send message from host to client
    bytesSent = send(((Server *)global_server)->clientSocket, message,
                     sizeof(message), 0);

    if (bytesSent == -1) {
      printf("Errpr");
      perror("Send failed");
    };
  }
}

void handle_key_pressed(const char *eventData) {
  if (strcmp(eventData, K_SPACEBAR) == 0) {
    GameState *gameState = (GameState *)global_gameState;
    if (gameState->online)
      Publish(EVENT_OUT_NETWORK_MESSAGE, NM_PLAYER_JUMP);
    player_jump(global_player);
  }
}
