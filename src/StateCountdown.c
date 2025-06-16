#include "states/StateCountdown.h"
#include "Bird.h"
#include "Settings.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>

// Variables
// ---------
static Bird *bird;
static const float COUNTDOWN_TIME = 0.75;
static int count;
static float timer;
// ---------

void StateCountdownEnter(Bird *player) {
  bird = player;
  count = 3;
  timer = 0.0f;
  BirdReset(bird);
}

void StateCountdownUpdate(float dt) {
  timer += dt;
  if (timer > COUNTDOWN_TIME) {
    timer = fmodf(timer, COUNTDOWN_TIME);
    count--;
  }
}

bool IsTimerOver(void) { return count == 0; }

void StateCountdownDraw(void) {
  BirdDraw(bird);

  char buffer[sizeof(char) + 1];
  snprintf(buffer, sizeof(buffer), "%d", count);
  int textWidth = MeasureText(buffer, HUGE_FONT_SIZE);
  float textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(hugeFont, buffer, (Vector2){textX, 80}, HUGE_FONT_SIZE, 1, WHITE);
}

void StateCountdownExit(void) {
  // Do nothing
}
