#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct Server {
  bool host;
  int serverSocket;
  int clientSocket;
  struct sockaddr_in serverAddr;
  pthread_mutex_t serverMutex;
} Server;

void start_server(void);
void close_server(void);

void start_client(void);

void *wait_for_client(void *arg);
void *wait_for_server(void *arg);

void handle_connection(int socket);

#endif /* NETWORK_H */