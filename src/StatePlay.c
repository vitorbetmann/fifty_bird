#include "states/StatePlay.h"
#include "PipePairManager.h"
#include "Settings.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

// Prototypes
// ----------
static void CurrPipePairNodeUpdate(void);
static bool HasCollided(Bird *bird, PipePair *pipePair);
// ----------

// Variables
// ---------
static Bird *bird;
static PipePairQueue pipes;
static PipePairNode *currPipePairNode;
// ---------

void StatePlayEnter(Bird *player) {
  PipePairManagerInit();
  bird = player;
}

void StatePlayUpdate(float dt) {
  PipePairsUpdate(&pipes, dt, V_SCREEN);
  BirdUpdate(bird, dt);
  CurrPipePairNodeUpdate();

  if (currPipePairNode != NULL) {
    if (HasCollided(bird, currPipePairNode->pipePair)) {
      bird->isAlive = false;
    }
  }

  if (bird->pos.y + bird->hitBox.height > V_SCREEN.y - 16) {
    bird->isAlive = false;
  }

  if (!bird->isAlive) {
    PlaySound(explosionSound);
    PlaySound(hurtSound);
  }
}

void CurrPipePairNodeUpdate(void) {
  if (currPipePairNode == NULL) {
    currPipePairNode = pipes.head;
    return;
  }

  float currPipePairPos = currPipePairNode->pipePair->pos->x;
  int currPipePairWidth = currPipePairNode->pipePair->width;
  if (bird->pos.x > currPipePairPos + currPipePairWidth) {
    bird->score++;
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
  BirdDraw(bird);

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "Score: %d", bird->score);
  DrawTextEx(flappyFont, buffer, (Vector2){8, 8}, FLAPPY_FONT_SIZE, 1, WHITE);
}

void StatePlayExit() {
  PipePairsUnload(&pipes);
  currPipePairNode = NULL;
}