#include "network.h"
#include "player/player.hpp"
#include "pubsub.h"
#include <cstdio>
#include <cstring>

typedef struct GameState {
  Server *server;
  Player *player;
} GameState;

// TODO: Error handling
void start_server(void) {
  Server *server = (Server *)global_server;
  int serverSocket;
  struct sockaddr_in serverAddr;

  if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) ==
      -1) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(serverSocket, 5) == -1) {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on :%d\n", PORT);

  server->host = true;
  server->serverSocket = serverSocket;
  server->clientSocket = 0;
  server->serverAddr = serverAddr;
}

void close_server(void) {
  Server *server = (Server *)global_server;
  close(server->serverSocket);
}

void start_client(void) {
  int serverSocket;
  struct sockaddr_in serverAddr;
  Server *server = (Server *)global_server;

  if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(serverSocket, (struct sockaddr *)&serverAddr,
              sizeof(serverAddr)) == -1) {
    perror("Connection failed");
    close(serverSocket);
    return;
  }

  server->serverSocket = serverSocket;
  server->serverAddr = serverAddr;
}

void *wait_for_server(void *arg) {
  printf("WAIT FOR SERVER\n");
  Server *server = (Server *)global_server;
  while (1) {
    handle_connection(server->serverSocket);
  }
}

void *wait_for_client(void *arg) {
  printf("WAIT FOR CLIENT\n");
  while (1) {
    int clientSocket =
        accept(((Server *)global_server)->serverSocket, NULL, NULL);
    ((Server *)global_server)->clientSocket = clientSocket;
    if (clientSocket == -1) {
      perror("Accept failed");
      break;
    }
    handle_connection(clientSocket);
  }
}

void handle_connection(int socket) {
  char buffer[BUFFER_SIZE];
  int bytesRead;

  while (1) {
    bytesRead = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
      printf("Connection closed or error\n");
      break;
    }
    buffer[bytesRead] = '\0';
    printf("HANDLE CON - Received message = %s\n", buffer);
    Publish(EVENT_IN_NETWORK_MESSAGE, buffer);
  }
  close(socket);
}