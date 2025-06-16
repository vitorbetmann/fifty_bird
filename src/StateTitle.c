#include "states/StateTitle.h"

// Inlcudes
// --------
#include "Settings.h"
#include "raylib.h"
// --------

// Variables
// ---------
const char *const PROMPT = "Press Enter";
static Bird *bird;
// ---------

void StateTitleEnter(Bird *player) {
  bird = player;
  //
}

void StateTitleUpdate(float dt) {
  // Nothing to do
}

void StateTitleDraw(void) {
  int textWidth = MeasureText(GAME_TITLE, FLAPPY_FONT_SIZE);
  float textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(flappyFont, GAME_TITLE, (Vector2){textX, 64}, FLAPPY_FONT_SIZE, 1,
             WHITE);

  textWidth = MeasureText(PROMPT, MEDIUM_FONT_SIZE);
  textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(mediumFont, PROMPT, (Vector2){textX, 100}, MEDIUM_FONT_SIZE, 1,
             WHITE);
  BirdDraw(bird);
}

void StateTitleExit(void) {
  // Nothing to do
}
