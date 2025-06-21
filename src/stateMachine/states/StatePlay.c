#include "stateMachine/states/StatePlay.h"
#include "PipePairManager.h"
#include "Settings.h"
#include "raylib.h"
#include "smile.h"
#include "stateMachine/states/StateScore.h"
#include <stdio.h>
#include <stdlib.h>

// Data Types
// ----------
State statePlay = {.id = "play",
                   .enter = StatePlayEnter,
                   .update = StatePlayUpdate,
                   .draw = StatePlayDraw,
                   .exit = StatePlayExit};

static ScoreArgs scoreArgs;

// Prototypes
// ----------
static void CurrPipePairNodeUpdate(void);
static bool HasCollided(Bird *bird, PipePair *pipePair);
// ----------

// Variables
// ---------
static PipePairQueue pipes;
static PipePairNode *currPipePairNode;
static bool isPaused;
Texture pauseImg;
// ---------

void StatePlayEnter(void *args) { PipePairManagerInit(); }

void StatePlayUpdate(float dt) {
  if (isPaused) {
    if (IsKeyPressed(KEY_P)) {
      isPaused = !isPaused;
    }
  } else {
    PipePairsUpdate(&pipes, dt, V_SCREEN);
    BirdUpdate(gBird, dt);
    CurrPipePairNodeUpdate();

    if (currPipePairNode != NULL) {
      if (HasCollided(gBird, currPipePairNode->pipePair)) {
        gBird->isAlive = false;
      }
    }

    if (gBird->pos.y + gBird->hitBox.height > V_SCREEN.y - 16) {
      gBird->isAlive = false;
    }

    if (!gBird->isAlive) {
      PlaySound(explosionSound);
      PlaySound(hurtSound);
      sm_change_state(&stateScore, &scoreArgs);
    }

    if (IsKeyPressed(KEY_P)) {
      isPaused = !isPaused;
    }
  }
}

void CurrPipePairNodeUpdate(void) {
  if (currPipePairNode == NULL) {
    currPipePairNode = pipes.head;
    return;
  }

  float currPipePairPos = currPipePairNode->pipePair->pos->x;
  int currPipePairWidth = currPipePairNode->pipePair->width;
  if (gBird->pos.x > currPipePairPos + currPipePairWidth) {
    gBird->score++;
    PlaySound(scoreSound);
    currPipePairNode = currPipePairNode->next;
  }
}

bool HasCollided(Bird *bird, PipePair *pipePair) {
  return CheckCollisionRecs(bird->hitBox, pipePair->top->hitBox) ||
         CheckCollisionRecs(bird->hitBox, pipePair->bottom->hitBox);
}

void StatePlayDraw(void) {
  PipePairsDraw(&pipes);
  BirdDraw(gBird);
  if (isPaused) {
    float imgScale = 0.05;
    DrawTextureEx(pauseImg,
                  (Vector2){(V_SCREEN.x - pauseImg.width * imgScale) / 2.0,
                            (V_SCREEN.y - pauseImg.height * imgScale) / 2.0},
                  0, imgScale, WHITE);
  }

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "Score: %d", gBird->score);
  DrawTextEx(flappyFont, buffer, (Vector2){8, 8}, FLAPPY_FONT_SIZE, 1, WHITE);
}

void StatePlayExit() {
  scoreArgs.score = gBird->score;

  PipePairsUnload(&pipes);
  currPipePairNode = NULL;
}
