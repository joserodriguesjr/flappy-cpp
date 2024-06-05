#ifndef PUBSUB_H
#define PUBSUB_H

#define MAX_SUBSCRIBERS 10

// Define a function pointer type for the subscriber callback
// typedef void (*SubscriberCallback)(const char *, void *, void *);
typedef void (*SubscriberCallback)(const char *);

// Function to subscribe to a specific event type with a callback function
void Subscribe(const char *eventType, SubscriberCallback callback);

// Function to publish an event with optional data
// void Publish(const char *eventType, const char *eventData, void
// *additionalData, void *additionalData2);
void Publish(const char *eventType, const char *eventData);

// Event types
#define EVENT_IN_NETWORK_MESSAGE "InNetwork"
#define EVENT_OUT_NETWORK_MESSAGE "OutNetwork"
#define EVENT_KEY_PRESSED "KeyPressed"

#define EVENT_COLLISION "Collision"
#define EVENT_MOVEMENT "Movement"

// Network Messages
#define NM_PLAYER_JUMP "PLAYER-JUMP;"
#define NM_GAME_START "GAME-START;"
#define NM_GAME_RESTART "GAME-RESTART;"

// Keys
#define K_SPACEBAR "SPACEBAR"

void handle_in_network_messages(const char *eventData);
void handle_out_network_messages(const char *eventData);
void handle_key_pressed(const char *eventData);
// void HandleMovement(const char *eventData, void *g, void *p)

#endif // PUBSUB_H