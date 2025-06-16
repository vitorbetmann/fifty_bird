#include "states/StatePlay.h"
#include "PipePairManager.h"
#include "Settings.h"
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

void StatePlayEnter(Bird *playerBird) {
  PipePairManagerInit();
  bird = playerBird;
  BirdReset(playerBird);
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
}

void CurrPipePairNodeUpdate(void) {
  if (currPipePairNode == NULL) {
    currPipePairNode = pipes.head;
    return;
  }

  float currPipePairPos = currPipePairNode->pipePair->pos->x;
  int currPipePairWidth = currPipePairNode->pipePair->width;
  if (bird->pos.x > currPipePairPos + currPipePairWidth) {
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
}

void StatePlayExit() { PipePairsUnload(&pipes); }