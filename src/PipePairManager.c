#include "PipePairManager.h"
#include "PipePair.h"
#include "Settings.h"
#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"

// Prototypes
// ----------
static void PipesEnqueue(PipePair *pipePair, PipePairQueue *pipePairs);
static void PipesDequeue(PipePairQueue *pipePairs);
static bool CanGeneratePipePair(float dt);
static void UpdateLastGapY(void);
static void PipePairsUnloadNode(PipePairNode *pipePairNode);
// ----------

// Variables
// ---------
static float spawnTimer;
static float lastGapY;
// ---------

void PipePairManagerInit(void) {
  spawnTimer = 0.0f;
  lastGapY = GetRandomValue(PIPE_TOP_MARGIN,
                            V_SCREEN.y - PIPE_GAP - PIPE_BOTTOM_MARGIN);
}

static void PipesEnqueue(PipePair *pipePair, PipePairQueue *pipePairs) {
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

static void PipesDequeue(PipePairQueue *pipes) {
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

void PipePairsUpdate(PipePairQueue *pipePairs, float dt, Vector2 screen) {

  if (CanGeneratePipePair(dt)) {
    UpdateLastGapY();
    PipePair *newPipePair = NewPipePair((Vector2){screen.x + 32, lastGapY});
    PipesEnqueue(newPipePair, pipePairs);
  }

  PipePairNode *curr = pipePairs->head;
  while (curr != NULL) {
    PipePairUpdate(curr->pipePair, dt);
    PipePairNode *next = curr->next;
    if (curr->pipePair->pos->x < -curr->pipePair->width) {
      PipesDequeue(pipePairs);
    }
    curr = next;
  }
}

static bool CanGeneratePipePair(float dt) {
  spawnTimer += dt;
  if (spawnTimer > SPAWN_TIME) {
    spawnTimer = 0.0f;
    return true;
  }
  return false;
}

static void UpdateLastGapY(void) {
  lastGapY += GetRandomValue(-PIPE_SHIFT, PIPE_SHIFT);
  lastGapY = Clamp(lastGapY, PIPE_TOP_MARGIN,
                   V_SCREEN.y - PIPE_GAP - PIPE_BOTTOM_MARGIN);
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

static void PipePairsUnloadNode(PipePairNode *pipePairNode) {
  PipePairUnload(pipePairNode->pipePair);
  free(pipePairNode);
}