#pragma once

#include <Arduino.h>
#include "animation.h"

// ── Pong game config ────────────────────────────────────────────────

#define PONG_PADDLE_HEIGHT  4
#define PONG_PADDLE_X1      1    // Player 1 column
#define PONG_PADDLE_X2      30   // Player 2 column
#define PONG_WIN_SCORE      5
#define PONG_SERVE_DELAY_MS 1000
#define PONG_TICK_MS        33   // ~30 fps

// ── Game status ─────────────────────────────────────────────────────

enum PongStatus : uint8_t {
  PONG_WAITING,   // waiting for 2 players
  PONG_PLAYING,
  PONG_SCORED,    // brief pause after a goal
  PONG_GAMEOVER
};

// ── Game state ──────────────────────────────────────────────────────

struct PongState {
  float ballX, ballY;
  float ballVX, ballVY;
  int8_t paddle1Y, paddle2Y;   // top pixel of each paddle
  int8_t paddle1Dir, paddle2Dir; // -1 up, 0 stop, +1 down
  uint8_t score1, score2;
  PongStatus status;
  uint8_t winner;               // 0=none, 1 or 2
  unsigned long lastTick;
  unsigned long scoreTime;      // millis() when a goal was scored
  uint8_t playerCount;
};

extern PongState pong;

// ── Public API ──────────────────────────────────────────────────────

void initPong();
void resetPongGame();
void updatePong();
void renderPong();

// Player slot management (returns assigned player number 1|2, or 0 if full)
uint8_t pongAddPlayer();
void    pongRemovePlayer(uint8_t player);

// Input from WebSocket: action = "up", "down", "release"
void handlePongInput(uint8_t player, const char* action);
