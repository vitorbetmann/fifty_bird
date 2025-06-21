#include "stateMachine/states/StateCountdown.h"
#include "Bird.h"
#include "Settings.h"
#include "raylib.h"
#include "smile.h"
#include "stateMachine/StateMachine.h"
#include "stateMachine/states/StatePlay.h"
#include <stdio.h>

// Data types
// ----------
State stateCountdown = {.id = "countdown",
                        .enter = StateCountdownEnter,
                        .update = StateCountdownUpdate,
                        .draw = StateCountdownDraw,
                        .exit = NULL};

// Prototypes
// ----------
bool IsTimerOver(void);

// Variables
// ---------
static const float COUNTDOWN_TIME = 0.75;
static float timer;
// ---------

void StateCountdownEnter(void *args) {
  BirdReset(gBird);

  timer = 4.0f;
}

void StateCountdownUpdate(float dt) {
  timer -= 1.25 * dt;

  if (IsTimerOver()) {
    sm_change_state(&statePlay, NULL);
  }
}

bool IsTimerOver(void) { return timer < 1; }

void StateCountdownDraw(void) {
  BirdDraw(gBird);

  char buffer[sizeof(char) + 1];
  snprintf(buffer, sizeof(buffer), "%d", (int)(timer));
  int textWidth = MeasureText(buffer, HUGE_FONT_SIZE);
  float textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(hugeFont, buffer, (Vector2){textX, 80}, HUGE_FONT_SIZE, 1, WHITE);
}
