#pragma once

#include <WebServer.h>
#include <WebSocketsServer.h>

#include "animation.h"

// Shared HTTP server instance.
extern WebServer server;

// WebSocket server for Pong controls (port 81).
extern WebSocketsServer wsServer;

// Must be called in loop() to process WebSocket traffic.
void loopWebSocket();

// Broadcast Pong game state to all connected WS clients.
void broadcastPongState();

// Configure Wi-Fi access point and register all HTTP routes.
void setupWebServer();

