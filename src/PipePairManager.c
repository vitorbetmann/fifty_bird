#include "PipePairManager.h"
#include "PipePair.h"
#include "raylib.h"
#include "stdlib.h"

static float spawnTimer;

void PipePairManagerInit(void) {
  spawnTimer = 0.0f;
  PipePairInit();
}

void PipesEnqueue(PipePair *pipePair, PipePairQueue *pipePairs) {
  PipePairNode *newNode = malloc(sizeof(PipePairNode));
  if (newNode == NULL) {
    return;
  }

  newNode->pipePair = pipePair;
  newNode->next = NULL;

  if (pipePairs->head == NULL) {
    pipePairs->head = pipePairs->tail = newNode;
  } else {
    pipePairs->tail->next = newNode;
    pipePairs->tail = newNode;
  }
}

void PipesDequeue(PipePairQueue *pipes) {
  if (pipes->head == NULL) {
    return;
  }
  PipePairNode *temp = pipes->head;
  pipes->head = pipes->head->next;

  if (pipes->head == NULL) {
    pipes->tail = NULL;
  }

  PipePairsUnloadNode(temp);
}

void PipesUpdate(PipePairQueue *pipePairs, float dt, Vector2 screen) {

  if (CanGeneratePipePair(dt)) {
    PipesEnqueue(NewPipePair(screen), pipePairs);
  }

  PipePairNode *curr = pipePairs->head;
  while (curr != NULL) {
    PipePairUpdate(curr->pipePair, dt);
    PipePairNode *next = curr->next;
    if (curr->pipePair->pos->x < -(*curr->pipePair->width)) {
      PipesDequeue(pipePairs);
    }
    curr = next;
  }
}

bool CanGeneratePipePair(float dt) {
  spawnTimer += dt;
  if (spawnTimer > 2) {
    spawnTimer = 0.0f;
    return true;
  }
  return false;
}

void PipePairsDraw(PipePairQueue *pipes) {
  PipePairNode *curr = pipes->head;
  while (curr != NULL) {
    PipePairDraw(curr->pipePair);
    curr = curr->next;
  }
}

void PipePairsUnload(PipePairQueue *pipes) {
  PipePairNode *curr = pipes->head;
  while (curr != NULL) {
    PipePairNode *next = curr->next;
    PipePairsUnloadNode(curr);
    curr = next;
  }

  pipes->head = pipes->tail = NULL;
}

void PipePairsUnloadNode(PipePairNode *pipePairNode) {
  PipePairUnload(pipePairNode->pipePair);
  free(pipePairNode);
}