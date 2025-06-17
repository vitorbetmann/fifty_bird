#include "states/StateCountdown.h"
#include "Bird.h"
#include "Settings.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>

// Variables
// ---------
static const float COUNTDOWN_TIME = 0.75;
static float timer;
// ---------

void StateCountdownEnter() {
  BirdReset(gBird);
  timer = 3.4f;
}

void StateCountdownUpdate(float dt) { timer -= 1.25 * dt; }

bool IsTimerOver(void) { return timer < 1; }

void StateCountdownDraw(void) {
  BirdDraw(gBird);

  char buffer[sizeof(char) + 1];
  snprintf(buffer, sizeof(buffer), "%d", (int)(roundf)(timer));
  int textWidth = MeasureText(buffer, HUGE_FONT_SIZE);
  float textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(hugeFont, buffer, (Vector2){textX, 80}, HUGE_FONT_SIZE, 1, WHITE);
}

void StateCountdownExit(void) {
  // Do nothing
}
