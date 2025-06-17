#include "states/StateScore.h"
#include "Settings.h"
#include "raylib.h"

#include "Settings.h"
#include "string.h"
#include <stdint.h>
#include <stdio.h>

// Variables
// ---------
static const char GAME_OVER_MSG[] = "Oof! You lost!";
static const char PLAY_AGAIN_MSG[] = "Press Enter to Play Again";
static const char SCORE_MSG[] = "Score: ";
static int score;
// ---------

void StateScoreEnter() { score = gBird->score; }

void StateScoreUpdate(float dt) {
  // Do nothing
}

void StateScoreDraw(void) {
  int textWidth = MeasureText(GAME_OVER_MSG, FLAPPY_FONT_SIZE);
  float textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(flappyFont, GAME_OVER_MSG, (Vector2){textX, 64}, FLAPPY_FONT_SIZE,
             1, WHITE);

  char buffer[sizeof(SCORE_MSG) + sizeof(uint32_t)];
  snprintf(buffer, sizeof(buffer), "%s%d", SCORE_MSG, score);
  textWidth = MeasureText(buffer, MEDIUM_FONT_SIZE);
  textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(mediumFont, buffer, (Vector2){textX, 100}, MEDIUM_FONT_SIZE, 1,
             WHITE);

  textWidth = MeasureText(PLAY_AGAIN_MSG, MEDIUM_FONT_SIZE);
  textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(mediumFont, PLAY_AGAIN_MSG, (Vector2){textX, 160},
             MEDIUM_FONT_SIZE, 1, WHITE);
}

void StateScoreExit(void) {
  // Do nothing
}