// Inlcudes
// --------
#include "stateMachine/states/StateTitle.h"
#include "Settings.h"
#include "raylib.h"
#include "smile.h"
#include "stateMachine/states/StateCountdown.h"
#include <stdlib.h>
// --------

// Data Types
// ----------
State stateTitle = {.enter = NULL,
                    .update = StateTitleUpdate,
                    .draw = StateTitleDraw,
                    .exit = NULL};

// Variables
// ---------
static const char PROMPT[] = "Press Enter";
// ---------

void StateTitleUpdate(float dt) {
  if (HasValidInput(input2)) {
    sm_change_state(&stateCountdown, NULL);
  }
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
  BirdDraw(gBird);
}
